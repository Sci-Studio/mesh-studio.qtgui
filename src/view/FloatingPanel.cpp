#include "FloatingPanel.hpp"

#include <QFrame>
#include <QHBoxLayout>
#include <QPixmap>
#include <QSizePolicy>
#include <QVBoxLayout>

FloatingPanel::FloatingPanel(QWidget* parent) : QFrame(parent) {
    setObjectName("leftConfigPanel");
    setAttribute(Qt::WA_StyledBackground, true);

    auto* leftPanelLayout = new QVBoxLayout(this);
    leftPanelLayout->setContentsMargins(0, 0, 0, 0);
    leftPanelLayout->setSpacing(0);

    auto* header = new QFrame(this);
    header->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    header->setMinimumHeight(64);
    header->setStyleSheet("QFrame { border-bottom: 1px solid rgba(68, 71, 72, 128); }");

    auto* headerLayout = new QVBoxLayout(header);
    headerLayout->setContentsMargins(16, 16, 16, 14);
    headerLayout->setSpacing(8);

    auto* titleRow = new QHBoxLayout();
    titleRow->setContentsMargins(0, 0, 0, 0);
    titleRow->setSpacing(12);

    auto* docIcon = new QLabel(header);
    docIcon->setFixedSize(14, 17);
    docIcon->setPixmap(QPixmap(":/assets/ui/file-doc.svg")
                           .scaled(docIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    titleRow->addWidget(docIcon, 0, Qt::AlignVCenter);

    auto* title = new QLabel("Project_Alpha.dxf", header);
    title->setObjectName("titleLabel");
    mFileNameLabel = title;
    titleRow->addWidget(title, 1, Qt::AlignVCenter);
    titleRow->addStretch(1);
    headerLayout->addLayout(titleRow);

    leftPanelLayout->addWidget(header);
    leftPanelLayout->addStretch(1);
}
