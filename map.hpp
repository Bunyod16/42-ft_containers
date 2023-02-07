#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <iostream>
#include "iterator.hpp"
#include "rbt.hpp"

namespace ft
{

template<class Key, class T, class Compare = std::less<Key>,class Allocator = std::allocator<std::pair<const Key, T> > >
class map
{
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::VecIterator<value_type> iterator;
        typedef ft::VecIterator<const value_type> const_iterator;
        typedef ft::VecRevIterator<iterator> reverse_iterator;
        typedef ft::VecRevIterator<const iterator> const_reverse_iterator;

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            protected:
                Compare comp;

            public:
                value_compare(Compare c) : comp(c) {};

                bool operator()( const value_type& lhs, const value_type& rhs ) const
                {
                    comp(lhs.first, rhs.first);
                }

        };

        typedef ft::RBTree<value_type, Compare, Allocator>

        //Member Functions
        map();

        explicit map(const Compare &comp, const Allocator &alloc = Allocator() );

        template< class InputIt >
        map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() );

        map( const map& other );

        ~map();

        map& operator=( const map& other );

        allocator_type get_allocator() const;

        // Element access
        T& at( const Key& key );
        
        const T& at( const Key& key ) const;

        T& operator[]( const Key& key );

        //Capacity
        bool empty() const;

        size_type size() const;

        size_type max_size() const;

        //Modifiers
        void clear();

        std::pair<iterator, bool> insert( const value_type& value );

        template< class InputIt >
        void insert( InputIt first, InputIt last );

        iterator erase( iterator pos );

        iterator erase( iterator first, iterator last );

        size_type erase( const Key& key );

        void swap( map& other );

        //Lookup
        size_type count( const Key& key ) const;

        iterator find( const Key& key );

        const_iterator find( const Key& key ) const;

        std::pair<iterator,iterator> equal_range( const Key& key );

        std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

        iterator lower_bound( const Key& key );
        
        const_iterator lower_bound( const Key& key ) const;

        iterator upper_bound( const Key& key );

        const_iterator upper_bound( const Key& key ) const;

        key_compare key_comp() const;

        map::value_compare value_comp() const;
        
        template< class Key, class T, class Compare, class Alloc >
        bool operator==( const map<Key,T,Compare,Alloc>& lhs,
                         const map<Key,T,Compare,Alloc>& rhs );
        	
        template< class Key, class T, class Compare, class Alloc >
        bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
                         const map<Key,T,Compare,Alloc>& rhs );

        template< class Key, class T, class Compare, class Alloc >
        bool operator<( const map<Key,T,Compare,Alloc>& lhs,
                        const map<Key,T,Compare,Alloc>& rhs );

        template< class Key, class T, class Compare, class Alloc >
        bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
                         const map<Key,T,Compare,Alloc>& rhs );

        template< class Key, class T, class Compare, class Alloc >
        bool operator>( const map<Key,T,Compare,Alloc>& lhs,
                        const map<Key,T,Compare,Alloc>& rhs );

        template< class Key, class T, class Compare, class Alloc >
        bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
                         const map<Key,T,Compare,Alloc>& rhs );

        template< class Key, class T, class Compare, class Alloc >
        void swap( std::map<Key,T,Compare,Alloc>& lhs,
                std::map<Key,T,Compare,Alloc>& rhs );
    
    private:
        ft::RBTree<ft::pair<key_type, mapped_type> > _rbt;
        Compare                                     _key_compare;
};
}
#endif