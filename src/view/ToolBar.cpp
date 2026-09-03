#include "ToolBar.hpp"

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVBoxLayout>

ToolBar::ToolBar(QWidget* parent) : QFrame(parent) {
    setObjectName("ms-viewport-toolbar");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedSize(48, 82);

    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(6, 6, 6, 6);
    rootLayout->setSpacing(4);

    mTriangulateButton = new QToolButton(this);
    mTriangulateButton->setObjectName("ms-viewport-toolbar-triangulate");
    mTriangulateButton->setFixedSize(36, 36);
    mTriangulateButton->setIcon(QIcon(":/svg/Triangulate_24.svg"));
    mTriangulateButton->setIconSize(QSize(20, 20));
    mTriangulateButton->setToolTip("Triangulate mesh");
    mTriangulateButton->setAutoRaise(true);
    rootLayout->addWidget(mTriangulateButton, 0, Qt::AlignCenter);

    auto* divider = new QFrame(this);
    divider->setObjectName("ms-viewport-toolbar-divider");
    divider->setFixedHeight(1);
    divider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rootLayout->addWidget(divider);

    mGridToggleButton = new QToolButton(this);
    mGridToggleButton->setObjectName("ms-viewport-toolbar-grid");
    mGridToggleButton->setFixedSize(36, 36);
    mGridToggleButton->setIcon(QIcon(":/svg/Grid_24.svg"));
    mGridToggleButton->setIconSize(QSize(18, 18));
    mGridToggleButton->setToolTip("Toggle grid");
    mGridToggleButton->setCheckable(true);
    mGridToggleButton->setChecked(true);
    mGridToggleButton->setAutoRaise(true);
    rootLayout->addWidget(mGridToggleButton, 0, Qt::AlignCenter);

    connect(mTriangulateButton, &QToolButton::clicked, this, &ToolBar::triangulateClicked);
    connect(mGridToggleButton, &QToolButton::toggled, this, &ToolBar::gridToggled);
}

void ToolBar::setGridEnabled(bool enabled) {
    if (mGridToggleButton == nullptr) {
        return;
    }
    mGridToggleButton->setChecked(enabled);
}

void ToolBar::setTriangulateEnabled(bool enabled) {
    if (mTriangulateButton == nullptr) {
        return;
    }
    mTriangulateButton->setEnabled(enabled);
}
