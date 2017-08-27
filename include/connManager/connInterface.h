#pragma once
#include "connManager/util.h"
template <typename connInfo>
class connInterface
{
  public:
    connInterface(ConnInfo info)
    {
        __LOG(debug, "new connection! " << (void *)this);
    }
    connInterface(){};

    virtual bool connect(ConnInfo info) = 0;
    virtual bool disconnect() = 0;
    virtual void onConnected() final {}
    virtual void onDisconnected(int error) final {}
    ConnInfo _info;
};
template <typename connInfo>
class RedisConn : public connInterface<connInfo>
{
public:
    RedisConn(ConnInfo info)
    {
        __LOG(debug, "new Redis connection! " << (void *)this);
    }
    bool connect(ConnInfo info) override { return true; }
    bool disconnect() override { return true; }
};
