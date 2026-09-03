#include "MeshExplorer.hpp"

MeshExplorer::MeshExplorer(QWidget* parent) : QFrame(parent) {
    setObjectName("ms-mesh-explorer");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedWidth(300);
    show();

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    auto* rootLayout = new QVBoxLayout(this);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    createHeader(rootLayout);
}

void MeshExplorer::createHeader(QVBoxLayout* rootLayout) {
    auto* headerFrame = new QFrame(this);
    headerFrame->setObjectName("ms-mesh-explorer-header");
    headerFrame->setAttribute(Qt::WA_StyledBackground, true);
    headerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    headerFrame->setFixedHeight(50);

    auto* headerLayout = new QHBoxLayout(headerFrame);
    headerLayout->setContentsMargins(16, 16, 16, 16);
    headerLayout->setSpacing(12);

    auto* fileIconLabel = new QLabel(headerFrame);
    fileIconLabel->setObjectName("ms-mesh-explorer-file-icon");
    fileIconLabel->setFixedSize(14, 17);
    fileIconLabel->setPixmap(
        QPixmap(":/svg/File_24.svg")
            .scaled(fileIconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    headerLayout->addWidget(fileIconLabel, 0, Qt::AlignVCenter);

    mFileNameLabel = new QLabel("No File Selected", headerFrame);
    mFileNameLabel->setObjectName("ms-mesh-explorer-file-name");
    mFileNameLabel->setAttribute(Qt::WA_StyledBackground, true);
    mFileNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mFileNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    headerLayout->addWidget(mFileNameLabel, 1);

    rootLayout->addWidget(headerFrame);
}

void MeshExplorer::setCurrentFileName(const QString& fileName) {
    if (mFileNameLabel == nullptr) {
        return;
    }
    mFileNameLabel->setText(fileName);
}
