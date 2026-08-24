#include "ViewPort.hpp"
#include <QDebug>

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {}

ViewPort::~ViewPort() {}

void ViewPort::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);

    if (!mShader.loadFromFiles(":/shaders/mesh.vertex")) {
        qWarning() << "Unable to load mesh vertex shader.";
    }
}

void ViewPort::resizeGL(int w, int h) {}

void ViewPort::paintGL() {
    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ViewPort::setBackgroundColor(const QColor& color) {
    mBackground = color;
    update();
}

void ViewPort::setMesh(const geometry::Mesh& mesh) {
    mMesh = mesh;
    qDebug() << "ViewPort mesh updated. points:" << mMesh.points.size()
             << "constraints:" << mMesh.constraints.size();
    update();
}
