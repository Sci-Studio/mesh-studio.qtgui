#include "MainWindow.hpp"
#include "ViewPort.hpp"
#include "application/MenuBar.hpp"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <qobject.h>

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
    connect(mMenuBar, &MenuBar::openNewFile, this,
            [this](const QString& path) { mMeshPipeline->loadFromDxf(path); });
}
