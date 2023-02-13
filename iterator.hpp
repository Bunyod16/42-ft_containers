#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <iostream>
#include "map"

namespace ft
{

template <typename Iterator>
class iterator_traits
{
	public:
	typedef typename    Iterator::difference_type difference_type ;
	typedef typename    Iterator::value_type value_type;
	typedef typename    Iterator::pointer pointer;
	typedef typename    Iterator::reference reference;
	typedef typename    Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*>
{
	public:
	typedef ptrdiff_t                                   difference_type;
	typedef T                                           value_type;
	typedef T*                                          pointer;
	typedef T&                                          reference;
	typedef typename  std::random_access_iterator_tag   iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
	public:
	typedef ptrdiff_t										difference_type;
	typedef T												value_type;
	typedef const T*										pointer;
	typedef const T&										reference;
	typedef typename  std::random_access_iterator_tag		iterator_category;
};

template<bool B, class T = void>
struct enable_if
{

};

template<class T>
struct enable_if<true, T>
{
	typedef T type;
};

template <typename T>
class is_integral
{
	public:
		static const bool	value_type = std::numeric_limits<T>::is_integer;
};

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                            	InputIt2 first2, InputIt2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
 
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
    							InputIt2 first2, InputIt2 last2, Compare comp)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
 
    return (first1 == last1) && (first2 != last2);
}

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

template< class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first;
	T2 second;
	
	pair():first(),second() {};
	
	template<class U, class V>
	pair (const pair<U,V> &pr) : first(pr.first), second(pr.second) {}

	pair (const first_type &a, const second_type &b) : first(a), second(b) {};

	pair & operator=(const pair & pr)
	{
		first = pr.first;
		second = pr.second;
		return (*this);
	}

	template <class A, class B>
	friend bool operator==( const std::pair<A, B>& lhs, const std::pair<A, B>& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class A, class B>
	friend bool operator!=( const std::pair<A, B>& lhs, const std::pair<A, B>& rhs )
	{
		return (lhs.first != rhs.first && lhs.second != rhs.second);
	}

	template <class A, class B>
	friend bool operator<( const std::pair<A, B>& lhs, const std::pair<A, B>& rhs )
	{
		return (lhs.first < rhs.first || (lhs.first < rhs.first && lhs.second < rhs.second));
	}
	
	template <class A, class B>
	friend bool operator<=(const pair<A, B> & lhs, const pair<A, B> & rhs)
	{
		return (!(rhs < lhs));
	}
	
	template <class A, class B>
	friend bool operator>(const pair<A, B> & lhs, const pair<A, B> & rhs)
	{
		return (rhs < lhs);
	}
	
	template <class A, class B>
	friend bool operator>=(const pair<A, B> & lhs, const pair<A, B> & rhs)
	{
		return (!(lhs < rhs));
	}
};

template <class A, class B>
ft::pair<A, B> make_pair( A t, B u )
{
	return (pair<A, B>(t, u));
}

template <typename T>
class VecRevIterator : public std::iterator<std::random_access_iterator_tag, T>
{
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
	    typedef typename ft::iterator_traits<T>::value_type value_type;
	    typedef typename ft::iterator_traits<T>::difference_type difference_type;
	    typedef typename ft::iterator_traits<T>::pointer pointer;
	    typedef typename ft::iterator_traits<T>::reference reference;

	    // constructor
	    VecRevIterator() : _ptr(nullptr) {};

		explicit VecRevIterator( iterator_type x) : _ptr(x._ptr - 1) {};
		
		template<class U>
		VecRevIterator(const VecRevIterator<U> &other) : _ptr(other._ptr) {};

	    // increment/decrement operators
	    VecRevIterator& operator++() { --_ptr; return *this; }
	    VecRevIterator& operator--() { ++_ptr; return *this; }
	    VecRevIterator operator++(int) { VecRevIterator tmp(*this); operator++(); return tmp; }
	    VecRevIterator operator--(int) { VecRevIterator tmp(*this); operator--(); return tmp; }

	    // arithmetic operators
	    VecRevIterator operator+(difference_type n) const { return VecRevIterator(_ptr + n); }
	    VecRevIterator operator-(difference_type n) const { return VecRevIterator(_ptr - n); }
	    difference_type operator-(const VecRevIterator& rhs) const { return _ptr - rhs._ptr; }
	    VecRevIterator& operator+=(difference_type n) { _ptr += n; return *this; }
	    VecRevIterator& operator-=(difference_type n) { _ptr -= n; return *this; }

	    // dereference operator
	    T& operator*() const { return *_ptr; }
	    T* operator->() const { return _ptr; }
	    T& operator[](difference_type n) const { return _ptr[n]; }

	    // comparison operators
	    bool operator==(const VecRevIterator& rhs) const { return _ptr == rhs._ptr; }
	    bool operator!=(const VecRevIterator& rhs) const { return _ptr != rhs._ptr; }
	    bool operator<(const VecRevIterator& rhs) const { return _ptr < rhs._ptr; }
	    bool operator>(const VecRevIterator& rhs) const { return _ptr > rhs._ptr; }
	    bool operator<=(const VecRevIterator& rhs) const { return _ptr <= rhs._ptr; }
		bool operator>=(const VecRevIterator& rhs) const { return _ptr >= rhs._ptr; }

	private:
		T* _ptr;
};

template <typename T>
class VecIterator : public std::iterator<std::random_access_iterator_tag, T>
{
	public:
		typedef typename std::random_access_iterator_tag iterator_category;
	    typedef T value_type;
	    typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

	    // constructor
	    VecIterator(pointer p) : _ptr(p) {}

	    // increment/decrement operators
	    VecIterator& operator++() { ++_ptr; return *this; }
	    VecIterator& operator--() { --_ptr; return *this; }
	    VecIterator operator++(int) { VecIterator tmp(*this); operator++(); return tmp; }
	    VecIterator operator--(int) { VecIterator tmp(*this); operator--(); return tmp; }

	    // arithmetic operators
	    VecIterator operator+(difference_type n) const { return VecIterator(_ptr + n); }
	    VecIterator operator-(difference_type n) const { return VecIterator(_ptr - n); }
	    difference_type operator-(const VecIterator& rhs) const { return _ptr - rhs._ptr; }
	    VecIterator& operator+=(difference_type n) { _ptr += n; return *this; }
	    VecIterator& operator-=(difference_type n) { _ptr -= n; return *this; }

	    // dereference operator
	    T& operator*() const { return *_ptr; }
	    T* operator->() const { return _ptr; }
	    T& operator[](difference_type n) const { return _ptr[n]; }

	    // comparison operators
	    bool operator==(const VecIterator& rhs) const { return _ptr == rhs._ptr; }
	    bool operator!=(const VecIterator& rhs) const { return _ptr != rhs._ptr; }
	    bool operator<(const VecIterator& rhs) const { return _ptr < rhs._ptr; }
	    bool operator>(const VecIterator& rhs) const { return _ptr > rhs._ptr; }
	    bool operator<=(const VecIterator& rhs) const { return _ptr <= rhs._ptr; }
		bool operator>=(const VecIterator& rhs) const { return _ptr >= rhs._ptr; }

	private:
		T* _ptr;
};

template <class T>
struct Node {
	typedef Node<T> *node;
	
	Node() : _data(nullptr),
			_parent(nullptr),
			_left(nullptr),
			_right(nullptr),
			_is_sentinal(false),
			_color(0) {}

	Node(T *data, node parent = nullptr, node left = nullptr, node right = nullptr, bool is_sentinal = false, int color = 0) : 
		_data(data),
		_parent(parent),
		_left(left),
		_right(right),
		_is_sentinal(is_sentinal),
		_color(color) {};

	Node(const Node &other) : 
		_data(other._data),
		_parent(other._parent),
		_left(other._left),
		_right(other._right),
		_is_sentinal(other._is_sentinal),
		_color(other._color) {};

	~Node() {};

	public:
		T _data; // holds the pair, access key with .first and value with .second
		node _parent; // pointer to the parent
		node _left; // pointer to left child
		node _right; // pointer to right child
		int _color; // 1 -> Red, 0 -> Black
		bool _is_sentinal; // 1 -> Red, 0 -> Black
};

template <class T>
class   map_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
{
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
	    typedef typename ft::iterator_traits<T>::value_type value_type;
	    typedef typename ft::iterator_traits<T>::difference_type difference_type;
	    typedef typename ft::iterator_traits<T>::pointer pointer;
	    typedef typename ft::iterator_traits<T>::reference reference;
		typedef Node<typename std::remove_const<value_type>::type>*	node_pointer;

		map_iterator() : _ptr(nullptr) {};
		map_iterator(const map_iterator<typename std::remove_const<value_type>::type> &copy) : _ptr(copy._ptr) {}
		map_iterator(node_pointer node) : _ptr(node) {}
		
		map_iterator	&operator=(const map_iterator &other)
		{
			this->_ptr = other._ptr;
			return (*this);
		}

		~map_iterator();
		
		map_iterator &operator++()
		{
			// if node has a right child
			if (!_ptr->_right._is_sentinal)
			{
				_ptr = _ptr->_right;
				while (!_ptr->_left._is_sentinal) {
					_ptr = _ptr->_left;
				}
			}
			else
			{
				// set parent to one node above child
				node_pointer _parent = _ptr->_parent;

				// while a node is the _right child of a _parent
				while (_parent->_is_sentinal && _ptr == _parent->_right)
				{
					// set _parent to node
					_ptr = _parent;
					_parent = _parent->_parent;
				}
				// set node to _parent
				_ptr = _parent;
			}
			return *this;
		}
	
	    map_iterator operator++(int)
		{
			map_iterator<value_type> ret = *this;

			// if node has a _right child
			if (!_ptr->_right._is_sentinal)
			{
				_ptr = _ptr->_right;
				while (!_ptr->_left._is_sentinal) {
					_ptr = _ptr->_left;
				}
			}
			else
			{
				// set _parent to one node above child
				node_pointer _parent = _ptr->_parent;

				// while a node is the _right child of a _parent
				while (!_parent->_is_sentinal && _ptr == _parent->_right)
				{
					// set _parent to node
					_ptr = _parent;
					_parent = _parent->_parent;
				}
				// set node to _parent
				_ptr = _parent;
			}
			return ret;
		}

	    map_iterator& operator--()
		{
			// if node has a _left child
			if (!_ptr->_left._is_sentinal)
			{
				_ptr = _ptr->_left;
				while (!_ptr->_right._is_sentinal) {
					_ptr = _ptr->_right;
				}
			}
			else
			{
				// set parent to one node above child
				node_pointer _parent = _ptr->_parent;

				// while a node is the _left child of a _parent
				while (!_parent->_is_sentinal && _ptr == _parent->_left)
				{
					// set _parent to node
					_ptr = _parent;
					_parent = _parent->_parent;
				}
				// set node to _parent
				_ptr = _parent;
			}
			return *this;
  		}

	    map_iterator operator--(int)
		{
			map_iterator<value_type> tmp(*this);
			// if node has a _left child
			if (!_ptr->_left._is_sentinal)
			{
				_ptr = _ptr->_left;
				while (!_ptr->_right._is_sentinal) {
					_ptr = _ptr->_right;
				}
			}
			else
			{
				// set _parent to one node above child
				node_pointer _parent = _ptr->_parent;

				// while a node is the _left child of a _parent
				while (!_parent->_is_sentinal && _ptr == _parent->_left)
				{
					// set _parent to node
					_ptr = _parent;
					_parent = _parent->_parent;
				}
				// set node to _parent
				_ptr = _parent;
			}
			return tmp;
		}

		bool operator==(const map_iterator& rhs) const { return _ptr == rhs._ptr; }
	    bool operator!=(const map_iterator& rhs) const { return _ptr != rhs._ptr; }
	    bool operator<(const map_iterator& rhs) const { return _ptr < rhs._ptr; }
	    bool operator>(const map_iterator& rhs) const { return _ptr > rhs._ptr; }
	    bool operator<=(const map_iterator& rhs) const { return _ptr <= rhs._ptr; }
		bool operator>=(const map_iterator& rhs) const { return _ptr >= rhs._ptr; }
	    // arithmetic operators
		node_pointer _ptr;

};

}

#endif