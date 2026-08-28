#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QTimer>

#include "MainWindow.hpp"
#include "utils/Theme.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Theme::apply(app);

    MainWindow window;
    window.show();

    QTimer::singleShot(5, &window, [&window]() { window.setWindowState(Qt::WindowMaximized); });

    return app.exec();
}
