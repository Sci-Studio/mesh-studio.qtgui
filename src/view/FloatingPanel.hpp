#pragma once

#include <QFrame>
#include <QLabel>

class FloatingPanel : public QFrame {
    Q_OBJECT

  public:
    explicit FloatingPanel(QWidget* parent = nullptr);

  private:
    QLabel* mFileNameLabel = nullptr;
};
