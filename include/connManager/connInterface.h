#pragma once
#include "connManager/util.h"
template <typename connInfo>
class connInterface
{
  public:
    connInterface(ConnInfo info)
    {
        __LOG(debug, "new connection! "<<(void*)this);
    }
    connInterface(){};

    bool connect(ConnInfo info){return true;};
    ConnInfo _info;

};