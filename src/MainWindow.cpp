#include "MainWindow.hpp"
#include "geometry/Mesh.hpp"
#include "parser/DxfParser.hpp"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    auto* fileMenu = menuBar()->addMenu("&File");
    auto* openAction = fileMenu->addAction("&Open");
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
