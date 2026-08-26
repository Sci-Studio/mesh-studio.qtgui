#pragma once

#include "MeshPipeline.hpp"
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
    QMenu* mFileMenu = nullptr;
    ViewPort* mViewPort = nullptr;
    MeshPipeline* mMeshPipeline = nullptr;
};
