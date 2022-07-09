#include "windowmanager.h"

int windowManager::startRegisterWindow()
{
    engine.reset(new QQmlApplicationEngine{});
    engine->rootContext()->setContextProperty("registerWindow", registerWindow.get());
    engine->load(QStringLiteral("qrc:/registerUI.qml"));

    return app->exec();
}

windowManager::windowManager(boost::asio::io_service& service)
{
    int arg{0};
    app.reset(new QGuiApplication{arg, nullptr});
    registerWindow.reset(new Register{service});
    connect(&(*registerWindow), &Register::hashStatus, this, &windowManager::hashStatus);
    registerWindow->initializeConnection();
    if(!registerWindow->checkLoginData()){
        startRegisterWindow();
    }
}

void windowManager::hashStatus(bool status)
{
    if(!status){
        startRegisterWindow();
        return;
    }
}
