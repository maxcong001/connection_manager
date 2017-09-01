#include <async/io_context.h>
#include <future>
#include <iostream>
#include <ctime>


using namespace IOService;
using namespace std;


io_context::io_context():
    _executor(new io_context::executor_type(_io_service))
{}


io_context::executor_type io_context::get_executor() noexcept
{
    return *_executor;
}

io_context::count_type io_context::run()
{
    _io_service.reset();
    boost::asio::io_service::work work(_io_service);
    return _io_service.run();
}

void io_context::stop()
{
    _io_service.stop();
}


io_context::executor_type::executor_type(boost::asio::io_service & io_service)
    : _io_service(io_service)
{}


void io_context::executor_type::invoke_later(std::function<void ()> func, std::chrono::milliseconds const & ms)
{
    std::shared_ptr<boost::asio::deadline_timer> t(new boost::asio::deadline_timer(_io_service, boost::posix_time::milliseconds(ms.count())));
    auto lambda = [func, t] (boost::system::error_code const &) -> void // Make a copy from deadline_timer
        {
            func();
        };
    t->async_wait(lambda);
}


void io_context::executor_type::invoke_at(std::function<void ()> func, std::time_t const & date)
{
    std::shared_ptr<boost::asio::deadline_timer> t(new boost::asio::deadline_timer(_io_service));
    auto lambda = [func, t] (boost::system::error_code const &) -> void // Make a copy from deadline_timer
        {
            func();
        };
    t->expires_at(boost::posix_time::from_time_t(date));
    t->async_wait(lambda);
}
