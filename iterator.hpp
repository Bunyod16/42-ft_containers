#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <iostream>

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
std::pair<A, B> make_pair( A t, B u )
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
}

#endif