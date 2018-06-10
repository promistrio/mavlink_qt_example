#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <QtMath>
#include "mavcommunicator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    MavCommunicator mavModel;

    QQmlApplicationEngine engine;
    QQmlContext * ctx = engine.rootContext();


    ctx->setContextProperty("mavModel", &mavModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
