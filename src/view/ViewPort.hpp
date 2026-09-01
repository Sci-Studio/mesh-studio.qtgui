#pragma once

#include "../renderer/MeshRenderer.hpp"
#include "../renderer/Shader.hpp"
#include "FloatingPanel.hpp"
#include "ToolBox.hpp"
#include "geometry/Mesh.hpp"

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class ViewPort : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

  public:
    explicit ViewPort(QWidget* parent = nullptr);
    ~ViewPort();

    void setBackgroundColor(const QColor& color);
    void setCurrentFileName(const QString& fileName);

  protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

  public:
    void setMesh(const geometry::Mesh& mesh);

  signals:
    void triangulateRequested();

  private slots:
    void setTopView();
    void setIsoView();

  private:
    QColor mBackground{QColor::fromRgb(30, 30, 30)};
    geometry::Mesh mMesh;
    bool mMeshUploadPending = true;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mProjectionMatrix;

    Shader mShader;
    MeshRenderer mMeshRenderer;
    FloatingPanel* mFloatingConfigPanel = nullptr;
    ToolBox* mToolBox = nullptr;

    void setProjectionMatrix();
};
