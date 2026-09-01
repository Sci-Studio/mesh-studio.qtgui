#include <QApplication>
#include <QTimer>

#include "MainWindow.hpp"
#include "controller/MeshController.hpp"
#include "geometry/Mesh.hpp"
#include "utils/Theme.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Theme::apply(app);

    MainWindow window;
    window.show();

    geometry::Mesh mesh;
    MeshController meshController(&mesh, &window);

    QTimer::singleShot(5, &window, [&window]() { window.setWindowState(Qt::WindowMaximized); });

    return app.exec();
}
