#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP
#include <iostream>

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
		typedef ft::VecIterator<_Tp>							iterator;
		typedef ft::VecIterator<const _Tp>						const_iterator;
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