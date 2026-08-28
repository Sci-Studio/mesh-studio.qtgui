#pragma once

#include <QMenuBar>

class MenuBar : public QMenuBar {
    Q_OBJECT

  public:
    explicit MenuBar(QWidget* parent = nullptr);

  signals:
    void openNewFile(const QString& path);

  private slots:
    void onOpenClicked();

  private:
    QMenu* mFileMenu = nullptr;
};
