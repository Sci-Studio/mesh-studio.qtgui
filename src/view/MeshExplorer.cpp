#include "MeshExplorer.hpp"

MeshExplorer::MeshExplorer(QWidget* parent) : QFrame(parent) {
    setObjectName("ms-mesh-explorer");
    setAttribute(Qt::WA_StyledBackground, true);
    setFixedWidth(300);
    show();
}
