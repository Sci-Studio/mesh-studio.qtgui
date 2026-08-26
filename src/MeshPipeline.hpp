#pragma once

#include "geometry/Mesh.hpp"

#include <QObject>
#include <QString>

class MeshPipeline : public QObject {
    Q_OBJECT

  public:
    explicit MeshPipeline(QObject* parent = nullptr);

    bool loadFromDxf(const QString& path);
    const geometry::Mesh& mesh() const;

  signals:
    void meshUpdated();
    void loadFailed(const QString& message);

  private:
    geometry::Mesh mMesh;
};
