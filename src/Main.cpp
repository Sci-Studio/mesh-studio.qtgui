#include <QApplication>
#include <QTimer>

#include "controller/MeshController.hpp"
#include "model/UIMesh.hpp"
#include "utils/Theme.hpp"
#include "view/MainWindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Theme::apply(app);

    MainWindow window;
    window.show();

    UIMesh uiMesh;
    MeshController meshController(&uiMesh, &window);

    QTimer::singleShot(5, &window, [&window]() { window.setWindowState(Qt::WindowMaximized); });

    return app.exec();
}
