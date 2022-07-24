#pragma once

#include <QObject>
#include <register.h>
#include <boost/asio.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <mainwindow.h>

class windowManager: public QObject
{
    Q_OBJECT
    std::shared_ptr<Register> register_;
    std::shared_ptr<MainWindow> main_;
    std::unique_ptr<QGuiApplication> app;
    std::unique_ptr<QQmlApplicationEngine> engine;

    void startRegistration();
    void start(boost::asio::io_service& service);
    bool checkRegisterState();
    void asyncLogin(const QString& login, const QString& password);
    void asyncRegister(const QString& login, const QString& password);
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
