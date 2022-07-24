#include "mainwindow.h"

MainWindow::MainWindow(boost::asio::io_service &service, QObject *parent):
    service_{service},
    QObject{parent},
    ip_{"127.0.0.1"},
    port_{10678}
{
    handler_.reset(new ConnectionHandler<MainWindow>{ service_, *this});
    handler_->setAsyncReadCallback(&MainWindow::readCallback);
    handler_->setWriteCallback(&MainWindow::writeCallback);
}

MainWindow::~MainWindow()
{
    handler_->getSocket().close();
}

void MainWindow::readCallback(std::shared_ptr<IConnectionHandler<MainWindow> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{

}

void MainWindow::writeCallback(std::shared_ptr<IConnectionHandler<MainWindow> > handler, const boost::system::error_code &err, size_t bytes_transferred)
{

}

void MainWindow::init(const boost::system::error_code &erCode)
{
    handler_->callRead();
}

void MainWindow::startClose()
{
    emit customClose();
    emit restartSession();
}

void MainWindow::initializeConnection()
{
    handler_->getSocket().async_connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip_), port_),std::bind(&MainWindow::init,shared_from_this(),std::placeholders::_1));
}

void MainWindow::logout()
{
     QMetaObject::invokeMethod(this, "startClose",Qt::QueuedConnection);
}
