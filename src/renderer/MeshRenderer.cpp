#include "MeshRenderer.hpp"
#include "geometry/Mesh.hpp"

#include <GL/gl.h>
#include <QDebug>

MeshRenderer::MeshRenderer() {}

MeshRenderer::~MeshRenderer() {
    destroy();
}

bool MeshRenderer::initialize() {
    if (mInitialized) {
        return true;
    }

    if (!mPointVbo.create()) {
        qWarning() << "Failed to create point vertex buffer.";
        return false;
    }
    mPointVbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    mInitialized = true;
    return true;
}

void MeshRenderer::destroy() {
    if (!mInitialized) {
        return;
    }
    mPointVbo.destroy();
    mInitialized = false;
}

void MeshRenderer::draw(const geometry::Mesh& mesh, Shader& shader) {
    if (!mInitialized) {
        return;
    }

    uploadMeshVertices(mesh);

    mPointVbo.bind();
    shader.program()->enableAttributeArray(0);
    shader.program()->setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    glPointSize(5.0f);
    glDrawArrays(GL_POINTS, 0, static_cast<int>(mMeshVertices.size() / 2));

    shader.program()->disableAttributeArray(0);
}

void MeshRenderer::release() {
    mPointVbo.release();
}

void MeshRenderer::uploadMeshVertices(const geometry::Mesh& mesh) {

    mMeshVertices = {
        -0.5f, -0.5f, // bottom-left
        0.5f,  -0.5f, // bottom-right
        0.0f,  0.5f   // top
    };
    mPointVbo.bind();

    mPointVbo.allocate(mMeshVertices.data(),
                       static_cast<int>(mMeshVertices.size() * sizeof(float)));
    mPointVbo.release();
}
