#pragma once

#include <memory>
#include <util/function_traits.h>

namespace util
{
    class NonCopyable
    {
    public:
        NonCopyable(NonCopyable const &) = delete;
        NonCopyable & operator=(NonCopyable const &) = delete;
    protected:
        NonCopyable() = default;
    };



    /**
     * Wraps the given (possibly) NonCopyable object and provides a Copyable object.
     */
    template <typename T>
    struct make_copyable
    {
        make_copyable() = default;
        
        make_copyable(make_copyable<T> const & other):
            _instance(std::move(other._instance))
        {
        }

        make_copyable(make_copyable<T> & other):
            _instance(std::move(other._instance))
        {
        }

        make_copyable & operator=(make_copyable<T> const & other)
        {
            _instance = std::move(other._instance);
        }
        
        make_copyable(make_copyable<T> && other):
            _instance(std::move(other._instance))
        {
        }

        make_copyable & operator=(make_copyable<T> && other)
        {
            _instance = std::move(other._instance);
        }
        

        template <typename U>
        make_copyable(U && u):
            _instance(std::move(u))
        {
        }
        
        T && operator*()
        {
            return std::move(_instance);
        }
        
        T && operator*() const
        {
            return std::move(_instance);
        }

    protected:
        mutable T _instance;
    };


    
    template <typename T>
    struct make_copyable_function
    {
        make_copyable_function() = default;
        
        make_copyable_function(make_copyable_function<T> const & other):
            _instance(std::move(other._instance))
        {
        }

        make_copyable_function(make_copyable_function<T> & other):
            _instance(std::move(other._instance))
        {
        }

        make_copyable_function & operator=(make_copyable_function<T> const & other)
        {
            _instance = std::move(other._instance);
        }
        
        make_copyable_function(make_copyable_function<T> && other):
            _instance(std::move(other._instance))
        {
        }

        make_copyable_function & operator=(make_copyable_function<T> && other)
        {
            _instance = std::move(other._instance);
        }
        

        template <typename U>
        make_copyable_function(U && u):
            _instance(std::move(u))
        {
        }
        
        T && operator*()
        {
            return std::move(_instance);
        }
        
        T && operator*() const
        {
            return std::move(_instance);
        }


        template <typename... Args>
        typename util::function_traits<T(Args...)>::return_type operator()(Args... args)
        {
            return _instance(std::forward<Args>(args)...);
        }

        template <typename... Args>
        typename util::function_traits<T(Args...)>::return_type operator()(Args... args) const
        {
            return _instance(std::forward<Args>(args)...);
        }

    protected:
        mutable T _instance;
    };
}
