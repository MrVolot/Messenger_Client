//#include "messenger.h"
//#include <QDebug>
//#include "../Json/json/json.h"
//#include <Commands.h>
//template <typename Caller>
//Messenger<Caller>::Messenger(boost::asio::io_service& service, const std::string& hash):
//    service_{service},
//    ip_{"127.0.0.1"},
//    port_{10690},
//    hash_{hash}
//{
//    handler_.reset(new ConnectionHandler<Messenger>{ service_, *this});
//    handler_->setAsyncReadCallback(&Messenger::readCallback);
//    handler_->setWriteCallback(&Messenger::writeCallback);
//}
//template <typename Caller>
//Messenger<Caller>::~Messenger()
//{
//    handler_->getSocket().close();
//}
//template <typename Caller>
//void Messenger<Caller>::readCallback(std::shared_ptr<IConnectionHandler<Messenger> > handler, const boost::system::error_code &err, size_t bytes_transferred)
//{
//    if(err){
//        qDebug()<<err.message().c_str();
//        return;
//    }
//    auto data{boost::asio::buffer_cast<const char*>(handler->getStrBuf()->data())};
//    parseServerCommands(data);
//    handler_->callAsyncRead();
//}
//template <typename Caller>
//void Messenger<Caller>::writeCallback(std::shared_ptr<IConnectionHandler<Messenger> > handler, const boost::system::error_code &err, size_t bytes_transferred)
//{

//}
//template <typename Caller>
//void Messenger<Caller>::init(const boost::system::error_code &erCode)
//{
//    handler_->callWrite(hash_);
//    handler_->callAsyncRead();
//}
//template <typename Caller>
//void Messenger<Caller>::parseServerCommands(const std::string &data)
//{
//    Json::Value value;
//    Json::Reader reader;
//    reader.parse(data, value);
//    switch(value["command"].asInt()){
//    case SENDMESSAGE:
//        receiveMessage(data);
//        break;
//    }

//}
//template <typename Caller>
//void Messenger<Caller>::receiveMessage(const std::string &data)
//{
//    Json::Value value;
//    Json::Reader reader;
//    reader.parse(data, value);
//    qDebug()<<value["sender"].asCString() << " " << value["message"].asCString();
//}
//template <typename Caller>
//void Messenger<Caller>::initializeConnection()
//{
//    handler_->getSocket().async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip_), port_),std::bind(&Messenger::init,this->shared_from_this(),std::placeholders::_1));
//}
//template <typename Caller>
//void Messenger<Caller>::sendMessage(const std::string &receiver, const std::string &message)
//{
//    Json::Value value;
//    Json::FastWriter writer;
//    value["receiver"] = receiver;
//    value["message"] = message;
//    value["command"] = "sendMessage";
//    handler_->callWrite(writer.write(value));
//}
//template <typename Caller>
//void Messenger<Caller>::logout()
//{
//    Json::Value value;
//    Json::FastWriter writer;
//    value["command"] = "logout";
//    handler_->callWrite(writer.write(value));
//}
//template <typename Caller>
//void Messenger<Caller>::setReceiveMessageCallback(std::function<void (Caller*, const std::string &, const std::string &)> callback)
//{
//    senderCallback_= callback;
//}
