#pragma once 

#include <type_traits>
#include <utility>
#include <memory>

namespace util
{
    template<class F>
    struct function_traits;

// Function pointers
// std::string (*)()    
    template<class R>
    struct function_traits<R(*)()>
    {
        using return_type = R;
 
        static constexpr std::size_t arity = 0;
    };


    template<class R, typename... Args>
    struct function_traits<R(*)(Args...)>
    {
        using return_type = R;
 
        static constexpr std::size_t arity = 0;
    };
    
// Functors
// std::string ()(Args...)
    template<class R, class... Args>
    struct function_traits<R(Args...)>
    {
        using return_type = typename std::result_of<R(Args...)>::type;
 
        static constexpr std::size_t arity = sizeof...(Args);
 
        template <std::size_t N>
        struct argument
        {
            static_assert(N < arity, "error: invalid parameter index.");
            using type = typename std::tuple_element<N,std::tuple<Args...>>::type;
        };
    };


// Member function pointers
// std::string (A::*)(Args...)
    template<class C, class R, class... Args>
    struct function_traits<R(C::*)(Args...)>
    {
        using return_type = R;
    };
 
// Const member function pointers
// std::string (A::*)(Args...) const
    template<class C, class R, class... Args>
    struct function_traits<R(C::*)(Args...) const>
    {
        using return_type = R;
    };
 

    template<class F>
    struct function_traits<F&> : public function_traits<F>
    {};
 
    template<class F>
    struct function_traits<F&&> : public function_traits<F>
    {};
  
}
