#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QTimer>

#include "MainWindow.hpp"

QString readResourceText(const QString& resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }
    QTextStream stream(&file);
    return stream.readAll();
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    const QString styleSheet =
        readResourceText(":/styles/tokens.qss") + "\n" + readResourceText(":/styles/app.qss");
    if (!styleSheet.isEmpty()) {
        app.setStyleSheet(styleSheet);
    }

    MainWindow window;
    window.show();

    QTimer::singleShot(5, &window, [&window]() { window.setWindowState(Qt::WindowMaximized); });

    return app.exec();
}
