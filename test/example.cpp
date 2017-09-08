
#include "logger/logger.hpp"
#include "connManager/connManager.h"
#include "connManager/connInterface.h"
#include "async/scheduler.h"
#include <thread>
#include <unistd.h>

int main()
{
	set_log_level(logger_iface::log_level::debug);
	// start IO service
	IOService::Scheduler &scheduler = IOService::Scheduler::instance();

	std::thread scheduler_thread([&scheduler] {
		std::cout << "start a new thread to run boost io_service!" << std::endl;
		scheduler.run();
		std::cout << "should not run here" << std::endl;
	});

	// now for connection manager
	ConnInfo info;
	info.type = 0;

	connManager<RedisConn<ConnInfo>> *tmp_comm = new connManager<RedisConn<ConnInfo>>();

	tmp_comm->add_pool();
	tmp_comm->add_pool();
	tmp_comm->add_pool();
	tmp_comm->add_conn(info);
	tmp_comm->add_conn(info);

	// disconnect 3 connection
	for (int i = 0; i < 5; i++)
	{
		auto tmp = tmp_comm->get_conn();
		if (tmp == nullptr)
		{
			__LOG(error, "no conn in the list!!");
		}
		else
		{
			__LOG(warn, "got one conection, connection status is " << tmp->get_conn_state());
			tmp->onDisconnected(1);
		}
	}
#if 0
	//	tmp_comm->del_conn(info);
	for (int i = 0; i < 2; i++)
	{
		auto tmp = tmp_comm->get_conn();
		if (tmp == nullptr)
		{
			__LOG(error, "no conn in the list!!");
		}
		else
		{
			std::cout << "got one conection, connection status is " << tmp->get_conn_state() << std::endl;
			tmp->onDisconnected(1);
		}
	}
#endif
	//	now there is one connection
	__LOG(error, "001!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	{
		auto tmp = tmp_comm->get_conn();
		if (tmp == nullptr)
		{
			__LOG(error, "no conn in the list!!");
		}
		else
		{
			std::cout << "got one conection, connection status is " << tmp->get_conn_state() << std::endl;
			//tmp->onDisconnected(1);
		}
	}

	__LOG(error, "002!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
	{
		auto tmp = tmp_comm->get_conn();
		if (tmp == nullptr)
		{
			__LOG(error, "no conn in the list!!");
		}
		else
		{
			std::cout << "got one conection, connection status is " << tmp->get_conn_state() << std::endl;
			tmp->onDisconnected(1);
		}
	}

	
	__LOG(error, "003!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

	for (int i = 0; i < 3; i++)
	{
		auto tmp = tmp_comm->get_conn();
		if (tmp == nullptr)
		{
			__LOG(error, "no conn in the list!!");
		}
		else
		{
			std::cout << "got one conection, connection status is " << tmp->get_conn_state() << std::endl;
			tmp->onDisconnected(1);
		}
	}

	__LOG(warn, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

	auto tmp = tmp_comm->get_conn();
	if (tmp == nullptr)
	{
		__LOG(error, "no conn in the list!!");
	}
	else
	{
		std::cout << "got one conection, connection status is " << tmp->get_conn_state() << std::endl;
		tmp->onDisconnected(1);
	}

	// wait here
	scheduler_thread.join();
}
