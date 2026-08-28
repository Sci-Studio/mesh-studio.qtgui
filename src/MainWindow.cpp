#include "MainWindow.hpp"
#include "ViewPort.hpp"

#include <QAction>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    mViewPort = new ViewPort(this);
    setCentralWidget(mViewPort);
    mMeshPipeline = new MeshPipeline(this);

    connect(mMeshPipeline, &MeshPipeline::meshUpdated, this,
            [this]() { mViewPort->setMesh(mMeshPipeline->mesh()); });

    connect(mMeshPipeline, &MeshPipeline::loadFailed, this, [this](const QString& message) {
        QMessageBox::warning(this, "DXF Parsing Error", message);
    });

    mMenuBar = new MenuBar(this);
    setMenuBar(mMenuBar);
    connect(mMenuBar, &MenuBar::openNewFile, this, [this](const QString& path) {
        mViewPort->setCurrentFileName(QFileInfo(path).fileName());
        mMeshPipeline->loadFromDxf(path);
    });
}
