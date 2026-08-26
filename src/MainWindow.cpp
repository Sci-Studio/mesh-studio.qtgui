#include "MainWindow.hpp"
#include "ViewPort.hpp"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    mViewPort = new ViewPort(this);
    setCentralWidget(mViewPort);
    mMeshPipeline = new MeshPipeline(this);

    connect(mMeshPipeline, &MeshPipeline::meshUpdated, this, [this]() {
        const geometry::Mesh& mesh = mMeshPipeline->mesh();
        mViewPort->setMesh(mesh);
        qDebug() << "points:" << mesh.points.size() << "constraints:" << mesh.constraints.size();
    });

    connect(mMeshPipeline, &MeshPipeline::loadFailed, this, [this](const QString& message) {
        QMessageBox::warning(this, "DXF Parsing Error", message);
    });

    mFileMenu = menuBar()->addMenu("&File");
    auto* openAction = mFileMenu->addAction("&Open");
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenClicked);
}

void MainWindow::onOpenClicked() {
    const QString path =
        QFileDialog::getOpenFileName(this, "Open DXF", QString(), "DXF files (*.dxf)");

    if (path.isEmpty()) {
        return;
    }

    mMeshPipeline->loadFromDxf(path);
}
