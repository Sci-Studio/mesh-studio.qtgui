#pragma once

#include "../model/UIMesh.hpp"
#include "MenuBar.hpp"
#include "ViewPort.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  public slots:
    void setRenderMesh(const UIMesh& mesh);
    void setWarningMessage(const QString& warning);
    void setFileName(const QString& path);

  signals:
    void openNewFileRequest(const QString& path);
    void triangulateRequest();

  private:
    MenuBar* mMenuBar = nullptr;
    ViewPort* mViewPort = nullptr;
};
