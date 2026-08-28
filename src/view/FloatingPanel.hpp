#pragma once

#include <QFrame>
#include <qobject.h>
#include <qwidget.h>

class FloatingPanel : public QFrame {
    Q_OBJECT

  public:
    explicit FloatingPanel(QWidget* parent = nullptr);
};
