#pragma once

#include <QFrame>
#include <QLabel>

class FloatingPanel : public QFrame {
    Q_OBJECT

  public:
    explicit FloatingPanel(QWidget* parent = nullptr);
    void setFileName(const QString& fileName);

  private:
    QLabel* mFileNameLabel = nullptr;
};
