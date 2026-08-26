#pragma once

#include "geometry/Mesh.hpp"
#include "renderer/MeshRenderer.hpp"
#include "renderer/Shader.hpp"

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

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

  public slots:
    void setMesh(const geometry::Mesh& mesh);

  signals:
    void uploadMesh(const geometry::Mesh& mesh);

  private:
    QColor mBackground{QColor::fromRgb(30, 30, 30)};
    geometry::Mesh mMesh;

    Shader mShader;
    MeshRenderer mMeshRenderer;
};
