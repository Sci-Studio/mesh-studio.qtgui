#include "MenuBar.hpp"

#include <QFileDialog>
#include <qtmetamacros.h>

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    mFileMenu = addMenu("&File");
    auto* openAction = mFileMenu->addAction("&Open");
    connect(openAction, &QAction::triggered, this, &MenuBar::onOpenClicked);
}

void MenuBar::onOpenClicked() {
    const QString path =
        QFileDialog::getOpenFileName(this, "Open DXF", QString(), "DXF files (*.dxf)");

    if (path.isEmpty()) {
        return;
    }

    emit openNewFile(path);
}
