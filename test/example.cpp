
#include "logger/logger.hpp"
#include "connManager/connManager.h"
#include "connManager/connInterface.h"

int main()
{
	set_log_level(logger_iface::log_level::debug);

	ConnInfo info;
	info.type = 0;

	connManager<RedisConn<ConnInfo>> *tmp_comm = new connManager<RedisConn<ConnInfo>>();
	tmp_comm->add_pool();
	tmp_comm->add_pool();
	tmp_comm->add_pool();
	tmp_comm->add_conn(info);
	tmp_comm->add_conn(info);

	for (int i = 0; i < 100; i++)
	{
		std::cout << tmp_comm->get_conn() << std::endl;
	}
}
