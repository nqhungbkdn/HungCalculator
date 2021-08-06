#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "calculator.h"
#include<QQmlContext>
#include<QQuickView>
#include "calculator.h"
#include "memorymodel.h"
#include <QStringListModel>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    MemoryModel memoryModel;

    QQmlApplicationEngine engine;
    QQmlContext *m_qmlContext = engine.rootContext();
    m_qmlContext->setContextProperty("_calculator", Calculator::getInstance());
    m_qmlContext->setContextProperty("_memoryModel", &memoryModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
