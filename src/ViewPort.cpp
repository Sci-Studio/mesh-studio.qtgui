#include "ViewPort.hpp"
#include <QDebug>
#include <QVector3D>

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {
}

ViewPort::~ViewPort() {
    makeCurrent();
    mMeshRenderer.destroy();
    mShader.release();
    doneCurrent();
}

void ViewPort::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);

    if (!mShader.loadFromFiles(":/shaders/mesh.vertex", ":/shaders/mesh.fragment")) {
        qWarning() << "Unable to load mesh shaders.";
    }

    if (!mMeshRenderer.initialize(mShader)) {
        qWarning() << "Unable to initialize mesh renderer.";
    }
}

void ViewPort::resizeGL(int w, int h) {}

void ViewPort::paintGL() {
    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (mMeshUploadPending) {
        mMeshRenderer.uploadMeshVertices(mMesh);
        mMeshUploadPending = false;
    }

    mShader.bind();
    mShader.program()->setUniformValue("uColor", QVector3D(0.90f, 0.90f, 0.90f));

    mMeshRenderer.draw();

    mMeshRenderer.release();
    mShader.release();
}

void ViewPort::setBackgroundColor(const QColor& color) {
    mBackground = color;
    update();
}

void ViewPort::setMesh(const geometry::Mesh& mesh) {
    mMesh = mesh;
    qDebug() << "ViewPort mesh updated. points:" << mMesh.points.size()
             << "constraints:" << mMesh.constraints.size();
    mMeshUploadPending = true;
    update();
}
