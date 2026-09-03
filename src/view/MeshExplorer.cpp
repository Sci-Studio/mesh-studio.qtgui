#include "MeshExplorer.hpp"

#include <QLocale>

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
    createGeometryStats(rootLayout);
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
    fileIconLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    headerLayout->addWidget(fileIconLabel, 0, Qt::AlignVCenter);

    mFileNameLabel = new QLabel("No File Selected", headerFrame);
    mFileNameLabel->setObjectName("ms-mesh-explorer-file-name");
    mFileNameLabel->setAttribute(Qt::WA_StyledBackground, true);
    mFileNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mFileNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    headerLayout->addWidget(mFileNameLabel, 1);

    auto* chevronLabel = new QLabel(headerFrame);
    chevronLabel->setObjectName("ms-mesh-explorer-chevron");
    chevronLabel->setFixedSize(12, 12);
    chevronLabel->setPixmap(
        QPixmap(":/svg/Chevron_24.svg")
            .scaled(chevronLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    chevronLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    headerLayout->addWidget(chevronLabel, 0, Qt::AlignVCenter);

    rootLayout->addWidget(headerFrame);
}

void MeshExplorer::createGeometryStats(QVBoxLayout* rootLayout) {
    auto* geometryFrame = new QFrame(this);
    geometryFrame->setObjectName("ms-mesh-explorer-geometry");
    geometryFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto* geometryLayout = new QVBoxLayout(geometryFrame);
    geometryLayout->setContentsMargins(0, 6, 0, 6);
    geometryLayout->setSpacing(0);

    auto* sectionHeader = new QLabel("GEOMETRY", geometryFrame);
    sectionHeader->setObjectName("ms-mesh-explorer-section-title");
    sectionHeader->setContentsMargins(10, 4, 10, 6);
    geometryLayout->addWidget(sectionHeader);

    geometryLayout->addWidget(createStatRow(":/svg/Points_24.svg", "Points", mPointsValueLabel));
    createDivider(geometryLayout, geometryFrame, "points");
    geometryLayout->addWidget(
        createStatRow(":/svg/Constraints_24.svg", "Constraints", mConstraintsValueLabel));
    createDivider(geometryLayout, geometryFrame, "constraints");
    geometryLayout->addWidget(
        createStatRow(":/svg/Triangle_24.svg", "Triangles", mTrianglesValueLabel));

    rootLayout->addWidget(geometryFrame);
}

void MeshExplorer::createDivider(QVBoxLayout* geometryLayout, QFrame* geometryFrame,
                                 const QString& objectName) {
    auto* divider = new QFrame(geometryFrame);
    divider->setObjectName("ms-mesh-explorer-divider");
    divider->setFixedHeight(1);
    geometryLayout->addWidget(divider);
}

QFrame* MeshExplorer::createStatRow(const QString& iconPath, const QString& labelText,
                                    QLabel*& valueLabel) {

    auto* rowFrame = new QFrame(this);
    rowFrame->setObjectName("ms-mesh-explorer-stat-row");
    rowFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto* rowLayout = new QHBoxLayout(rowFrame);
    rowLayout->setContentsMargins(10, 8, 10, 8);
    rowLayout->setSpacing(8);

    auto* iconLabel = new QLabel(rowFrame);
    iconLabel->setObjectName("ms-mesh-explorer-stat-icon");
    iconLabel->setFixedSize(16, 16);
    iconLabel->setPixmap(
        QPixmap(iconPath).scaled(iconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    rowLayout->addWidget(iconLabel, 0, Qt::AlignVCenter);

    auto* textLabel = new QLabel(labelText, rowFrame);
    textLabel->setObjectName("ms-mesh-explorer-stat-label");
    rowLayout->addWidget(textLabel, 1, Qt::AlignVCenter);

    valueLabel = new QLabel("0", rowFrame);
    valueLabel->setObjectName("ms-mesh-explorer-stat-value");
    valueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    rowLayout->addWidget(valueLabel, 0, Qt::AlignVCenter);

    return rowFrame;
}

void MeshExplorer::setCurrentFileName(const QString& fileName) {
    if (mFileNameLabel == nullptr) {
        return;
    }
    mFileNameLabel->setText(fileName);
}

void MeshExplorer::updateCounterLabel(QLabel* label, unsigned int value) {
    if (label == nullptr) {
        return;
    }
    label->setText(QLocale().toString(static_cast<qlonglong>(value)));
}

void MeshExplorer::setPointsValueLabel(unsigned int points) {
    updateCounterLabel(mPointsValueLabel, points);
}

void MeshExplorer::setConstraintsValueLabel(unsigned int constraints) {
    updateCounterLabel(mConstraintsValueLabel, constraints);
}

void MeshExplorer::setTrianglesValueLabel(unsigned int triangles) {
    updateCounterLabel(mTrianglesValueLabel, triangles);
}
