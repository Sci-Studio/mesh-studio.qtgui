#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <qmenu.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private slots:
    void onOpenClicked();

  private:
    QMenu* mFileMenu;
};
