#pragma once

#include "geometry/Mesh.hpp"
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
    void setMesh(const geometry::Mesh& mesh);

  protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

  private:
    QColor mBackground{QColor::fromRgb(30, 30, 30)};
    geometry::Mesh mMesh;

    Shader mShader;
};
