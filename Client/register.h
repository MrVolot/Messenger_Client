#pragma once

#include <QObject>
#include <boost/asio.hpp>
#include "../ConnectionHandler/headers/ConnectionHandler.h"
#include <mutex>
#include <condition_variable>

class Register : public QObject,  public std::enable_shared_from_this<Register>
{
    Q_OBJECT

    std::string ip_;
    short port_;
    boost::asio::io_service& service_;
    std::shared_ptr<IConnectionHandler<Register>> handler_;
    std::mutex mtx;
    std::condition_variable cv;
    std::string serverResponseString;

    void writeCallback(std::shared_ptr<IConnectionHandler<Register>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void readCallback(std::shared_ptr<IConnectionHandler<Register>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void init(const boost::system::error_code& erCode);
    std::string createDeviceId();
    unsigned int checkServerResponse();
public:
    Register(boost::asio::io_service& service, QObject *parent = nullptr);
    ~Register();
    unsigned int loginUser(const QString& login, const QString& password, const QString& command);
    unsigned int checkLoginData();
    void initializeConnection();
};
