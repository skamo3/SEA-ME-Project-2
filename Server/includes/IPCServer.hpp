#ifndef IPCSERVER_H_
#define IPCSERVER_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/IPCStubDefault.hpp>

class IPCServer: public v1_0::commonapi::IPCStubDefault {

public:
    IPCServer();
    virtual ~IPCServer();

    virtual void canDataMethod(const std::shared_ptr<CommonAPI::ClientId> _client,
    v1::commonapi::IPC::CanData _frame, canDataMethodReply_t _reply);

    void executeServer();

};

#endif
