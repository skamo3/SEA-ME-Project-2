#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/IPCProxy.hpp>

using namespace v1_0::commonapi;

int main() {
    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
    std::shared_ptr<IPCProxy<>> myProxy =
    	runtime->buildProxy<IPCProxy>("local", "test");

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    IPC::CanData canFrame;
    myProxy->canDataMethod(1, callStatus, canFrame);
    std::cout << "Got message: '" << canFrame.getRpm() << "'\n";
    return 0;
}
