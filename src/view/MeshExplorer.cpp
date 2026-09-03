#include "MeshExplorer.hpp"

#include <QFontMetrics>
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
    setCurrentFileName(QString());
}

void MeshExplorer::createHeader(QVBoxLayout* rootLayout) {
    mHeaderFrame = new QFrame(this);
    mHeaderFrame->setObjectName("ms-mesh-explorer-header");
    mHeaderFrame->setAttribute(Qt::WA_StyledBackground, true);
    mHeaderFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mHeaderFrame->setFixedHeight(50);

    auto* headerLayout = new QHBoxLayout(mHeaderFrame);
    headerLayout->setContentsMargins(16, 16, 16, 16);
    headerLayout->setSpacing(12);

    mChevronButton = new QToolButton(mHeaderFrame);
    mChevronButton->setObjectName("ms-mesh-explorer-chevron-btn");
    mChevronButton->setFixedSize(12, 12);
    mChevronButton->setVisible(true);
    mChevronButton->setAttribute(Qt::WA_TranslucentBackground, true);

    const QPixmap source(":/svg/Chevron_24.svg");
    mChevronDownIcon = source.scaled(12, 12, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mChevronRightIcon =
        mChevronDownIcon.transformed(QTransform().rotate(-90.0), Qt::SmoothTransformation);
    mChevronButton->setIcon(QIcon(mChevronDownIcon));
    headerLayout->addWidget(mChevronButton, 0, Qt::AlignVCenter);

    auto* fileIconLabel = new QLabel(mHeaderFrame);
    fileIconLabel->setObjectName("ms-mesh-explorer-file-icon");
    fileIconLabel->setFixedSize(14, 17);
    fileIconLabel->setPixmap(
        QPixmap(":/svg/File_24.svg")
            .scaled(fileIconLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    fileIconLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    headerLayout->addWidget(fileIconLabel, 0, Qt::AlignVCenter);

    mFileNameLabel = new QLabel("No File Selected", mHeaderFrame);
    mFileNameLabel->setObjectName("ms-mesh-explorer-file-name");
    mFileNameLabel->setAttribute(Qt::WA_StyledBackground, true);
    mFileNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mFileNameLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    headerLayout->addWidget(mFileNameLabel, 1);

    connect(mChevronButton, &QToolButton::clicked, this, &MeshExplorer::toggleGeometryVisibility);

    rootLayout->addWidget(mHeaderFrame);
}

void MeshExplorer::createGeometryStats(QVBoxLayout* rootLayout) {
    mGeometryFrame = new QFrame(this);
    mGeometryFrame->setObjectName("ms-mesh-explorer-geometry");
    mGeometryFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto* geometryLayout = new QVBoxLayout(mGeometryFrame);
    geometryLayout->setContentsMargins(0, 6, 0, 6);
    geometryLayout->setSpacing(0);

    auto* sectionHeader = new QLabel("GEOMETRY", mGeometryFrame);
    sectionHeader->setObjectName("ms-mesh-explorer-section-title");
    sectionHeader->setContentsMargins(10, 4, 10, 6);
    geometryLayout->addWidget(sectionHeader);

    geometryLayout->addWidget(createStatRow(":/svg/Points_24.svg", "Points", mPointsValueLabel));
    createDivider(geometryLayout, mGeometryFrame, "points");
    geometryLayout->addWidget(
        createStatRow(":/svg/Constraints_24.svg", "Constraints", mConstraintsValueLabel));
    createDivider(geometryLayout, mGeometryFrame, "constraints");
    geometryLayout->addWidget(
        createStatRow(":/svg/Triangle_24.svg", "Triangles", mTrianglesValueLabel));

    setGeometryFrameVisible(false);
    rootLayout->addWidget(mGeometryFrame);
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
    if (mFileNameLabel == nullptr || mChevronButton == nullptr) {
        return;
    }
    const QString trimmedFileName = fileName.trimmed();
    if (trimmedFileName.isEmpty()) {
        mFileNameLabel->setText(QStringLiteral("No File Selected"));
        mChevronButton->setEnabled(false);
        setGeometryFrameVisible(false);
        setGeometryExpanded(false);
        mChevronButton->setIcon(QIcon(mChevronRightIcon));
        mFileNameLabel->setToolTip(QString());
        if (mHeaderFrame != nullptr) {
            mHeaderFrame->setToolTip(QStringLiteral("Open a new file"));
        }
        return;
    }
    const QFontMetrics metrics(mFileNameLabel->font());
    const int availableWidth = mFileNameLabel->width() > 0 ? mFileNameLabel->width() : 1;
    const QString elidedFileName =
        metrics.elidedText(trimmedFileName, Qt::ElideRight, availableWidth);
    mFileNameLabel->setText(elidedFileName);
    mChevronButton->setEnabled(true);
    setGeometryFrameVisible(true);
    setGeometryExpanded(true);
    mChevronButton->setIcon(QIcon(mChevronDownIcon));
    mFileNameLabel->setToolTip(trimmedFileName);
    if (mHeaderFrame != nullptr) {
        mHeaderFrame->setToolTip(QString());
    }
}

void MeshExplorer::setRowLabelValue(QLabel* label, unsigned int value) {
    if (label == nullptr) {
        return;
    }
    label->setText(QLocale().toString(static_cast<qlonglong>(value)));
}

void MeshExplorer::setPointsValueLabel(unsigned int points) {
    setRowLabelValue(mPointsValueLabel, points);
}

void MeshExplorer::setConstraintsValueLabel(unsigned int constraints) {
    setRowLabelValue(mConstraintsValueLabel, constraints);
}

void MeshExplorer::setTrianglesValueLabel(unsigned int triangles) {
    setRowLabelValue(mTrianglesValueLabel, triangles);
}

void MeshExplorer::setGeometryFrameVisible(bool visible) {
    if (mGeometryFrame == nullptr) {
        return;
    }
    mGeometryFrame->setVisible(visible);
}

void MeshExplorer::toggleGeometryVisibility() {
    if (mGeometryFrame == nullptr || mChevronButton == nullptr || !mChevronButton->isEnabled()) {
        return;
    }
    setGeometryExpanded(!mGeometryExpanded);
    mGeometryExpanded ? mChevronButton->setIcon(QIcon(mChevronDownIcon))
                      : mChevronButton->setIcon(QIcon(mChevronRightIcon));
    setGeometryFrameVisible(mGeometryExpanded);
}

void MeshExplorer::setGeometryExpanded(bool expanded) {
    if (mGeometryFrame == nullptr) {
        return;
    }
    mGeometryExpanded = expanded;
}
