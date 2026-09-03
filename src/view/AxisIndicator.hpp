#pragma once

#include <QWidget>

class AxisIndicator : public QWidget {
    Q_OBJECT

  public:
    explicit AxisIndicator(QWidget* parent = nullptr);

    void setRotationDegrees(float rotationDegrees);

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    float mRotationDegrees = 0.0f;
};
