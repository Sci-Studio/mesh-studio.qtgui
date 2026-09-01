#include "MeshController.hpp"

#include "parser/DxfParser.hpp"

#include <utility>

bool triangulate(geometry::Mesh& mesh);

MeshController::MeshController(geometry::Mesh* mesh, MainWindow* window, QObject* parent)
    : QObject(parent), mMesh(mesh), mMainWindow(window) {

    connect(mMainWindow, &MainWindow::openNewFileRequest, this, &MeshController::loadMesh);
    connect(mMainWindow, &MainWindow::triangulateRequest, this, &MeshController::triangulate);
}

void MeshController::loadMesh(const QString& path) {
    if (mMesh == nullptr) {
        mMainWindow->setWarningMessage("Mesh controller is not initialized.");
        return;
    }

    parser::dxf::DxfParser parser;
    geometry::Mesh nextMesh;

    if (!parser.loadMesh(path.toUtf8().constData(), nextMesh)) {
        mMainWindow->setWarningMessage(QStringLiteral("Failed to parse %1").arg(path));
        return;
    }

    *mMesh = std::move(nextMesh);
    mMainWindow->setRenderMesh(*mMesh);
    return;
}

void MeshController::triangulate() {
    if (mMesh == nullptr) {
        mMainWindow->setWarningMessage("Mesh controller is not initialized.");
        return;
    }

    if (mMesh->pointsReal().empty()) {
        mMainWindow->setWarningMessage("Load a DXF file before triangulation.");
        return;
    }

    if (!::triangulate(*mMesh)) {
        mMainWindow->setWarningMessage("Triangulation failed.");
        return;
    }

    mMainWindow->setRenderMesh(*mMesh);
}
