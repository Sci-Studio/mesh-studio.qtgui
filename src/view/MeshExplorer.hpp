#pragma once

#include <QFrame>
#include <QLabel>
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
    unsigned int mPoints;
    unsigned int mConstraints;
    unsigned int mTriangles;

    QLabel* mFileNameLabel = nullptr;
    QLabel* mPointsValueLabel = nullptr;
    QLabel* mConstraintsValueLabel = nullptr;
    QLabel* mTrianglesValueLabel = nullptr;

    void createHeader(QVBoxLayout* rootLayout);
    void createGeometryStats(QVBoxLayout* rootLayout);
    void createDivider(QVBoxLayout* geometryLayout, QFrame* geometryFrame,
                       const QString& objectName);
    QFrame* createStatRow(const QString& iconPath, const QString& labelText, QLabel*& valueLabel);
};
