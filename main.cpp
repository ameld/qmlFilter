#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "MyFilter.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyFilte>("my.filter", 1, 0, "MyFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
