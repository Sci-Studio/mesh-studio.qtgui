#include "PreferencesPopup.hpp"

#include <QDialogButtonBox>
#include <QLabel>
#include <QVBoxLayout>

PreferencesPopup::PreferencesPopup(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Preferences");
    setModal(true);
    setFixedSize(420, 240);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(12);

    auto* description =
        new QLabel("Preferences dialog placeholder.\nSettings UI will be added later.");
    description->setWordWrap(true);
    layout->addWidget(description);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    layout->addWidget(buttons);
}
