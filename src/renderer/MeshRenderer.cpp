#include "MeshRenderer.hpp"

#include <QDebug>
#include <algorithm>

MeshRenderer::MeshRenderer() {}

MeshRenderer::~MeshRenderer() {
    destroy();
}

bool MeshRenderer::initialize(Shader& shader) {
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

    if (!mPointVbo.create()) {
        qWarning() << "Failed to create point vertex buffer.";
        mVao.destroy();
        mLineVao.destroy();
        return false;
    }
    if (!mLineVbo.create()) {
        qWarning() << "Failed to create line vertex buffer.";
        mPointVbo.destroy();
        mVao.destroy();
        mLineVao.destroy();
        return false;
    }
    mPointVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mLineVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    mVao.bind();
    shader.bind();
    mPointVbo.bind();

    shader.program()->enableAttributeArray(0);
    shader.program()->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));

    mPointVbo.release();

    mLineVao.bind();
    mLineVbo.bind();
    shader.program()->enableAttributeArray(0);
    shader.program()->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));

    mLineVbo.release();
    shader.release();
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
    mPointVbo.destroy();
    mLineVbo.destroy();
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

    mVao.bind();
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, static_cast<int>(mMeshVertices.size() / 2));
    mVao.release();
}

void MeshRenderer::release() {
    mPointVbo.release();
    mLineVbo.release();
}

void MeshRenderer::uploadMeshVertices(const geometry::Mesh& mesh) {
    mMeshVertices.clear();
    mConstraintVertices.clear();

    const auto realPoints = mesh.pointsReal();
    if (realPoints.empty()) {
        mPointVbo.bind();
        mPointVbo.allocate(nullptr, 0);
        mPointVbo.release();
        mLineVbo.bind();
        mLineVbo.allocate(nullptr, 0);
        mLineVbo.release();
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

    mPointVbo.bind();
    mPointVbo.allocate(mMeshVertices.data(),
                       static_cast<int>(mMeshVertices.size() * sizeof(float)));
    mPointVbo.release();

    mLineVbo.bind();
    mLineVbo.allocate(mConstraintVertices.data(),
                      static_cast<int>(mConstraintVertices.size() * sizeof(float)));
    mLineVbo.release();
}
