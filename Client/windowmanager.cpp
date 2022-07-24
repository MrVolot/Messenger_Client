#include "windowmanager.h"
#include <ioserviceworker.h>
#include <Commands.h>


windowManager::windowManager(boost::asio::io_service& service)
{
    int arg{0};
    app.reset(new QGuiApplication{arg, nullptr});
    start(service);

}

void windowManager::start(boost::asio::io_service& service)
{
    register_.reset(new Register{service});
    register_->initializeConnection();
    //auto status{checkRegisterState()}; //true when login was successful
    engine.reset(new QQmlApplicationEngine{});
    engine->rootContext()->setContextProperty("mainWindowClass", this);
    engine->load(QStringLiteral("qrc:/MainWindow.qml"));
    //    if(status){
    //        emit loginSuccess();
    //    }
    app->exec();
}

bool windowManager::checkRegisterState()
{
    auto authResponse{register_->checkLoginData()};
    switch(authResponse){
    case AUTHSUCCESS:
        return true;
    case AUTHFAIL:
        return false;
    }
    return false;
}

void windowManager::asyncLogin(const QString &login, const QString &password)
{
    if(register_!=nullptr){
        auto credentialsResponse{register_->loginUser(login, password, "login")};
        switch(credentialsResponse){
        case WRONGCREDENTIALS:
            emit wrongCredentials();
            return;
        case RIGHTCREDENTIALS:
            emit loginSuccess();
            return;
        }
    }
}

void windowManager::asyncRegister(const QString &login, const QString &password)
{
    if(register_!=nullptr){
        auto credentialsResponse{register_->loginUser(login, password, "register")};
        switch(credentialsResponse){
        case USERALREADYEXISTS:
            emit userExists();
            return;
        case RIGHTCREDENTIALS:
            emit loginSuccess();
            return;
            ;
        }
    }
}

void windowManager::loginUser(const QString &login, const QString &password)
{
    std::thread trd{&windowManager::asyncLogin, this, login, password};
    trd.detach();
}

void windowManager::registerUser(const QString &login, const QString &password)
{
    std::thread trd{&windowManager::asyncRegister, this, login, password};
    trd.detach();
}
