#include "windowmanager.h"
#include <ioserviceworker.h>
#include <Commands.h>

windowManager::windowManager(boost::asio::io_service& service): service_{service}
{
    int arg{0};
    app_.reset(new QGuiApplication{arg, nullptr});
    start();

}

void windowManager::start()
{
    register_.reset(new Register{service_});
    register_->initializeConnection();
    auto status{checkRegisterState()}; //true when login was successful
    engine_.reset(new QQmlApplicationEngine{});
    engine_->rootContext()->setContextProperty("mainWindowClass", this);
    engine_->load(QStringLiteral("qrc:/MainWindow.qml"));
    if(status){
        emit loginSuccess();
        createMessengerInstance();
    }
    app_->exec();
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
            createMessengerInstance();
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
            createMessengerInstance();
            return;
            ;
        }
    }
}

void windowManager::createMessengerInstance()
{
    auto hash{register_->getHash()};
    register_.reset();
    messenger_.reset(new Messenger{service_, hash});
    messenger_->initializeConnection();
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
