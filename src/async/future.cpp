#include <async/future.h>

namespace IOService
{
    namespace detail
    {
    }

    future<void>::future():
        _shared_state(new detail::future_shared_state<void>)
    {
    }

    IOService::future<void>::future(std::shared_ptr<detail::future_shared_state<void>> const & shared_state)
    {
        _shared_state = shared_state;
    }

    void IOService::future<void>::get()
    {
        if (!_shared_state->_valid)
        {
            std::unique_lock<std::mutex> ul(_shared_state->_mutex);
            _shared_state->_cv.wait(ul);
            _shared_state->_valid = false;
        }
        if (_shared_state->_ex_ptr != nullptr)
        {
            std::rethrow_exception(_shared_state->_ex_ptr);
        }
        
        return;
    }
    

    bool IOService::future<void>::valid() const
    {
        return _shared_state->_valid;
    }

    
    void IOService::detail::future_shared_state<void>::set_value()
    {
        {
            std::lock_guard<std::mutex> lg(_mutex);
            _valid = true;
        }
        notify();
    }

    
    void IOService::detail::future_shared_state<void>::set_exception(std::exception_ptr p)
    {
        {
            std::lock_guard<std::mutex> lg(_mutex);
            _ex_ptr = p;
            _valid = true;
        }
        notify();
    }
    

    
    void IOService::detail::future_shared_state<void>::notify()
    {
        if (_then)
        {
            std::shared_ptr<IOService::detail::future_shared_state<void>> wrapper(this->shared_from_this());
            Scheduler::instance().get_executor().post(
                [=] () mutable
                {
                    _then(std::move(IOService::future<void>(wrapper)));
                    _valid = false;
                } );
        }
        else
        {
            _cv.notify_all();
        }
    }

    


    IOService::future<void> promise<void>::get_future()
    {
        if (2 == _future._shared_state.use_count())
        {
            throw std::future_error(std::make_error_code(std::future_errc::future_already_retrieved));
        }
        IOService::future<void> fut(_future._shared_state);
        return std::move(fut);
    }

    void promise<void>::set_value()
    {
        _future._shared_state->set_value();
    }

    
    void promise<void>::set_exception(std::exception_ptr p)
    {
        _future._shared_state->set_exception(p);
    }


    
    
}
