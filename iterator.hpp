#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

#include <iostream>

// std::iterator_traits
// • std::reverse_iterator
// • std::enable_if
// Yes, it is C++11 but you will be able to implement it in a C++98 manner.
// This is asked so you can discover SFINAE.
// • std::is_integral
// • std::equal and/or std::lexicographical_compare
// • std::pair
// • std::make_pair

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

template <typename Iter>
class reverse_iterator
{
	public:
	typedef Iter													iterator_type;
	typedef typename    iterator_traits<Iter>::iterator_category	iterator_category;
	typedef typename    iterator_traits<Iter>::value_type			value_type;
	typedef typename    iterator_traits<Iter>::difference_type		difference_type ;
	typedef typename    iterator_traits<Iter>::pointer				pointer;
	typedef typename    iterator_traits<Iter>::reference			reference;
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
class VecIterator 
// : public ft::iterator<VecIterator_tag, T>
{
public:
	// Member types
	typedef std::random_access_iterator_tag iterator_category;
	// Constructors
	VecIterator() : m_ptr(nullptr) {}
	VecIterator(T* ptr) : m_ptr(ptr) {}

	// Member functions
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	T& operator[](std::ptrdiff_t n) const { return *(m_ptr + n); }

	VecIterator& operator++() { ++m_ptr; return *this; }
	VecIterator operator++(int) { VecIterator tmp(*this); operator++(); return tmp; }
	VecIterator& operator--() { --m_ptr; return *this; }
	VecIterator operator--(int) { VecIterator tmp(*this); operator--(); return tmp; }

	VecIterator& operator+=(std::ptrdiff_t n) { m_ptr += n; return *this; }
	VecIterator& operator-=(std::ptrdiff_t n) { m_ptr -= n; return *this; }
	VecIterator operator+(std::ptrdiff_t n) const { return VecIterator(m_ptr + n); }
	VecIterator operator-(std::ptrdiff_t n) const { return VecIterator(m_ptr - n); }
	std::ptrdiff_t operator-(const VecIterator& other) const { return m_ptr - other.m_ptr; }
	bool operator<(const VecIterator& other) const { return m_ptr < other.m_ptr; }
	bool operator<=(const VecIterator& other) const { return m_ptr <= other.m_ptr; }
	bool operator>(const VecIterator& other) const { return m_ptr > other.m_ptr; }
	bool operator>=(const VecIterator& other) const { return m_ptr >= other.m_ptr; }
	bool operator==(const VecIterator& other) const { return m_ptr == other.m_ptr; }
	bool operator!=(const VecIterator& other) const { return m_ptr != other.m_ptr; }
private:
	T* m_ptr;
};

template <typename T>
class ReverseIterator {
	public:
		typedef T iterator_type;
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;

		ReverseIterator();
		explicit ReverseIterator(iterator_type it);

	};
}

#endif