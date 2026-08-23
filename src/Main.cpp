#include <QApplication>
#include <QTimer>

#include "MainWindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    QTimer::singleShot(5, &window, [&window]() { window.setWindowState(Qt::WindowMaximized); });

    return app.exec();
}
