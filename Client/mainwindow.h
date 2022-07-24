#pragma once

#include <QObject>
#include <boost/asio.hpp>
#include "../ConnectionHandler/headers/ConnectionHandler.h"

class MainWindow:public QObject,  public std::enable_shared_from_this<MainWindow>
{
    Q_OBJECT

    std::string ip_;
    short port_;
    boost::asio::io_service& service_;
    std::shared_ptr<IConnectionHandler<MainWindow>> handler_;
    std::string login_;

    void readCallback(std::shared_ptr<IConnectionHandler<MainWindow>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void writeCallback(std::shared_ptr<IConnectionHandler<MainWindow>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void init(const boost::system::error_code& erCode);

public:
    Q_INVOKABLE void logout();
    MainWindow(boost::asio::io_service& service, QObject *parent = nullptr);
    ~MainWindow();
    void initializeConnection();
signals:
    void customClose();
    void restartSession();
private slots:
    void startClose();
};
