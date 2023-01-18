#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
#include <iostream>

namespace ft
{
    template <typename T>
	class VecIterator {
	public:
		// Member types
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		// Constructors
		VecIterator() : m_ptr(nullptr) {}
		VecIterator(T* ptr) : m_ptr(ptr) {}

		// Member functions
		reference operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }
		reference operator[](difference_type n) const { return *(m_ptr + n); }

		VecIterator& operator++() { ++m_ptr; return *this; }
		VecIterator operator++(int) { VecIterator tmp(*this); operator++(); return tmp; }
		VecIterator& operator--() { --m_ptr; return *this; }
		VecIterator operator--(int) { VecIterator tmp(*this); operator--(); return tmp; }

		VecIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
		VecIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
		VecIterator operator+(difference_type n) const { return VecIterator(m_ptr + n); }
		VecIterator operator-(difference_type n) const { return VecIterator(m_ptr - n); }
		difference_type operator-(const VecIterator& other) const { return m_ptr - other.m_ptr; }
		bool operator<(const VecIterator& other) const { return m_ptr < other.m_ptr; }
		bool operator<=(const VecIterator& other) const { return m_ptr <= other.m_ptr; }
		bool operator>(const VecIterator& other) const { return m_ptr > other.m_ptr; }
		bool operator>=(const VecIterator& other) const { return m_ptr >= other.m_ptr; }
		bool operator==(const VecIterator& other) const { return m_ptr == other.m_ptr; }
		bool operator!=(const VecIterator& other) const { return m_ptr != other.m_ptr; }
	private:
		T* m_ptr;
	};


    template<typename _Tp, typename _Allocator = std::allocator<_Tp> >
    class vector:
    {
		public:
			typedef _Tp												value_type;
			typedef _Allocator										allocator_type;
			typedef typename	allocator_type::reference			reference;
			typedef typename	allocator_type::const_reference 	const_reference;
			typedef typename	allocator_type::pointer 			pointer;
			typedef ft::VecIterator<_Tp>							iterator;
			typedef const ft::VecIterator<_Tp>						const_iterator;
			typedef std::reverse_iterator<iterator>					reverse_iterator;
			typedef const std::reverse_iterator<const_iterator>		const_reverse_iterator;
			typ



			// Constructors
			explicit vector (const _Allocator& alloc = allocator_type());

			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			
			template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector &copy);
			
			// Destructor
			~vector() { }
	
			vector &operator=(const vector& __x)
			{
				static_cast<_Base&>(*this) = __x;
				this->_M_invalidate_all();
				_M_update_guaranteed_capacity();
				return *this;
			}

    };
}
#endif