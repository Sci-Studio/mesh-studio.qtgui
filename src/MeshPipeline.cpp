#include "MeshPipeline.hpp"

#include "parser/DxfParser.hpp"

#include <utility>

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
