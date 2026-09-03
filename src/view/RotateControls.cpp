#include "RotateControls.hpp"

#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

RotateControls::RotateControls(QWidget* parent) : QFrame(parent) {
    setObjectName("ms-rotate-controls");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedSize(122, 40);
    raise();
    show();

    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(4, 4, 4, 4);
    rootLayout->setSpacing(0);

    auto* rowLayout = new QHBoxLayout();
    rowLayout->setContentsMargins(0, 0, 0, 0);
    rowLayout->setSpacing(4);

    mGripHandle = new QFrame(this);
    mGripHandle->setObjectName("ms-rotate-controls-grip");
    mGripHandle->setFixedSize(6, 20);
    rowLayout->addWidget(mGripHandle, 0, Qt::AlignVCenter);

    mRotateCcwButton = new QToolButton(this);
    mRotateCcwButton->setObjectName("ms-rotate-controls-ccw");
    mRotateCcwButton->setFixedSize(36, 31);
    mRotateCcwButton->setIcon(QIcon(":/svg/Rotate_CCW_24.svg"));
    mRotateCcwButton->setIconSize(QSize(24, 24));
    mRotateCcwButton->setToolTip("Rotate 45° CCW");
    mRotateCcwButton->setAutoRaise(true);
    rowLayout->addWidget(mRotateCcwButton, 0, Qt::AlignVCenter);

    auto* divider = new QFrame(this);
    divider->setObjectName("ms-rotate-controls-divider");
    divider->setFixedSize(1, 20);
    rowLayout->addWidget(divider, 0, Qt::AlignVCenter);

    mRotateCwButton = new QToolButton(this);
    mRotateCwButton->setObjectName("ms-rotate-controls-cw");
    mRotateCwButton->setFixedSize(36, 31);
    mRotateCwButton->setIcon(QIcon(":/svg/Rotate_CW_24.svg"));
    mRotateCwButton->setIconSize(QSize(24, 24));
    mRotateCwButton->setToolTip("Rotate 45° CW");
    mRotateCwButton->setAutoRaise(true);
    rowLayout->addWidget(mRotateCwButton, 0, Qt::AlignVCenter);

    rootLayout->addLayout(rowLayout);

    connect(mRotateCcwButton, &QToolButton::clicked, this, &RotateControls::rotateCcwClicked);
    connect(mRotateCwButton, &QToolButton::clicked, this, &RotateControls::rotateCwClicked);
}
