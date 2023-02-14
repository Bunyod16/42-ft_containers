#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <iostream>
#include "iterator.hpp"
#include "rbt.hpp"

namespace ft
{

template<class Key, class T, class Compare = std::less<Key>,class Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
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
		typedef size_t size_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			protected:
				Compare comp;

			public:
				value_compare(Compare c) : comp(c) {};

				bool operator()( const value_type& lhs, const value_type& rhs ) const
				{
					return (comp(lhs.first, rhs.first));
				}

		};

		typedef ft::RBTree<ft::pair<const key_type, mapped_type>, value_compare, allocator_type> tree_type;
		typedef typename tree_type::node_pointer node_pointer;
		typedef typename tree_type::iterator	tree_iterator;
	
		private:
			tree_type		_rbt;
			allocator_type	_alloc;
			key_compare		_key_compare;

		//Member Functions
		//default
		public:
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
					_rbt(comp, alloc),
					_alloc(alloc),
					_key_compare(comp) {}

			// template< class InputIt >
			// map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {};

			// map( const map& other ) {};

			~map() {};

			map& operator=( const map& other );

			allocator_type get_allocator() const;

			// Element access
			T& at( const Key& key );

			const T& at( const Key& key ) const;

			T& operator[]( const Key& key )
			{
				tree_iterator it(_rbt.get_root());

				while(it != _rbt.end())
				{
					if (it._ptr->_data.first == key)
						return it._ptr->_data.second;
					it++;
				}

				iterator result = insert(ft::make_pair(key, mapped_type())).first;
				return ((*result).second);
			};

			//Capacity
			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			//Modifiers
			void clear();

			ft::pair<iterator, bool> insert( const value_type& value ) {
				node_pointer node;
				node = _rbt.insert(value);
				return (ft::make_pair(iterator(&node->_data), true)); //TODO unhardcode
			};

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

			ft::pair<iterator,iterator> equal_range( const Key& key );

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

			iterator lower_bound( const Key& key );

			const_iterator lower_bound( const Key& key ) const;

			iterator upper_bound( const Key& key );

			const_iterator upper_bound( const Key& key ) const;

			key_compare key_comp() const;

			map::value_compare value_comp() const;
};
		template< class K, class V, class Comp, class Alloc >
		bool operator==( const map<K,V,Comp,Alloc>& lhs,
						 const map<K,V,Comp,Alloc>& rhs );
			
		template< class K, class V, class Comp, class Alloc >
		bool operator!=( const map<K,V,Comp,Alloc>& lhs,
						 const map<K,V,Comp,Alloc>& rhs );

		template< class K, class V, class Comp, class Alloc >
		bool operator<( const map<K,V,Comp,Alloc>& lhs,
						const map<K,V,Comp,Alloc>& rhs );

		template< class K, class V, class Comp, class Alloc >
		bool operator<=( const map<K,V,Comp,Alloc>& lhs,
						 const map<K,V,Comp,Alloc>& rhs );

		template< class K, class V, class Comp, class Alloc >
		bool operator>( const map<K,V,Comp,Alloc>& lhs,
						const map<K,V,Comp,Alloc>& rhs );

		template< class K, class V, class Comp, class Alloc >
		bool operator>=( const map<K,V,Comp,Alloc>& lhs,
						 const map<K,V,Comp,Alloc>& rhs );

		template< class K, class V, class Comp, class Alloc >
		void swap( std::map<K,V,Comp,Alloc>& lhs,
				std::map<K,V,Comp,Alloc>& rhs );
}
#endif