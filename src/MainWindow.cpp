#include "MainWindow.hpp"

#include <QAction>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    auto* fileMenu = menuBar()->addMenu("&File");
    auto* openAction = fileMenu->addAction("&Open");
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenClicked);
}

void MainWindow::onOpenClicked() {
    qDebug() << "Open clicked";
}
