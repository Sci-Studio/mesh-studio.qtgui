#include "MainWindow.hpp"

#include <QAction>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setMinimumSize(800, 600);
    setWindowTitle("MeshGenQt");

    mMenuBar = new MenuBar(this);
    setMenuBar(mMenuBar);

    mWorkspace = new QWidget(this);
    auto* workspaceLayout = new QHBoxLayout(mWorkspace);
    workspaceLayout->setContentsMargins(5, 5, 5, 5);
    workspaceLayout->setSpacing(5);

    mMeshExplorer = new MeshExplorer(mWorkspace);
    mViewPort = new ViewPort(mWorkspace);
    workspaceLayout->addWidget(mMeshExplorer, 0, Qt::AlignTop);
    workspaceLayout->addWidget(mViewPort, 1);
    setCentralWidget(mWorkspace);

    connect(mMenuBar, &MenuBar::openNewFile, this, &MainWindow::openNewFileRequest);
    connect(mViewPort, &ViewPort::triangulateRequested, this, &MainWindow::triangulateRequest);
}

void MainWindow::setRenderMesh(const UIMesh& mesh) {
    mViewPort->setMesh(mesh);
    mMeshExplorer->setPointsValueLabel(static_cast<unsigned int>(mesh.pointsReal().size()));
    mMeshExplorer->setConstraintsValueLabel(static_cast<unsigned int>(mesh.constraints().size()));
    mMeshExplorer->setTrianglesValueLabel(static_cast<unsigned int>(mesh.triangles().size()));
}

void MainWindow::setWarningMessage(const QString& warning) {
    QMessageBox::warning(this, "DXF Parsing Error", warning);
}

void MainWindow::setFileName(const QString& path) {
    mMeshExplorer->setCurrentFileName(QFileInfo(path).fileName());
}
