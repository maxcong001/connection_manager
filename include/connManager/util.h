#pragma once
#include <unordered_set>
#include <queue>
#include <memory>
#include <unordered_map>
#include <list>
#include <tuple>
#include <atomic>
#include "logger/logger.hpp"
struct ConnInfo
{
    std::string sourceIP;
    std::string sourcePort;
    std::string destIP;
    std::string destPort;
    int type;// connection type(now we have 0 local, others remote)

    ConnInfo& operator =(const ConnInfo& info)
    {
        this->sourceIP = info.sourceIP;
        this->sourcePort = info.sourcePort;
        this->destIP = info.destIP;
        this->destPort = info.destPort;
        this->type = info.type;
        return *this;
    }    
};