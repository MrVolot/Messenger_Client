#include <windowmanager.h>
#include <boost/asio.hpp>
#include <ioserviceworker.h>

int main(int argc, char *argv[]){
    windowManager obj{IoServiceWorker::getInstance().getService()};
}
