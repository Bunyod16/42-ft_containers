#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
#include <iostream>
#include "iterator.hpp"
#include <memory>

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename	allocator_type::reference			reference;
		typedef typename	allocator_type::const_reference 	const_reference;
		typedef typename	allocator_type::pointer 			pointer;
		typedef typename	allocator_type::const_pointer		const_pointer;

		typedef VecIterator<value_type>						iterator;
		typedef VecIterator<const value_type>				const_iterator;
		typedef VecRevIterator<iterator>					reverse_iterator;
		typedef VecRevIterator<const_iterator>				const_reverse_iterator;

		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;

		// Constructors
		explicit vector (const allocator_type& alloc = allocator_type()) : _allocator(alloc)
		{
			_data = nullptr;
			_size = 0;
			_capacity = 0;
			ReAlloc(2);
		};
	
		explicit vector (size_type count, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc)
		{
			_data = nullptr;
			_size = count;
			_capacity = count;
			ReAlloc(count);
			for (int x = 0; x < count; x++)
				_data[x] = val;
		};

		// template <class InputIterator>
		// vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type last, const allocator_type &alloc = allocator_type());
		
		// template <class InputIterator>
		// vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value_type, void>::type* = nullptr);

		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type());
		
		vector (const vector &copy);
		
		// Destructor
		~vector()
		{
			_allocator.deallocate(_data, _size);
		}

		// Accessor
		vector &operator=(const vector& rhs)
		{
			_allocator.deallocate(_data, _size);
			_allocator.allocate(rhs.size);
			// TODO, TRAVERSE THRU
		}

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
		size_type size() const { return _size; };

		size_type max_size() const;

		void resize (size_type n, value_type val = value_type());

		size_type capacity() const;

		bool empty() const;

		void reserve(size_type n);

		//Element access
		reference operator[] (size_type n)
		{
			if (n >= _size)
			{
				throw (std::out_of_range("index out of range"));
			}
			return _data[n];
		}

		const_reference operator[](size_type n) const
		{
			if (n >= _size)
			{
				throw (std::out_of_range("index out of range"));
			}
			return _data[n];
		}

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

		void push_back (const value_type &val)
		{
			if (_size >= _capacity)
				ReAlloc(_capacity + _capacity / 2);
			_data[_size++] = val;
		}

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
		template <class Tp, class Alloc>
		friend bool operator==(const ft::vector<T, Alloc>&rhs,
						const ft::vector<T, Alloc> &lhs);

		template <class Tp, class Alloc>
		friend bool operator!=(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

		template <class Tp, class Alloc>
		friend bool operator<(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);
		
		template <class Tp, class Alloc>
		friend bool operator<=(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

		template <class Tp, class Alloc>
		friend bool operator>(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

		template <class Tp, class Alloc>
		friend bool operator>=(const std::vector<T, Alloc> &rhs,
								const std::vector<T, Alloc> &lhs);

	private:
		void ReAlloc(size_t newCapacity)
		{
			T* newBlock = _allocator.allocate(newCapacity);

			size_t size = _size;
			if (newCapacity < size)
				_size = newCapacity;

			for (size_t i = 0; i < _size; i++)
				newBlock[i] = _data[i];

			delete[] _data;
			_data = newBlock;
			_capacity = newCapacity;
		}

	private:
		allocator_type _allocator;
		pointer _data;
		size_t _size;
		size_t _capacity;


};
}
#endif