#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "songmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SongManager songManager;
    engine.rootContext()->setContextProperty("songManager", &songManager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Mood-Mix", "Main");

    return app.exec();
}
