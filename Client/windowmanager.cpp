#include "windowmanager.h"
#include <ioserviceworker.h>

windowManager::windowManager(boost::asio::io_service& service)
{
    int arg{0};
    app.reset(new QGuiApplication{arg, nullptr});
    start(service);
}

int windowManager::startRegisterWindow()
{

    engine.reset(new QQmlApplicationEngine{});
    engine->rootContext()->setContextProperty("registerWindow", registerWindow.get());
    engine->load(QStringLiteral("qrc:/registerUI.qml"));
    registerWindow->initializeConnection();
    return app->exec();
}

int windowManager::startMainWindow()
{
    engine.reset(new QQmlApplicationEngine{});
    engine->rootContext()->setContextProperty("mainWindow", mainWindow.get());
    engine->load(QStringLiteral("qrc:/MainWindowUI.qml"));
    mainWindow->initializeConnection();
    return app->exec();
}

void windowManager::start(boost::asio::io_service& service)
{
    registerWindow.reset(new Register{service});
    mainWindow.reset(new MainWindow{service});
    connect(&(*registerWindow), &Register::hashStatus, this, &windowManager::hashStatus);
    connect(&(*mainWindow), &MainWindow::restartSession, this, &windowManager::onSessionClose);
    startRegisterWindow();
}


void windowManager::hashStatus(bool status)
{
    if(!status){
        startRegisterWindow();
        return;
    }
    startMainWindow();
}

void windowManager::onSessionClose()
{
    start(IoServiceWorker::getInstance().getService());
}
