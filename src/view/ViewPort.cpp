#include "ViewPort.hpp"
#include "../utils/Shader.hpp"

#include <QDebug>
#include <QVector3D>

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {
    mToolBox = new ToolBox(this);

    connect(mToolBox, &ToolBox::onTopViewClicked, this, &ViewPort::setTopView);
    connect(mToolBox, &ToolBox::onIsoViewClicked, this, &ViewPort::setIsoView);
    connect(mToolBox, &ToolBox::onTriangulateClicked, this,
            [this]() { emit triangulateRequested(); });
}

ViewPort::~ViewPort() {
    makeCurrent();
    mMeshRenderer.destroy();
    mProgram.release();
    doneCurrent();
}

void ViewPort::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);

    if (!Shader::loadFromFiles(":/shaders/mesh.vertex", ":/shaders/mesh.fragment", mProgram)) {
        qWarning() << "Unable to load mesh shaders.";
    }

    if (!mMeshRenderer.initialize(mProgram)) {
        qWarning() << "Unable to initialize mesh renderer.";
    }

    setTopView();
    setProjectionMatrix();
}

void ViewPort::resizeGL(int w, int h) {
    constexpr int marginToolBox = 24;
    constexpr int marginFloatingPanel = 20;

    if (!mToolBox) {
        return;
    };

    const int xToolBox = w - marginToolBox - mToolBox->width();
    const int yToolBox = marginToolBox;

    mToolBox->move(std::max(0, xToolBox), std::max(0, yToolBox));

    setProjectionMatrix();
    update();
}

void ViewPort::paintGL() {
    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (mMeshUploadPending) {
        mMeshRenderer.uploadMeshVertices(mUIMesh);
        mMeshUploadPending = false;
    }

    QMatrix4x4 mvp = mProjectionMatrix * mViewMatrix;

    mProgram.bind();
    mProgram.setUniformValue("uColor", QVector3D(0.90f, 0.90f, 0.90f));

    mProgram.setUniformValue("uMVP", mvp);

    mMeshRenderer.draw();

    mMeshRenderer.release();
    mProgram.release();
}

void ViewPort::setBackgroundColor(const QColor& color) {
    mBackground = color;
    update();
}

void ViewPort::setMesh(const UIMesh& uiMesh) {
    mUIMesh = uiMesh;
    qDebug() << "ViewPort mesh updated. points:" << mUIMesh.points().size()
             << "constraints:" << mUIMesh.constraints().size();
    mMeshUploadPending = true;
    update();
}

void ViewPort::setTopView() {
    mViewMatrix.setToIdentity();
    update();
}

void ViewPort::setIsoView() {
    mViewMatrix.setToIdentity();
    // For a flat XY sketch (z=0), a FreeCAD-like isometric look is best
    // approximated by in-plane spin + tilt instead of pure X/Y yaw-pitch.
    mViewMatrix.rotate(-45.0f, QVector3D(0.0f, 0.0f, 1.0f));
    mViewMatrix.rotate(54.7356f, QVector3D(1.0f, 0.0f, 0.0f));
    update();
}

void ViewPort::setProjectionMatrix() {
    mProjectionMatrix.setToIdentity();
    const float aspect =
        height() > 0 ? static_cast<float>(width()) / static_cast<float>(height()) : 1.0f;

    if (aspect >= 1.0f) {
        mProjectionMatrix.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
        mProjectionMatrix.ortho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
    }
}
