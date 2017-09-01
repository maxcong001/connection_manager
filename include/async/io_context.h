#pragma once
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>


namespace IOService
{
    /*
     * Derived from "C++ Extensions for Networking" Technical Specification n4625 (2016-11-28)
     * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/n4625.pdf
     */
    class io_context
    {
    public:
        class executor_type;
        typedef uint32_t count_type;

        io_context();
        io_context(io_context const &) = delete;
        io_context & operator=(io_context const &) = delete;
        virtual ~io_context() = default;

        executor_type get_executor() noexcept;
        count_type run();
        void stop();
    private:
        boost::asio::io_service _io_service;
        std::unique_ptr<executor_type> _executor;
    };


    class io_context::executor_type
    {
    public:
        executor_type(boost::asio::io_service & io_service);
        executor_type(executor_type const & other) noexcept = default;
        executor_type(executor_type && other) noexcept = default;
        executor_type & operator=(executor_type const & other) noexcept;
        executor_type & operator=(executor_type && other) noexcept;


        template<class Func, class ProtoAllocator = std::allocator<void> >
        void post(Func && f, ProtoAllocator const & a = std::allocator<void>()) const;
        void invoke_later(std::function<void ()> func, std::chrono::milliseconds const & ms);
        void invoke_at(std::function<void ()> func, std::time_t const & date);

    private:
        boost::asio::io_service & _io_service;
    };

    template<class Func, class ProtoAllocator>
    void io_context::executor_type::post(Func && f, ProtoAllocator const & a) const
    {
        _io_service.post(f);
    }
}
