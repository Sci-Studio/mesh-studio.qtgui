#include "ToolBox.hpp"
#include <qdialog.h>
#include <qpushbutton.h>

ToolBox::ToolBox(QWidget* parent) : QFrame(parent) {
    setObjectName("toolbox");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedSize(130, 130);
    raise();
    show();

    mTopViewButton = new QPushButton(this);
    mIsoViewButton = new QPushButton(this);
    mTriangulateButton = new QPushButton(this);

    mTopViewButton->setIcon(QIcon(":/assets/ui/top.png"));
    mIsoViewButton->setIcon(QIcon(":/assets/ui/iso.png"));
    mTriangulateButton->setIcon(QIcon(":/assets/ui/triangulate.png"));

    mTopViewButton->setIconSize(QSize(45, 45));
    mIsoViewButton->setIconSize(QSize(45, 45));
    mTriangulateButton->setIconSize(QSize(45, 38));

    mTopViewButton->setGeometry(17, 19, 45, 45);
    mIsoViewButton->setGeometry(64, 19, 45, 45);
    mTriangulateButton->setGeometry(41, 76, 48, 38);

    connect(mTopViewButton, &QPushButton::clicked, this, &ToolBox::onTopViewClicked);
}

void ToolBox::onTopViewClicked() {
    qDebug() << "top view clicked";
}

void ToolBox::onIsoViewClicked() {
    qDebug() << "Iso view clicked";
}

void ToolBox::onTriangulateClicked() {
    qDebug() << "ttiangulate clicked";
}
