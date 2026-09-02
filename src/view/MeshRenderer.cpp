#include "MeshRenderer.hpp"

#include <QDebug>
#include <algorithm>
#include <array>
#include <set>

MeshRenderer::MeshRenderer() {}

MeshRenderer::~MeshRenderer() {
    destroy();
}

bool MeshRenderer::initialize(QOpenGLShaderProgram& program) {
    if (mInitialized) {
        return true;
    }

    if (!mVao.create()) {
        qWarning() << "Failed to create vertex array object.";
        return false;
    }
    if (!mLineVao.create()) {
        qWarning() << "Failed to create line vertex array object.";
        mVao.destroy();
        return false;
    }
    if (!mTriangulationVao.create()) {
        qWarning() << "Failed to create triangulation vertex array object.";
        mLineVao.destroy();
        mVao.destroy();
        return false;
    }

    if (!mPointVbo.create()) {
        qWarning() << "Failed to create point vertex buffer.";
        mVao.destroy();
        mLineVao.destroy();
        mTriangulationVao.destroy();
        return false;
    }
    if (!mLineVbo.create()) {
        qWarning() << "Failed to create line vertex buffer.";
        mPointVbo.destroy();
        mVao.destroy();
        mLineVao.destroy();
        mTriangulationVao.destroy();
        return false;
    }
    if (!mTriangulationVbo.create()) {
        qWarning() << "Failed to create triangulation vertex buffer.";
        mLineVbo.destroy();
        mPointVbo.destroy();
        mVao.destroy();
        mLineVao.destroy();
        mTriangulationVao.destroy();
        return false;
    }
    mPointVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mLineVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mTriangulationVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    mVao.bind();
    program.bind();
    mPointVbo.bind();

    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));

    mPointVbo.release();

    mLineVao.bind();
    mLineVbo.bind();
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));

    mLineVbo.release();

    mTriangulationVao.bind();
    mTriangulationVbo.bind();
    program.enableAttributeArray(0);
    program.setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    mTriangulationVbo.release();

    program.release();
    mTriangulationVao.release();
    mLineVao.release();
    mVao.release();

    mInitialized = true;
    return true;
}

void MeshRenderer::destroy() {
    if (!mInitialized) {
        return;
    }
    mVao.destroy();
    mLineVao.destroy();
    mTriangulationVao.destroy();
    mPointVbo.destroy();
    mLineVbo.destroy();
    mTriangulationVbo.destroy();
    mInitialized = false;
}

void MeshRenderer::draw() {
    if (!mInitialized) {
        return;
    }

    mLineVao.bind();
    glLineWidth(1.5f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(mConstraintVertices.size() / 2));
    mLineVao.release();

    mTriangulationVao.bind();
    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(mTriangulationVertices.size() / 2));
    mTriangulationVao.release();

    mVao.bind();
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, static_cast<int>(mMeshVertices.size() / 2));
    mVao.release();
}

void MeshRenderer::release() {
    mPointVbo.release();
    mLineVbo.release();
    mTriangulationVbo.release();
}

void MeshRenderer::uploadMeshVertices(const geometry::Mesh& mesh) {
    mMeshVertices.clear();
    mConstraintVertices.clear();
    mTriangulationVertices.clear();

    const auto realPoints = mesh.pointsReal();
    if (realPoints.empty()) {
        mPointVbo.bind();
        mPointVbo.allocate(nullptr, 0);
        mPointVbo.release();
        mLineVbo.bind();
        mLineVbo.allocate(nullptr, 0);
        mLineVbo.release();
        mTriangulationVbo.bind();
        mTriangulationVbo.allocate(nullptr, 0);
        mTriangulationVbo.release();
        return;
    }

    const auto boundingBox = mesh.getboundingBox();
    const double centerX = 0.5 * (boundingBox.minX + boundingBox.maxX);
    const double centerY = 0.5 * (boundingBox.minY + boundingBox.maxY);
    const double spanX = boundingBox.maxX - boundingBox.minX;
    const double spanY = boundingBox.maxY - boundingBox.minY;
    const double maxSpan = std::max(spanX, spanY);
    const double scale = maxSpan > 1e-12 ? maxSpan : 1.0;
    const auto normalizeX = [centerX, scale](double x) {
        return static_cast<float>((x - centerX) / scale) * 1.8f;
    };
    const auto normalizeY = [centerY, scale](double y) {
        return static_cast<float>((y - centerY) / scale) * 1.8f;
    };

    mMeshVertices.reserve(realPoints.size() * 2);
    for (const auto& point : realPoints) {
        const float normalizedX = normalizeX(point.x);
        const float normalizedY = normalizeY(point.y);

        mMeshVertices.push_back(normalizedX);
        mMeshVertices.push_back(normalizedY);
    }

    const auto& allPoints = mesh.points();
    const auto& constraints = mesh.constraints();
    const auto& triangles = mesh.triangles();
    mConstraintVertices.reserve(constraints.size() * 4);
    for (const auto& edge : constraints) {
        if (edge.a < 0 || edge.b < 0 || edge.a >= static_cast<int>(allPoints.size()) ||
            edge.b >= static_cast<int>(allPoints.size())) {
            continue;
        }

        const auto& a = allPoints[edge.a];
        const auto& b = allPoints[edge.b];
        if (a.isSymbolic() || b.isSymbolic()) {
            continue;
        }

        mConstraintVertices.push_back(normalizeX(a.x));
        mConstraintVertices.push_back(normalizeY(a.y));
        mConstraintVertices.push_back(normalizeX(b.x));
        mConstraintVertices.push_back(normalizeY(b.y));
    }

    std::set<std::pair<int, int>> triangulationEdges;
    for (const auto& triangle : triangles) {
        const std::array<int, 3> v = {triangle.vertices[0], triangle.vertices[1],
                                      triangle.vertices[2]};

        for (size_t i = 0; i < v.size(); ++i) {
            const int a = v[i];
            const int b = v[(i + 1) % v.size()];

            if (a < 0 || b < 0 || a >= static_cast<int>(allPoints.size()) ||
                b >= static_cast<int>(allPoints.size())) {
                continue;
            }

            const auto& pa = allPoints[a];
            const auto& pb = allPoints[b];
            if (pa.isSymbolic() || pb.isSymbolic()) {
                continue;
            }

            triangulationEdges.emplace(std::min(a, b), std::max(a, b));
        }
    }

    mTriangulationVertices.reserve(triangulationEdges.size() * 4);
    for (const auto& edge : triangulationEdges) {
        const auto& a = allPoints[edge.first];
        const auto& b = allPoints[edge.second];

        mTriangulationVertices.push_back(normalizeX(a.x));
        mTriangulationVertices.push_back(normalizeY(a.y));
        mTriangulationVertices.push_back(normalizeX(b.x));
        mTriangulationVertices.push_back(normalizeY(b.y));
    }

    mPointVbo.bind();
    mPointVbo.allocate(mMeshVertices.data(),
                       static_cast<int>(mMeshVertices.size() * sizeof(float)));
    mPointVbo.release();

    mLineVbo.bind();
    mLineVbo.allocate(mConstraintVertices.data(),
                      static_cast<int>(mConstraintVertices.size() * sizeof(float)));
    mLineVbo.release();

    mTriangulationVbo.bind();
    mTriangulationVbo.allocate(mTriangulationVertices.data(),
                               static_cast<int>(mTriangulationVertices.size() * sizeof(float)));
    mTriangulationVbo.release();
}
