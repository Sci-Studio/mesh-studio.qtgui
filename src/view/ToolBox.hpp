#pragma once

#include <QFrame>
#include <qwidget.h>

class ToolBox : public QFrame {
    Q_OBJECT

  public:
    explicit ToolBox(QWidget* parent = nullptr);
};
