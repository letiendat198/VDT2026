#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QLoggingCategory>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("VDT2026", "Main");

    engine.rootContext()->setContextProperty("THUNDERFOREST_API_KEY", qgetenv("THUNDERFOREST_API_KEY"));
    qDebug() << qgetenv("THUNDERFOREST_API_KEY");

    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    return QGuiApplication::exec();
}
