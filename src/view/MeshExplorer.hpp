#pragma once

#include <QFrame>

class MeshExplorer : public QFrame {
    Q_OBJECT

  public:
    explicit MeshExplorer(QWidget* parent = nullptr);

    void setPoints(const unsigned int points);
    void setConstraints(const unsigned int points);
    void setTriangles(const unsigned int points);

  private:
    unsigned int mPoints;
    unsigned int mConstraints;
    unsigned int mTriangles;
};
