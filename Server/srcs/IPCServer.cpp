#include "../includes/IPCServer.hpp"
#include <v1/commonapi/IPCProxy.hpp>

IPCServer::IPCServer()
{

}

IPCServer::~IPCServer()
{

}

void IPCServer::canDataMethod(const std::shared_ptr<CommonAPI::ClientId> _client, v1::commonapi::IPC::CanData _frame, canDataMethodReply_t _reply)
{
    std::cout << _frame.getRpm() << std::endl;
    _frame.setRpm(30);

    _reply(_frame);
}

void IPCServer::executeServer()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<IPCServer> myService =
    	std::make_shared<IPCServer>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;
}