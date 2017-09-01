#pragma once

#include <memory>
#include <chrono>
#include <async/io_context.h>

namespace IOService
{

    class Scheduler: public io_context
    {
    public:
        ~Scheduler() = default;

        static Scheduler & instance();
        void destroy();

    protected:
        Scheduler();

    private:
        static std::unique_ptr<Scheduler> _instance;
    };


    inline void invoke_now(std::function<void ()> func)
    {
        Scheduler::instance().get_executor().post(func);
    }

    inline void invoke_later(std::function<void ()> func, std::chrono::milliseconds const & ms)
    {
        Scheduler::instance().get_executor().invoke_later(func, ms);
    }


    inline void invoke_later(std::function<void ()> func, uint32_t ms)
    {
        invoke_later(func, std::chrono::milliseconds(ms));
    }


    inline void invoke_at(std::function<void ()> func, std::time_t const & date)
    {
        Scheduler::instance().get_executor().invoke_at(func, date);
    }

}
