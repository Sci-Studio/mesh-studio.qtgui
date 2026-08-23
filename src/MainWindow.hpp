#pragma once

#include "ViewPort.hpp"

#include <QMainWindow>
#include <QMenuBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private slots:
    void onOpenClicked();

  private:
    QMenu* mFileMenu;
    ViewPort* mViewPort;
};
