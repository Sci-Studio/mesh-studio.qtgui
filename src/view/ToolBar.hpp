#pragma once

#include <QFrame>

class QToolButton;

class ToolBar : public QFrame {
    Q_OBJECT

  public:
    explicit ToolBar(QWidget* parent = nullptr);

    void setGridEnabled(bool enabled);

  signals:
    void triangulateClicked();
    void gridToggled(bool visible);

  private:
    QToolButton* mTriangulateButton = nullptr;
    QToolButton* mGridToggleButton = nullptr;
};
