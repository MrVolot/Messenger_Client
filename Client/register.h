#pragma once

#include <QObject>
#include <boost/asio.hpp>
#include "../ConnectionHandler/headers/ConnectionHandler.h"
#include <QDebug>

using namespace boost::asio;

class Register : public QObject,  public std::enable_shared_from_this<Register>
{
    Q_OBJECT

    std::string ip_;
    short port_;
    io_service& service_;
    std::shared_ptr<IConnectionHandler<Register>> handler_;
    std::string login_;

    void readCallback(std::shared_ptr<IConnectionHandler<Register>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void writeCallback(std::shared_ptr<IConnectionHandler<Register>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void init(const boost::system::error_code& erCode);
    void writeHashToFile(const std::string &hash);
public:
    explicit Register(io_service& service, QObject *parent = nullptr);
    Q_INVOKABLE void loginUser(QString login, QString password, QString command);
    bool checkLoginData();
    void initializeConnection();
signals:
    void hashStatus(bool status);
    void customClose();
    void wrongCredentials();
};
