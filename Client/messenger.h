#pragma once

#include <boost/asio.hpp>
#include "../ConnectionHandler/headers/ConnectionHandler.h"
#include <contact.h>

class Messenger: public std::enable_shared_from_this<Messenger>
{
    std::string ip_;
    short port_;
    boost::asio::io_service& service_;
    std::shared_ptr<IConnectionHandler<Messenger>> handler_;
    std::unordered_map<long long, Contact> contactMap_;
    long long userId_;
    std::string hash_;
    std::string name_;

    void readCallback(std::shared_ptr<IConnectionHandler<Messenger>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void writeCallback(std::shared_ptr<IConnectionHandler<Messenger>> handler, const boost::system::error_code &err, size_t bytes_transferred);
    void init(const boost::system::error_code& erCode);
public:
    Messenger(boost::asio::io_service& service, const std::string& hash);
    void initializeConnection();
};
