#include "MeshController.hpp"
#include "parser/DxfParser.hpp"

#include <utility>

bool triangulate(geometry::Mesh& mesh);

MeshController::MeshController(UIMesh& uiMesh, MainWindow& window, QObject* parent)
    : QObject(parent), mUIMesh(uiMesh), mMainWindow(window) {

    connect(&mMainWindow, &MainWindow::openNewFileRequest, this, &MeshController::loadMesh);
    connect(&mMainWindow, &MainWindow::triangulateRequest, this, &MeshController::triangulate);
}

void MeshController::loadMesh(const QString& path) {
    parser::dxf::DxfParser parser;
    geometry::Mesh nextMesh;

    if (!parser.loadMesh(path.toUtf8().constData(), nextMesh)) {
        mMainWindow.setWarningMessage(QStringLiteral("Failed to parse %1").arg(path));
        return;
    }

    mUIMesh.setFromMesh(std::move(nextMesh));
    mMainWindow.setRenderMesh(mUIMesh);
    return;
}

void MeshController::triangulate() {
    if (mUIMesh.pointsReal().empty()) {
        mMainWindow.setWarningMessage("Load a DXF file before triangulation.");
        return;
    }

    if (!::triangulate(mUIMesh)) {
        mMainWindow.setWarningMessage("Triangulation failed.");
        return;
    }

    mMainWindow.setRenderMesh(mUIMesh);
}
