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
    std::shared_ptr<Register> registerWindow;
    std::shared_ptr<MainWindow> mainWindow;
    std::unique_ptr<QGuiApplication> app;
    std::unique_ptr<QQmlApplicationEngine> engine;

    int startRegisterWindow();
    int startMainWindow();
    void start(boost::asio::io_service& service);
public:
    windowManager(boost::asio::io_service& service);
private slots:
    void hashStatus(bool status);
    void onSessionClose();
};
