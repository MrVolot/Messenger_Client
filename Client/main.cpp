#include <windowmanager.h>
#include <ioserviceworker.h>

int main(int argc, char *argv[]){
    windowManager obj{IoServiceWorker::getInstance().getService()};
}
