#pragma once

#include <QObject>
#include <register.h>
#include <boost/asio.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>

class windowManager: public QObject
{
    Q_OBJECT
    std::shared_ptr<Register> registerWindow;
    std::unique_ptr<QGuiApplication> app;
    std::unique_ptr<QQmlApplicationEngine> engine;

    int startRegisterWindow();
public:
    windowManager(boost::asio::io_service& service);
private slots:
    void hashStatus(bool status);
};
