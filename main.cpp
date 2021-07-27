#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calculator.h"
#include<QQmlContext>
#include<QQuickView>
#include "calculator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    //qDebug() << _calculator.calculate("1*2+3/7*((2+5)*99+14)");

    QQmlApplicationEngine engine;
    QQmlContext *m_qmlContext = engine.rootContext();
    m_qmlContext->setContextProperty("calculator", Calculator::getInstance());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
