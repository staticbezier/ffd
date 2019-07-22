#include <QGuiApplication>
#include <QQuickView>

#include "ctrl_points.h"
#include "stl_mesh.h"


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    app.setOrganizationName("None");
    app.setOrganizationDomain("None");
    app.setApplicationName("FFD/Bezier Volume Example");

    qmlRegisterType<ctrl_points>("own.classes.ctrl_points", 1, 0, "CtrlPoints");
    qmlRegisterType<stl_mesh>("own.classes.stl_mesh", 1, 0, "StlMesh");

    QQuickView view;

    view.resize(1024, 768);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
