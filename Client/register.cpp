#include "register.h"
#include "../Json/json/json.h"
#include <fstream>

Register::Register(io_service& service, QObject *parent)
    : service_{service},
      QObject{parent},
      ip_{"127.0.0.1"},
      port_{10677}
{
    handler_.reset(new ConnectionHandler<Register>{ service_, *this});
    handler_->setReadCallback(&Register::readCallback);
    handler_->setWriteCallback(&Register::writeCallback);
}

void Register::readCallback(std::shared_ptr<IConnectionHandler<Register> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{
    std::string data{boost::asio::buffer_cast<const char*>(handler_->getStrBuf()->data())};
    Json::Value value;
    Json::Reader reader;
    reader.parse(data, value);
    if(value["command"].asString() == "authResponse"){
        if(value["status"].asString() == "true"){
            writeHashToFile(value["token"].asString());
            emit customClose();
            emit hashStatus(true);
            return;
        }
    }
    if(value["command"].asString() == "loginResponse"){
        if(value["status"].asString() == "true"){
            writeHashToFile(value["token"].asString());
            emit hashStatus(true);
            return;
        }
    }
    emit wrongCredentials();
    handler_->callRead();
}

void Register::writeCallback(std::shared_ptr<IConnectionHandler<Register> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{

}

void Register::init(const boost::system::error_code& erCode)
{
    handler_->callRead();
}

void Register::initializeConnection()
{
    handler_->getSocket().async_connect(ip::tcp::endpoint(ip::address::from_string(ip_), port_),std::bind(&Register::init,shared_from_this(),std::placeholders::_1));
}

bool Register::checkLoginData()
{
    std::fstream tokenFile {"tokenFile.bin"};
    if (!tokenFile.is_open()){
        return false;
    }
    std::stringstream ss;
    ss << tokenFile.rdbuf();
    tokenFile.close();
    Json::Value value;
    Json::FastWriter writer;
    Json::Reader reader;
    reader.parse(ss.str(), value);
    value["command"] = "auth";
    handler_->callWrite(writer.write(value));
    return true;
}

void Register::loginUser(QString login, QString password, QString command)
{
    Json::Value value;
    Json::FastWriter writer_;
    value["command"] = command.toStdString();
    login_ = login.toStdString();
    value["login"] = login_;
    value["password"] = password.toStdString();
    handler_->callWrite(writer_.write(value));
}

void Register::writeHashToFile(const std::string &hash)
{
    std::fstream tokenFile {"tokenFile.bin"};
    Json::Value valueToFile;
    tokenFile.open("tokenFile.bin", std::ios::out);
    valueToFile["login"] = login_;
    valueToFile["token"] = hash;
    tokenFile << valueToFile;
    tokenFile.close();
    return;
}
