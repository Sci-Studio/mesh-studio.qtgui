#include "MeshPipeline.hpp"

#include "geometry/Mesh.hpp"
#include "parser/DxfParser.hpp"

#include <utility>

bool triangulate(geometry::Mesh& mesh);

MeshPipeline::MeshPipeline(QObject* parent) : QObject(parent) {}

bool MeshPipeline::loadFromDxf(const QString& path) {
    parser::dxf::DxfParser parser;
    geometry::Mesh nextMesh;

    if (!parser.loadMesh(path.toUtf8().constData(), nextMesh)) {
        emit loadFailed(QStringLiteral("Failed to parse %1").arg(path));
        return false;
    }

    mMesh = std::move(nextMesh);
    emit meshUpdated();
    return true;
}

const geometry::Mesh& MeshPipeline::mesh() const {
    return mMesh;
}

bool MeshPipeline::triangulate() {
    if (mMesh.pointsReal().empty()) {
        emit triangulationFailed(QStringLiteral("Load a DXF file before triangulation."));
        return false;
    }

    if (!::triangulate(mMesh)) {
        emit triangulationFailed(QStringLiteral("Triangulation failed."));
        return false;
    }

    emit meshUpdated();
    return true;
}
