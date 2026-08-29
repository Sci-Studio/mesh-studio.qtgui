#pragma once

#include <QFrame>
#include <QPushButton>

class ToolBox : public QFrame {
    Q_OBJECT

  public:
    explicit ToolBox(QWidget* parent = nullptr);

  signals:
    void onTopViewClicked();
    void onIsoViewClicked();
    void onTriangulateClicked();

  private:
    QPushButton* mTopViewButton = nullptr;
    QPushButton* mIsoViewButton = nullptr;
    QPushButton* mTriangulateButton = nullptr;
};
