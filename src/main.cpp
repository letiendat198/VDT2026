#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QQmlContext>
#include <QSettings>

#include "socket/Server.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("VDT2026");
    app.setOrganizationDomain("dat.gis.vdt2026");
    app.setApplicationName("gisVDT");

    QSettings settings;
    QString keyThunderforest = settings.value("keyThunderforest", "").toString();
    int socketPort = settings.value("socketPort", 8888).toInt();

    Server infoServer(socketPort);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("VDT2026", "Main");

    engine.rootContext()->setContextProperty("THUNDERFOREST_API_KEY", keyThunderforest);
    qDebug() << qgetenv("THUNDERFOREST_API_KEY");

    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    return QGuiApplication::exec();
}
