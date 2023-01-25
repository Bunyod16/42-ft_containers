#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
#include <iostream>
#include "iterator.hpp"

namespace ft {
template<typename _Tp, typename _Allocator = std::allocator<_Tp> >
class vector:
{
	public:
		typedef _Tp												value_type;
		typedef _Allocator										allocator_type;
		typedef typename	allocator_type::reference			reference;
		typedef typename	allocator_type::const_reference 	const_reference;
		typedef typename	allocator_type::pointer 			pointer;
		typedef typename	allocator_type::const_pointer		const_pointer;

		typedef MyIterator<value_type>						iterator;
		typedef MyIterator<const value_type>				const_iterator;
		// typedef VecIteratorRev<iterator>					reverse_iterator;
		// typedef VecIteratorRev<const_iterator>				const_reverse_iterator;

		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;

		// Constructors
		explicit vector (const allocator_type& alloc = allocator_type());
	
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

		// template <class InputIterator>
		// vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type last, const allocator_type &alloc = allocator_type());
		
		// template <class InputIterator>
		// vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value_type, void>::type* = nullptr);

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		
		vector (const vector &copy);
		
		// Destructor
		~vector() { }

		// Accessor
		vector &operator=(const vector& rhs)
		{}

		// Iterators
		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		reverse_iterator rbegin();
		
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		
		const_reverse_iterator rend() const;

		// Capacity
		size_type size() const;

		size_type max_size() const;

		void resize (size_type n, value_type val = value_type());

		size_type capacity() const;

		bool empty() const;

		void reserve(size_type n);

		//Element access
		reference operator[] (size_type n);

		const_reference operator[](size_type n) const;

		reference at(size_type n);

		const_reference at(size_type n) const;

		reference front();

		const_reference front() const;

		reference back();

		const_reference back() const;

		value_type *data();

		const value_type *data() const;

		// Modifiers
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);

		void assign (size_type n, const value_type &val);

		void push_back (const value_type &val);

		void pop_back();

		iterator insert (iterator position, const value_type &val);
		
		void insert (iterator position, size_type n, const value_type &val);

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);

		iterator erase(iterator position, iterator last);

		void swap(vector &x);

		void clear();

		//Non member function overloads
		template <class T, class Alloc>
		friend bool operator==(const ft::vector<T, Alloc>&rhs,
						const ft::vector<T, Alloc> &lhs);

		template <class T, class Alloc>
		friend bool operator!=(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

		template <class T, class Alloc>
		friend bool operator<(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);
		
		template <class T, class Alloc>
		friend bool operator<=(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

		template <class T, class Alloc>
		friend bool operator>(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

		template <class T, class Alloc>
		friend bool operator>=(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);




};
}
#endif