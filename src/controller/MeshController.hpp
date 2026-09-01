#pragma once

#include "../view/MainWindow.hpp"
#include "geometry/Mesh.hpp"

#include <QObject>
#include <QString>

class MeshController : public QObject {
    Q_OBJECT

  public:
    explicit MeshController(geometry::Mesh* mesh, MainWindow* window, QObject* parent = nullptr);

  private slots:
    void triangulate();
    void loadMesh(const QString& path);

  private:
    geometry::Mesh* mMesh;
    MainWindow* mMainWindow;
};
