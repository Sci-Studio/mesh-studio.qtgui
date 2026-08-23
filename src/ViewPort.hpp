#pragma once

#include <QOpenGLWidget>

class ViewPort : public QOpenGLWidget {
    Q_OBJECT

  public:
    explicit ViewPort(QWidget* parent = nullptr);
    ~ViewPort();

  protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};
