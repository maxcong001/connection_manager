
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
