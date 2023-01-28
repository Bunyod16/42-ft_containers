#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
#include <iostream>
#include "iterator.hpp"
#include <memory>

namespace ft {

template <typename G>
bool comp(G a, G b)
{
	return (a == b);
}

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
			_size = 0;
			Alloc(2);
		};
	
		explicit vector (size_type count, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc)
		{
			_size = 0;
			Alloc(count);
			for (unsigned int x = 0; x < _capacity; x++)
				push_back(val);
		};

		//enable_if is here because otherwise when you want to use something like vector(10, 100) to fill it up, it will match with the constructor below
		template <class InputIterator>
		vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type last, const allocator_type &alloc = allocator_type()) : _allocator(alloc)
		{
			_size = 0;
			Alloc(2);
			for(; first != last; first++)
			{
				push_back(*first);
			}
		}
		
		vector (const vector &copy)
		{
			_size = 0;
			Alloc(2);
			vector::const_iterator beg = copy.begin();
			vector::const_iterator end = copy.end();

			for(; beg != end; beg++)
			{
				push_back(*beg);
			}
		}
		
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
		iterator begin()
		{
			return (iterator(_data));
		}

		const_iterator begin() const
		{
			return (const_iterator(_data));
		}

		iterator end()
		{
			return (iterator(begin() + _size));
		}

		const_iterator end() const
		{
			return (const_iterator(begin() + _size));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(begin() + _size));
		}
		
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(begin() + _size));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

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
			if (_size >= _capacity) {
				ReAlloc(_capacity + _capacity / 2);
			}
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
	
		template <class _Tp, class _Alloc>
		friend bool operator==(const vector<_Tp, _Alloc>&rhs,
						const vector<_Tp, _Alloc> &lhs)
		{
			if (lhs._size == rhs._size)
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), ft::comp<typename vector<_Tp, _Alloc>::value_type>);
			return false;
		}

		template <class _Tp, class _Alloc>
		friend bool operator!=(const vector<_Tp, _Alloc> &rhs,
								const vector<_Tp, _Alloc> &lhs)
		{
			return (!(rhs == lhs));
		}

		template <class _Tp, class _Alloc>
		friend bool operator<(const vector<_Tp, _Alloc> &rhs,
								const vector<_Tp, _Alloc> &lhs);
		
		template <class _Tp, class _Alloc>
		friend bool operator<=(const vector<_Tp, _Alloc> &rhs,
								const vector<_Tp, _Alloc> &lhs);

		template <class _Tp, class _Alloc>
		friend bool operator>(const vector<_Tp, _Alloc> &rhs,
								const vector<_Tp, _Alloc> &lhs);

		template <class _Tp, class _Alloc>
		friend bool operator>=(const vector<_Tp, _Alloc> &rhs,
								const vector<_Tp, _Alloc> &lhs);

	private:
		void Alloc(size_t initCapacity)
		{
			_data = _allocator.allocate(initCapacity);
			_capacity = initCapacity;
		}
		
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