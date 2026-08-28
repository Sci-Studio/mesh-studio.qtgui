#include "MenuBar.hpp"
#include "PreferencesPopup.hpp"

#include <QFileDialog>

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    mFileMenu = addMenu("&File");
    auto* openAction = mFileMenu->addAction("&Open");
    connect(openAction, &QAction::triggered, this, &MenuBar::onOpenClicked);

    mEditMenu = addMenu("&Edit");
    auto* preferencesAction = mEditMenu->addAction("&Preferences");
    connect(preferencesAction, &QAction::triggered, this, &MenuBar::onPreferencesClicked);
}

void MenuBar::onOpenClicked() {
    const QString path =
        QFileDialog::getOpenFileName(this, "Open DXF", QString(), "DXF files (*.dxf)");

    if (path.isEmpty()) {
        return;
    }

    emit openNewFile(path);
}

void MenuBar::onPreferencesClicked() {
    PreferencesPopup preferencesPopup(this);
    preferencesPopup.exec();
}
