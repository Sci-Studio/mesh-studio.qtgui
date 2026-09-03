#include "ToolBox.hpp"
#include <qdialog.h>
#include <qpushbutton.h>

ToolBox::ToolBox(QWidget* parent) : QFrame(parent) {
    setObjectName("toolbox");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedSize(130, 84);
    raise();
    show();

    mTopViewButton = new QPushButton(this);
    mIsoViewButton = new QPushButton(this);

    mTopViewButton->setIcon(QIcon(":/svg/Rotate_CCW_24.svg"));
    mIsoViewButton->setIcon(QIcon(":/svg/Rotate_CW_24.svg"));

    mTopViewButton->setIconSize(QSize(45, 45));
    mIsoViewButton->setIconSize(QSize(45, 45));

    mTopViewButton->setGeometry(17, 19, 45, 45);
    mIsoViewButton->setGeometry(64, 19, 45, 45);

    connect(mTopViewButton, &QPushButton::clicked, this, [this]() { emit onTopViewClicked(); });
    connect(mIsoViewButton, &QPushButton::clicked, this, [this]() { emit onIsoViewClicked(); });
}
