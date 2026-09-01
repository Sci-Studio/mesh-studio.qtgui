#pragma once

#include "../model/UIMesh.hpp"
#include "../view/MainWindow.hpp"

#include <QObject>
#include <QString>

class MeshController : public QObject {
    Q_OBJECT

  public:
    explicit MeshController(UIMesh* uiMesh, MainWindow* window, QObject* parent = nullptr);

  private slots:
    void triangulate();
    void loadMesh(const QString& path);

  private:
    UIMesh* mUIMesh;
    MainWindow* mMainWindow;
};
