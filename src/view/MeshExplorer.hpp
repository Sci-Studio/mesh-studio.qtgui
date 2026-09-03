#pragma once

#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>

class MeshExplorer : public QFrame {
    Q_OBJECT

  public:
    explicit MeshExplorer(QWidget* parent = nullptr);

    void setCurrentFileName(const QString& fileName);
    void setPointsValueLabel(const unsigned int points);
    void setConstraintsValueLabel(const unsigned int points);
    void setTrianglesValueLabel(const unsigned int points);

  private:
    QLabel* mFileNameLabel = nullptr;
    QToolButton* mChevronButton = nullptr;
    QLabel* mPointsValueLabel = nullptr;
    QLabel* mConstraintsValueLabel = nullptr;
    QLabel* mTrianglesValueLabel = nullptr;
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
