#include "MeshRenderer.hpp"
#include "Shader.hpp"
#include "geometry/Mesh.hpp"

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

    if (!mPointVbo.create()) {
        qWarning() << "Failed to create point vertex buffer.";
        mVao.destroy();
        return false;
    }
    mPointVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    mVao.bind();
    shader.bind();
    mPointVbo.bind();

    shader.program()->enableAttributeArray(0);
    shader.program()->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));

    mPointVbo.release();
    shader.release();
    mVao.release();

    mInitialized = true;
    return true;
}

void MeshRenderer::destroy() {
    if (!mInitialized) {
        return;
    }
    mVao.destroy();
    mPointVbo.destroy();
    mInitialized = false;
}

void MeshRenderer::draw() {
    if (!mInitialized) {
        return;
    }

    mVao.bind();
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, static_cast<int>(mMeshVertices.size() / 2));
    mVao.release();
}

void MeshRenderer::release() {
    mPointVbo.release();
}

void MeshRenderer::uploadMeshVertices(const geometry::Mesh& mesh) {
    mMeshVertices.clear();

    double minX = 0.0;
    double maxX = 0.0;
    double minY = 0.0;
    double maxY = 0.0;
    bool hasPoint = false;

    for (const auto& point : mesh.points) {
        if (point.isSymbolic()) {
            continue;
        }

        if (!hasPoint) {
            minX = maxX = point.x;
            minY = maxY = point.y;
            hasPoint = true;
            continue;
        }

        minX = std::min(minX, point.x);
        maxX = std::max(maxX, point.x);
        minY = std::min(minY, point.y);
        maxY = std::max(maxY, point.y);
    }

    if (!hasPoint) {
        mPointVbo.bind();
        mPointVbo.allocate(nullptr, 0);
        mPointVbo.release();
        return;
    }

    const double centerX = 0.5 * (minX + maxX);
    const double centerY = 0.5 * (minY + maxY);
    const double spanX = maxX - minX;
    const double spanY = maxY - minY;
    const double maxSpan = std::max(spanX, spanY);
    const double scale = maxSpan > 1e-12 ? maxSpan : 1.0;

    mMeshVertices.reserve(mesh.points.size() * 2);
    for (const auto& point : mesh.points) {
        if (point.isSymbolic()) {
            continue;
        }

        const float normalizedX = static_cast<float>((point.x - centerX) / scale) * 1.8f;
        const float normalizedY = static_cast<float>((point.y - centerY) / scale) * 1.8f;

        mMeshVertices.push_back(normalizedX);
        mMeshVertices.push_back(normalizedY);
    }

    mPointVbo.bind();
    mPointVbo.allocate(mMeshVertices.data(),
                       static_cast<int>(mMeshVertices.size() * sizeof(float)));
    mPointVbo.release();
}
