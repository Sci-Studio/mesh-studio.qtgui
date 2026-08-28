#pragma once

#include <QApplication>

class Theme {

  public:
    static void apply(QApplication& app);

  private:
    static QString loadStyleSheet(const QString& path);
};
