#pragma once
#include "connManager/util.h"
template <typename connInfo>
class connInterface
{
  public:
    typedef connInfo conn_type_t;
    connInterface(connInfo info)
    {
        __LOG(debug, "new connection! " << (void *)this);
    }
    connInterface(){};

    virtual ~connInterface() {}

    virtual bool
    connect(connInfo info) = 0;
    virtual bool disconnect() = 0;
    virtual void onConnected() final
    {
        // tell pool that there is a new connection
    }
    virtual void onDisconnected(int error) final
    {
        // tell pool that a connection is deleted
    }

    connInfo getConnInfo() { return _info; }

    connInfo _info;
};
template <typename connInfo>
class RedisConn : public connInterface<connInfo>
{
  public:
    RedisConn(connInfo info)
    {
        __LOG(debug, "new Redis connection! " << (void *)this);
    }
    bool connect(connInfo info) override { return true; }
    bool disconnect() override { return true; }
};
