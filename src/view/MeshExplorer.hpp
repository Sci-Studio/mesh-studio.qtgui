#pragma once

#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>
#include <cstddef>

class MeshExplorer : public QFrame {
    Q_OBJECT

  public:
    explicit MeshExplorer(QWidget* parent = nullptr);

    void setCurrentFileName(const QString& fileName);
    void setPointsValueLabel(const size_t points);
    void setConstraintsValueLabel(const size_t points);
    void setTrianglesValueLabel(const size_t points);

  private:
    QLabel* mFileNameLabel = nullptr;
    QToolButton* mChevronButton = nullptr;
    QLabel* mPointsValueLabel = nullptr;
    QLabel* mConstraintsValueLabel = nullptr;
    QLabel* mTrianglesValueLabel = nullptr;
    QFrame* mHeaderFrame = nullptr;
    QFrame* mGeometryFrame = nullptr;
    QPixmap mChevronDownIcon;
    QPixmap mChevronRightIcon;
    bool mGeometryExpanded = false;

    void setGeometryFrameVisible(bool visible);
    void setGeometryExpanded(bool expanded);
    void toggleGeometryVisibility();
    void setRowLabelValue(QLabel* label, unsigned int value);
    void createHeader(QVBoxLayout* rootLayout);
    void createGeometryStats(QVBoxLayout* rootLayout);
    void createDivider(QVBoxLayout* geometryLayout, QFrame* geometryFrame,
                       const QString& objectName);
    QFrame* createStatRow(const QString& iconPath, const QString& labelText, QLabel*& valueLabel);
};
