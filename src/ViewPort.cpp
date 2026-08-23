#include "ViewPort.hpp"

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {
    setFixedSize(800, 600);
}

ViewPort::~ViewPort() {}

void ViewPort::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
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
