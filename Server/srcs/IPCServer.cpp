#include "../includes/IPCServer.hpp"
#include <v1/commonapi/IPCProxy.hpp>

IPCServer::IPCServer()
{

}

IPCServer::~IPCServer()
{

}

void IPCServer::canDataMethod(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _id, canDataMethodReply_t _reply)
{
}