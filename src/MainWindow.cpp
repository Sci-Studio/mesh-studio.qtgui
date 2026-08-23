#include "MainWindow.hpp"
#include "ViewPort.hpp"
#include "geometry/Mesh.hpp"
#include "parser/DxfParser.hpp"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    mViewPort = new ViewPort(this);

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

    geometry::Mesh mesh;
    parser::dxf::DxfParser parser;

    if (!parser.loadMesh(path.toUtf8().constData(), mesh)) {
        qWarning() << "Failed to parse" << path;
    }

    qDebug() << "points:" << mesh.points.size() << "constraints:" << mesh.constraints.size();
}
