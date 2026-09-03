#pragma once

#include "../model/UIMesh.hpp"
#include "MeshRenderer.hpp"
#include "RotateControls.hpp"
#include "ToolBar.hpp"

#include <QColor>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QRegion>
#include <vector>

class ViewPort : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

  public:
    explicit ViewPort(QWidget* parent = nullptr);
    ~ViewPort();

    void setBackgroundColor(const QColor& color);

  protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

  public:
    void setMesh(const UIMesh& mesh);

  signals:
    void triangulateRequested();

  private slots:
    void rotateModelCcw();
    void rotateModelCw();
    void setGridVisible(bool visible);

  private:
    QColor mBackground{QColor::fromRgb(30, 30, 30)};
    UIMesh mUIMesh;
    bool mMeshUploadPending = true;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mProjectionMatrix;

    QOpenGLShaderProgram mProgram;
    MeshRenderer mMeshRenderer;
    ToolBar* mToolBar = nullptr;
    RotateControls* mRotateControls = nullptr;
    bool mGridVisible = true;
    bool mGridInitialized = false;
    std::vector<float> mGridVertices;
    QOpenGLVertexArrayObject mGridVao;
    QOpenGLBuffer mGridVbo{QOpenGLBuffer::VertexBuffer};

    void setProjectionMatrix();
    void initializeGrid();
    void destroyGrid();
    void drawGrid();
    void applyRoundedMask();
    void updateToolbarStates();
};
