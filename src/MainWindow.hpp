#pragma once

#include "MeshPipeline.hpp"
#include "ViewPort.hpp"
#include "view/MenuBar.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private:
    MenuBar* mMenuBar = nullptr;
    ViewPort* mViewPort = nullptr;
    MeshPipeline* mMeshPipeline = nullptr;
};
