#pragma once
#include <unordered_set>
#include <queue>
#include <memory>
#include <unordered_map>
#include <list>
#include <tuple>
#include <atomic>
#include <thread>
#include "logger/logger.hpp"
#include "connManager/messagebus.h"

// this is for messagebus for conn
#define REM_CONN "rem_conn"

// this is for messagebus for pool
#define CONN_INC "conn_inc"
#define CONN_DEC "conn_dec"
// this is for messagebus for manager
#define POOL_INC "pool_inc"
#define POOL_DEC "pool_dec"

struct ConnInfo
{
    std::string sourceIP;
    std::string sourcePort;
    std::string destIP;
    std::string destPort;
    int type; // connection type(now we have 0 local, others remote)

    ConnInfo &operator=(const ConnInfo &info)
    {
        this->sourceIP = info.sourceIP;
        this->sourcePort = info.sourcePort;
        this->destIP = info.destIP;
        this->destPort = info.destPort;
        this->type = info.type;
        return *this;
    }

    bool operator==(const ConnInfo &rhs)
    {
        return !((this->sourceIP).compare(rhs.sourceIP)) && !((this->sourcePort).compare(rhs.sourcePort)) && !((this->destIP).compare(rhs.destIP)) && !((this->destPort).compare(rhs.destPort)) && this->type == rhs.type;
    }
    void dump()
    {
        __LOG(debug, "conn info ： \n"
                        << "type is : \n"
                        << ((!type) ? "local" : "remote"));
    }
};

