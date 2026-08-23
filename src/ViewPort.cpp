#include "ViewPort.hpp"

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {
    setFixedSize(800, 600);
}

ViewPort::~ViewPort() {}

void ViewPort::initializeGL() {}

void ViewPort::resizeGL(int w, int h) {}

void ViewPort::paintGL() {}
