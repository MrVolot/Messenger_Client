#include "messenger.h"
#include <QDebug>

Messenger::Messenger(boost::asio::io_service& service, const std::string& hash):
    service_{service},
    ip_{"127.0.0.1"},
    port_{10690},
    hash_{hash}
{
    handler_.reset(new ConnectionHandler<Messenger>{ service_, *this});
    handler_->setAsyncReadCallback(&Messenger::readCallback);
    handler_->setWriteCallback(&Messenger::writeCallback);
}

void Messenger::readCallback(std::shared_ptr<IConnectionHandler<Messenger> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{

}

void Messenger::writeCallback(std::shared_ptr<IConnectionHandler<Messenger> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{

}

void Messenger::init(const boost::system::error_code &erCode)
{
    handler_->callWrite(hash_);
    handler_->callAsyncRead();
}

void Messenger::initializeConnection()
{
    handler_->getSocket().async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip_), port_),std::bind(&Messenger::init,shared_from_this(),std::placeholders::_1));
}
