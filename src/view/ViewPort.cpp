#include "ViewPort.hpp"
#include "../utils/Shader.hpp"

#include <QDebug>
#include <QPainterPath>
#include <QRegion>
#include <QVector3D>
#include <algorithm>

ViewPort::ViewPort(QWidget* parent) : QOpenGLWidget(parent) {
    setObjectName("ms-view-port");
    setAttribute(Qt::WA_StyledBackground, true);

    mToolBar = new ToolBar(this);
    mRotateControls = new RotateControls(this);
    mAxisIndicator = new AxisIndicator(this);
    mToolBar->setGridEnabled(mGridVisible);
    mToolBar->setTriangulateEnabled(false);
    mAxisIndicator->setRotationDegrees(mModelRotationDegrees);

    connect(mToolBar, &ToolBar::triangulateClicked, this, [this]() { emit triangulateRequested(); });
    connect(mToolBar, &ToolBar::gridToggled, this, &ViewPort::setGridVisible);
    connect(mRotateControls, &RotateControls::rotateCcwClicked, this, &ViewPort::rotateModelCcw);
    connect(mRotateControls, &RotateControls::rotateCwClicked, this, &ViewPort::rotateModelCw);
}

ViewPort::~ViewPort() {
    makeCurrent();
    destroyGrid();
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
    initializeGrid();

    mViewMatrix.setToIdentity();
    setProjectionMatrix();
}

void ViewPort::resizeGL(int w, int h) {
    constexpr int marginToolBar = 11;
    constexpr int marginRotateControls = 15;
    constexpr int marginAxisLeft = 12;
    constexpr int marginAxisBottom = 20;

    if (mToolBar != nullptr) {
        mToolBar->move(marginToolBar, marginToolBar);
    }
    if (mRotateControls != nullptr) {
        const int xRotateControls = w - marginRotateControls - mRotateControls->width();
        const int yRotateControls = marginRotateControls;
        mRotateControls->move(std::max(0, xRotateControls), std::max(0, yRotateControls));
    }
    if (mAxisIndicator != nullptr) {
        const int xAxis = marginAxisLeft;
        const int yAxis = h - marginAxisBottom - mAxisIndicator->height();
        mAxisIndicator->move(std::max(0, xAxis), std::max(0, yAxis));
    }
    applyRoundedMask();

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

    mProgram.bind();
    // Keep the grid anchored in world space while only rotating the model.
    mProgram.setUniformValue("uMVP", mProjectionMatrix);
    drawGrid();

    QMatrix4x4 mvp = mProjectionMatrix * mViewMatrix;
    mProgram.setUniformValue("uMVP", mvp);
    mProgram.setUniformValue("uColor", QVector3D(0.90f, 0.90f, 0.90f));
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
    updateToolbarStates();
    update();
}

void ViewPort::rotateModelCcw() {
    mViewMatrix.rotate(90.0f, QVector3D(0.0f, 0.0f, 1.0f));
    mModelRotationDegrees += 90.0f;
    if (mAxisIndicator != nullptr) {
        mAxisIndicator->setRotationDegrees(mModelRotationDegrees);
    }
    update();
}

void ViewPort::rotateModelCw() {
    mViewMatrix.rotate(-90.0f, QVector3D(0.0f, 0.0f, 1.0f));
    mModelRotationDegrees -= 90.0f;
    if (mAxisIndicator != nullptr) {
        mAxisIndicator->setRotationDegrees(mModelRotationDegrees);
    }
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

void ViewPort::setGridVisible(bool visible) {
    mGridVisible = visible;
    update();
}

void ViewPort::initializeGrid() {
    if (mGridInitialized) {
        return;
    }

    if (!mGridVao.create()) {
        qWarning() << "Failed to create grid vertex array object.";
        return;
    }
    if (!mGridVbo.create()) {
        qWarning() << "Failed to create grid vertex buffer.";
        mGridVao.destroy();
        return;
    }
    mGridVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    mGridVertices.clear();
    constexpr float kHalfExtent = 1.8f;
    constexpr float kStep = 0.1f;
    for (float x = -kHalfExtent; x <= kHalfExtent + 1e-4f; x += kStep) {
        mGridVertices.push_back(x);
        mGridVertices.push_back(-kHalfExtent);
        mGridVertices.push_back(x);
        mGridVertices.push_back(kHalfExtent);
    }
    for (float y = -kHalfExtent; y <= kHalfExtent + 1e-4f; y += kStep) {
        mGridVertices.push_back(-kHalfExtent);
        mGridVertices.push_back(y);
        mGridVertices.push_back(kHalfExtent);
        mGridVertices.push_back(y);
    }

    mGridVao.bind();
    mGridVbo.bind();
    mGridVbo.allocate(mGridVertices.data(), static_cast<int>(mGridVertices.size() * sizeof(float)));
    mProgram.enableAttributeArray(0);
    mProgram.setAttributeBuffer(0, GL_FLOAT, 0, 2, 2 * sizeof(float));
    mGridVbo.release();
    mGridVao.release();

    mGridInitialized = true;
}

void ViewPort::drawGrid() {
    if (!mGridVisible || !mGridInitialized) {
        return;
    }
    mProgram.setUniformValue("uColor", QVector3D(0.22f, 0.23f, 0.24f));
    mGridVao.bind();
    glLineWidth(1.0f);
    glDrawArrays(GL_LINES, 0, static_cast<int>(mGridVertices.size() / 2));
    mGridVao.release();
}

void ViewPort::destroyGrid() {
    if (!mGridInitialized) {
        return;
    }
    mGridVao.destroy();
    mGridVbo.destroy();
    mGridVertices.clear();
    mGridInitialized = false;
}

void ViewPort::applyRoundedMask() {
    if (width() <= 0 || height() <= 0) {
        clearMask();
        return;
    }

    constexpr qreal kCornerRadius = 8.0;
    QRectF roundedRect = rect();
    roundedRect.adjust(0.5, 0.5, -0.5, -0.5);

    QPainterPath clipPath;
    clipPath.addRoundedRect(roundedRect, kCornerRadius, kCornerRadius);
    setMask(QRegion(clipPath.toFillPolygon().toPolygon()));
}

void ViewPort::updateToolbarStates() {
    if (mToolBar == nullptr) {
        return;
    }
    const bool hasMesh = !mUIMesh.pointsReal().empty();
    const bool alreadyTriangulated = !mUIMesh.triangles().empty();
    mToolBar->setTriangulateEnabled(hasMesh && !alreadyTriangulated);
}
