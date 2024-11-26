#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "mycounter.h"
#include "randomnumbergenerator.h"
#include "filehandler.h"
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CounterClass>("Counter", 1, 0, "Counter");
    app.setOrganizationName("MyOrganization");
    app.setOrganizationDomain("myorganization.com");

    //register the RandomNumberGenerator class here
    qmlRegisterType<RandomNumberGenerator>("RandomNumberGenerator", 1, 0, "RandomNumberGenerator");
    qmlRegisterType<FileHandler>("FileHandler", 1, 0, "FileHandler");
    qmlRegisterType<DatabaseManager>("DatabaseManager", 1, 0, "DatabaseManager");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/Counter/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

//google Gemini api key
//AIzaSyCQ2P-Imyhc7dGiq2VxmqpIncAMP8BUy6U
