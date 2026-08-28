#include "ToolBox.hpp"

ToolBox::ToolBox(QWidget* parent) : QFrame(parent) {
    setObjectName("leftConfigPanel");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedSize(130, 130);
}
