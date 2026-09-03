#pragma once

#include <QFrame>

class QFrame;
class QToolButton;

class RotateControls : public QFrame {
    Q_OBJECT

  public:
    explicit RotateControls(QWidget* parent = nullptr);

  signals:
    void rotateCcwClicked();
    void rotateCwClicked();

  private:
    QFrame* mGripHandle = nullptr;
    QToolButton* mRotateCcwButton = nullptr;
    QToolButton* mRotateCwButton = nullptr;
};
