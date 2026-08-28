#include "FloatingPanel.hpp"
#include <qnamespace.h>
#include <qwidget.h>

FloatingPanel::FloatingPanel(QWidget* parent) : QFrame(parent) {
    setObjectName("leftConfigPanel");
    setAttribute(Qt::WA_StyledBackground, true);
}
