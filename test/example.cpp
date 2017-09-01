
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

	IOService::invoke_now([=] {
		tmp_comm->add_pool();
		tmp_comm->add_pool();
		tmp_comm->add_pool();
		tmp_comm->add_conn(info);
		tmp_comm->add_conn(info);
	});

	IOService::invoke_later([=] {
		for (int i = 0; i < 100; i++)
		{
			std::cout << tmp_comm->get_conn() << std::endl;
		}
	},
							1000);
	// wait here
	scheduler_thread.join();
}
