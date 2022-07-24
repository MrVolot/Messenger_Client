#include "register.h"
#include "../Json/json/json.h"
#include <fstream>
#include <Commands.h>

#include <QSysInfo>
#include <QStorageInfo>
#include <QNetworkInterface>
#include <QSettings>
#include <QProcess>

Register::Register(boost::asio::io_service& service, QObject *parent)
    : service_{service},
      QObject{parent},
      ip_{"127.0.0.1"},
      port_{10679}
{
    handler_.reset(new ConnectionHandler<Register>{ service_, *this});
    handler_->setAsyncReadCallback(&Register::readCallback);
    handler_->setWriteCallback(&Register::writeCallback);
}

Register::~Register()
{
    handler_->getSocket().close();
}

void Register::writeCallback(std::shared_ptr<IConnectionHandler<Register> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{

}

void Register::readCallback(std::shared_ptr<IConnectionHandler<Register> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{
    serverResponseString.erase();
    serverResponseString = boost::asio::buffer_cast<const char*>(handler->getStrBuf()->data());
    cv.notify_all();
}

void Register::init(const boost::system::error_code& erCode)
{
    if(erCode){
        qDebug()<<erCode.message().c_str();
    }
}

void Register::initializeConnection()
{
    handler_->getSocket().async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip_), port_),std::bind(&Register::init,shared_from_this(),std::placeholders::_1));
}

unsigned int Register::checkServerResponse()
{
    Json::Value value;
    Json::Reader reader;
    reader.parse(serverResponseString, value);
    return value["command"].asInt();
}

unsigned int Register::checkLoginData()
{
    Json::Value value;
    Json::FastWriter writer;
    value["command"] = "auth";
    value["deviceId"] = createDeviceId();
    handler_->callWrite(writer.write(value));
    handler_->callAsyncRead();
    std::unique_lock<std::mutex> locker{mtx};
    cv.wait(locker);
    return checkServerResponse();
}

unsigned int Register::loginUser(const QString& login, const QString& password, const QString& command)
{
    Json::Value value;
    Json::FastWriter writer_;
    value["command"] = command.toStdString();
    value["login"] = login.toStdString();
    value["deviceId"] = createDeviceId();
    value["password"] = password.toStdString();
    handler_->callWrite(writer_.write(value));
    handler_->callAsyncRead();
    std::unique_lock<std::mutex> locker{mtx};
    cv.wait(locker);
    return checkServerResponse();
}

std::string Register::createDeviceId()
{
    std::string id{QSysInfo::currentCpuArchitecture().toLocal8Bit().constData()};
    id.append(QSysInfo::prettyProductName().toLocal8Bit().constData() );
    id.append(QSysInfo::kernelType().toLocal8Bit().constData());
    id.append(QSysInfo::kernelVersion().toLocal8Bit().constData());
    id.append(QSysInfo::machineHostName().toLocal8Bit().constData());
    return id;
}
