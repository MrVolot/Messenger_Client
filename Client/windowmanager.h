#pragma once

#include <QObject>
#include <register.h>
#include <boost/asio.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <messenger.h>

class windowManager: public QObject
{
    Q_OBJECT
    std::shared_ptr<Register> register_;
    std::shared_ptr<Messenger> messenger_;
    std::unique_ptr<QGuiApplication> app_;
    std::unique_ptr<QQmlApplicationEngine> engine_;
    boost::asio::io_service& service_;

    void startRegistration();
    void start();
    bool checkRegisterState();
    void asyncLogin(const QString& login, const QString& password);
    void asyncRegister(const QString& login, const QString& password);
    void createMessengerInstance();
public:
    windowManager(boost::asio::io_service& service);
public slots:
    Q_INVOKABLE void loginUser(const QString& login, const QString& password);
    Q_INVOKABLE void registerUser(const QString& login, const QString& password);
signals:
    void loginSuccess();
    void wrongCredentials();
    void userExists();
};
