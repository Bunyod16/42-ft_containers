#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
#include <iostream>
#include "iterator.hpp"
#include <memory>
#include <vector>


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
		// is yours different?
		//yes as i creating class iterator twice without using inheritance.
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
	
	private:
		allocator_type _allocator;
		pointer _data;
		size_t _size;
		size_t _capacity;
	
	public:
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
			if (_size == 0)
				return (begin());

			return (iterator(begin() + _size));
		}

		const_iterator end() const
		{
			if (_size == 0)
				return (begin());

			return (const_iterator(begin() + _size));
		}

		reverse_iterator rbegin()
		{
			// both is using this. 
			// reverse_iterator become const_reverse_iterator.
			//begin() give vectoriter trigger
			// then construvt rev_iterator will output both vectoriter triggrr & triggered 2
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
			// delete[] _data;
			clear();
			// _data = _allocator.allocate(_capacity);
			_allocator.deallocate(_data, _capacity);
		}

		// Accessor
		vector &operator=(const vector& rhs)
		{
			clear(); //check if stops here
			// _allocator.allocate(rhs.size());
			for (const_iterator it = rhs.begin(); it != rhs.end(); it++)
				push_back(*it);
			return *this;
		}

		// Capacity
		size_type size() const
		{
			return _size; 
		};
		
		size_type max_size() const
		{
			if (std::is_same<T, char>::value || std::is_same<T, unsigned char>::value) { return _allocator.max_size() / 2; }

			return (_allocator.max_size());
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
				for (; n != _size; pop_back());
			else if (n > _size)
				for (; n != _size; push_back(val));
		}
		
		size_type capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return (_size == 0 ? true : false);
		}

		void reserve(size_type n)
		{
			if (n > _capacity)
				ReAlloc(n);
		}

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

		reference at(size_type n)
		{
			if (n >= _size)
				throw (std::out_of_range("index out of range"));
			return _data[n];
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw (std::out_of_range("index out of range"));
			return _data[n];
		}

		reference front()
		{
			return (_data[0]);
		}

		const_reference front() const
		{
			return (_data[0]);
		}

		reference back()
		{
			return (_data[_size - 1]);
		}

		const_reference back() const
		{
			return (_data[_size - 1]);
		}

		value_type *data()
		{
			return _data;
		}

		const value_type *data() const
		{
			return _data;
		}

		// Modifiers
		template <class InputIterator>
		void assign (InputIterator first, typename enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type last)
		{
			clear();
			for (; first != last; first++) {
				push_back(*first);
			}
		}

		void assign (size_type n, const value_type &val)
		{
			clear();
			if (n > _capacity)
				ReAlloc(n);
			for (unsigned int x = 0; x < n; x++) {
				_allocator.construct(_data + x, val);
			}
			_size = n;
		}

		void push_back (const value_type &val)
		{
			if (_size >= _capacity) {
				ReAlloc(_capacity + _capacity / 2);
			}
			_allocator.construct(_data + _size++, val);
		}

		void pop_back()
		{
			if (!empty())
			{
				_size--;
				_allocator.destroy(_data + _size);
			}
		}

		iterator insert (iterator pos, const value_type &val)
		{
			size_type index = pos - begin();
			if (_size == _capacity) {
				reserve(_capacity * 2);
			}
			pos = begin() + index;
			for (iterator head = end(); head != pos; --head) {
				*head = *(head - 1);
			}
			*pos = val;
			++_size;
			return (pos);
		}
		
		void insert (iterator pos, size_type n, const value_type &val)
		{
			while (n--) {
				pos = insert(pos, val);
			}
		}

		template <class InputIterator>
		void insert(iterator pos, typename enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type first, InputIterator last)
		{
			while (first != last) {
				pos = insert(pos, *first);
				pos = pos + 1;
				first++;
			}
		}

		iterator erase(iterator position)
		{
			if (position == end() - 1)
			{
				pop_back();
				return (end());
			}
			
			size_t	dist	= std::distance(position, end() - 1);

			if (!dist)
				return position;

			while (position != end() - 1)
			{
				_allocator.destroy(&(*position));
				_allocator.construct(&(*position), *(++position));
			}
			_size--;
			_allocator.destroy(_data + _size);
			return (position - dist);
		}

		iterator erase(iterator position, iterator last)
		{
			if (position == end() - 1)
			{
				pop_back();
				return (end());
			}
			
			size_t	dist	= std::distance(position, last);
			if (!dist)
				return position;
			//dont give a shit and delete position to last)
			// shift the next stuff till end() position - last addresses back
			int offset = 0;
			while (position != end())
			{
				if (position < last)
				{
					_allocator.destroy(&(*position));
					// if (end() == position + 1)
						// break; // allocate more space if need to move more
					_allocator.construct(&(*position), *(position++ + dist));
				}
				else
				{
					offset++;
					_allocator.construct(&(*position), *(position++ + dist));
				}
			}
			_size = _size - dist;
			_allocator.destroy(_data + _size);
			return ((position - offset) - dist);
		}

		void swap(vector &other)
		{
			std::swap(_data, other._data);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
		}

		void clear()
		{
			while (_size > 0)
				pop_back();
		}

		//Non member function overloads
	
		template <class _Tp, class _Alloc>
		friend bool operator==(const vector<_Tp, _Alloc>&rhs,
						const vector<_Tp, _Alloc> &lhs)
		{
			if (lhs._size != rhs._size)
				return false;
			for (unsigned int i = 0; i < lhs.size(); i++) {
                if (lhs.at(i) != rhs.at(i))
					return false;
            }
            return true;
		}

		template <class _Tp, class _Alloc>
		friend bool operator!=(const vector<_Tp, _Alloc> &rhs,
								const vector<_Tp, _Alloc> &lhs)
		{
			if (lhs._size != rhs._size)
				return true;
			for (unsigned int i = 0; i < lhs.size(); i++) {
                if (lhs.at(i) != rhs.at(i))
					return true;
            }
            return false;
		}

		template <class _Tp, class _Alloc>
		friend bool operator<(const vector<_Tp, _Alloc> &lhs,
								const vector<_Tp, _Alloc> &rhs)
		{
			return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
		
		template <class _Tp, class _Alloc>
		friend bool operator<=(const vector<_Tp, _Alloc> &lhs,
								const vector<_Tp, _Alloc> &rhs)
		{
			return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
		}

		template <class _Tp, class _Alloc>
		friend bool operator>(const vector<_Tp, _Alloc> &lhs,
								const vector<_Tp, _Alloc> &rhs)
		{
			return (rhs < lhs);
		}

		template <class _Tp, class _Alloc>
		friend bool operator>=(const vector<_Tp, _Alloc> &lhs,
								const vector<_Tp, _Alloc> &rhs)
		{
			return (!(lhs < rhs));
		}

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

			T* tempHead = newBlock;
			for (iterator i = begin(); i != end(); i++)
				_allocator.construct(tempHead++, *i);

			for (iterator i = begin(); i != end(); i++)
				_allocator.destroy(&(*i));
		
			_allocator.deallocate(_data, _capacity);
			_data = newBlock;
			_capacity = newCapacity;
		}
		
};

}
#endif