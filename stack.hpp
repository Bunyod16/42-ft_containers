#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {

template<class T, class Container = ft::vector<T> >
class stack
{   
    public:
        typedef T           value_type;
        typedef Container   container_type;
        typedef size_t      size_type;

    private:
        container_type _container;

    public:
    explicit stack(const container_type &ctnr = container_type()) : _container(ctnr)
    {

    }

    stack(const stack &other) : _container(other._container)
    {

    }

    ~stack() {}
    bool empty() const
    {
        return (_container.empty());
    }
    
    size_type size() const
    {
        return (_container.size());
    }

    value_type& top()
    {
        return (_container.back());
    }
    
    const value_type& top() const
    {
        return (_container.back());
    }

    void push (const value_type& val)
    {
        return (_container.push_back(val));
    }

    void pop()
    {
        _container.pop_back();
    }

    friend bool operator==( const ft::stack<T, Container>& lhs,
                     const ft::stack<T, Container>& rhs )
    {
        return (lhs._container == rhs._container);
    }
    
    friend bool operator!=( const ft::stack<T, Container>& lhs,
                     const ft::stack<T, Container>& rhs )
    {
        return (lhs._container != rhs._container);
    }
    
    template< class Tt, class Ccontainer >
    friend bool operator< ( const ft::stack<Tt, Ccontainer>& lhs,
                     const ft::stack<Tt, Ccontainer>& rhs )
    {
        return (lhs._container < rhs._container);
    }
    
    template< class Tt, class Ccontainer >
    friend bool operator<=( const ft::stack<Tt, Ccontainer>& lhs,
                     const ft::stack<Tt, Ccontainer>& rhs )
    {
        return (lhs._container <= rhs._container);
    }
    
    template< class Tt, class Ccontainer >
    friend bool operator> ( const ft::stack<Tt, Ccontainer>& lhs,
                     const ft::stack<Tt, Ccontainer>& rhs )
    {
        return (lhs._container > rhs._container);
    }
    
    template< class Tt, class Ccontainer >
    friend bool operator>=( const ft::stack<Tt, Ccontainer>& lhs,
                     const ft::stack<Tt, Ccontainer>& rhs )
    {
        return (lhs._container >= rhs._container);
    }
};


}
#endif