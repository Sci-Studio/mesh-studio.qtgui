#include "ViewPort.hpp"
#include "view/ToolBox.hpp"

#include <QDebug>
#include <QVector3D>

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {
    mFloatingConfigPanel = new FloatingPanel(this);
    mToolBox = new ToolBox(this);

    connect(mToolBox, &ToolBox::onTopViewClicked, this, &ViewPort::setTopView);
    connect(mToolBox, &ToolBox::onIsoViewClicked, this, &ViewPort::setIsoView);
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

    mViewMatrix.setToIdentity();
}

void ViewPort::resizeGL(int w, int h) {
    constexpr int marginToolBox = 24;
    constexpr int marginFloatingPanel = 20;

    if (!mToolBox) {
        return;
    };

    const int xToolBox = w - marginToolBox - mToolBox->width();
    const int yToolBox = marginToolBox;

    mFloatingConfigPanel->move(marginFloatingPanel, marginFloatingPanel);
    mToolBox->move(std::max(0, xToolBox), std::max(0, yToolBox));
}

void ViewPort::paintGL() {
    glClearColor(mBackground.redF(), mBackground.greenF(), mBackground.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (mMeshUploadPending) {
        mMeshRenderer.uploadMeshVertices(mMesh);
        mMeshUploadPending = false;
    }

    QMatrix4x4 projection;

    const float aspect =
        height() > 0 ? static_cast<float>(width()) / static_cast<float>(height()) : 1.0f;

    if (aspect >= 1.0f) {
        projection.ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    } else {
        projection.ortho(-1.0f, 1.0f, -1.0f / aspect, 1.0f / aspect, -1.0f, 1.0f);
    }
    QMatrix4x4 mvp = projection * mViewMatrix;

    mShader.bind();
    mShader.program()->setUniformValue("uColor", QVector3D(0.90f, 0.90f, 0.90f));

    mShader.program()->setUniformValue("uMVP", mvp);

    mMeshRenderer.draw();

    mMeshRenderer.release();
    mShader.release();
}

void ViewPort::setBackgroundColor(const QColor& color) {
    mBackground = color;
    update();
}

void ViewPort::setCurrentFileName(const QString& fileName) {
    if (mFloatingConfigPanel == nullptr) {
        return;
    }

    mFloatingConfigPanel->setFileName(fileName);
}

void ViewPort::setMesh(const geometry::Mesh& mesh) {
    mMesh = mesh;
    qDebug() << "ViewPort mesh updated. points:" << mMesh.points().size()
             << "constraints:" << mMesh.constraints().size();
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
