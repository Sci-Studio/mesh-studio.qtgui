#include "MainWindow.hpp"

#include <QAction>
#include <QFileInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    mViewPort = new ViewPort(this);
    setCentralWidget(mViewPort);

    mMenuBar = new MenuBar(this);
    setMenuBar(mMenuBar);

    connect(mMenuBar, &MenuBar::openNewFile, this, [this](const QString& path) {
        mViewPort->setCurrentFileName(QFileInfo(path).fileName());
        emit openNewFileRequest(path);
    });
    connect(mViewPort, &ViewPort::triangulateRequested, this, &MainWindow::triangulateRequest);
}

void MainWindow::setRenderMesh(const UIMesh& mesh) {
    mViewPort->setMesh(mesh);
}

void MainWindow::setWarningMessage(const QString& warning) {
    QMessageBox::warning(this, "DXF Parsing Error", warning);
}
