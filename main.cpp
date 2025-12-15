#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <blackjackcontroller.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Basic");

    BlackjackController *blackjackController = new BlackjackController(&app);
    qmlRegisterSingletonInstance("proj.myproj.blackjackcontroller",1, 0, "BlackjackController", blackjackController);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("BlackJack", "Main");

    return app.exec();
}
