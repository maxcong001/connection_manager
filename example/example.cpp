/*
 * Copyright (c) 2016-20017 Max Cong <savagecm@qq.com>
 * this code can be found at https://github.com/maxcong001/connection_manager
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "logger/logger.hpp"
#include "connManager/connManager.h"
#include "connManager/messagebus.h"

int main()
{
    set_log_level(logger_iface::log_level::debug);
    __LOG(error, "hello logger!"
                     << "this is error log");
    __LOG(warn, "hello logger!"
                    << "this is warn log");
    __LOG(info, "hello logger!"
                    << "this is info log");
    __LOG(debug, "hello logger!"
                     << "this is debug log");
    std::string tmp001("test");
    std::string tmp002("test");
#if 0
    int a = 0;
    auto bus = message_bus<int>::instance();
    bus->register_handler(tmp001, &a, [](void *objp, void *msgp) { std::cout << "objp is : " << (void *)objp << " msgp is : " << (void *)msgp << std::endl; });
    bus->register_handler(tmp002, &a, [](void *objp, void *msgp) { std::cout << "objp isxxxx : " << (void *)objp << " msgp is : " << (void *)msgp << std::endl; });
    bus->call(tmp002, (void *)0);
    bus->call(tmp001, (void *)0);
    bus->remove_handler("test", &a);
    bus->call("test", (void *)0);
#endif
}
