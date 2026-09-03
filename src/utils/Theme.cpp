#include "Theme.hpp"

#include <QFile>
#include <QIODevice>
#include <QTextStream>

QString Theme::loadStyleSheet(const QString& resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return {};
    }
    QTextStream stream(&file);
    return stream.readAll();
}

void Theme::apply(QApplication& app) {
    const QStringList styleFiles = {":/styles/tokens.qss", ":/styles/app.qss",
                                    ":/styles/ToolBox.qss", ":/styles/ToolBar.qss",
                                    ":/styles/MeshExplorer.qss"};

    QString styleSheet;

    for (const auto& file : styleFiles) {
        styleSheet += loadStyleSheet(file);
        styleSheet += '\n';
    }

    if (!styleSheet.isEmpty()) {
        app.setStyleSheet(styleSheet);
    }
}
