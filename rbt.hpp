#include <iostream>
#include "iterator.hpp"

namespace ft
{
template<class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
class RBTree {
	public:
		typedef Node<T> node_type;
        typedef T value_type;
		typedef typename T::first_type key_type;
        typedef Compare value_comp;
        typedef Allocator allocator_type;
		typedef std::allocator<Node<T> > node_allocator;
		typedef typename node_allocator::pointer node_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ft::map_iterator<value_type> iterator;
        typedef ft::map_iterator<const value_type> const_iterator;
        typedef ft::VecRevIterator<iterator> reverse_iterator;
        typedef ft::VecRevIterator<const iterator> const_reverse_iterator;

private:

	node_pointer 		_root;
	node_pointer 		_sentinal;
	node_allocator _node_alloc;
	allocator_type _val_alloc;
	value_comp		_comp;
	size_t			_size;
 
public:

	node_pointer get_root()
	{
		return _root;
	}

	node_pointer create_node(const value_type &val = value_type(), bool is_sentinal = false)
	{
		node_pointer node;
		pointer new_val;

		node = _node_alloc.allocate(1);
		new_val = _val_alloc.allocate(1);

		_val_alloc.construct(new_val, val);
		_node_alloc.construct(node, node_type(*new_val, _sentinal, _sentinal, _sentinal, is_sentinal, 1));
		return (node);
	}

	//constructor
	RBTree(const value_comp comp = value_comp(), const Allocator alloc = Allocator()) : _val_alloc(alloc),
																							_comp(comp),
																							_size(0)
	{
		_node_alloc = node_allocator();
		_sentinal = create_node(value_type()) ;
		_sentinal->_color = 0;
		_sentinal->_left = nullptr;
		_sentinal->_right = nullptr;
		_sentinal->_is_sentinal = true;
		_root = _sentinal;
	}

	// find the node with the min key
	node_pointer min(node_pointer node) {
		while (node->_left != _sentinal) {
			node = node->_left;
		}
		return node;
	}

	// find the node with the max key
	node_pointer max(node_pointer node) {
		while (node->_right != _sentinal) {
			node = node->_right;
		}
		return node;
	}

	iterator begin()
	{
		return (iterator(min(_root)));
	}

	iterator end()
	{
		return (iterator(max(_root)));
	}

	reverse_iterator rbegin()
	{
		return (reverse_iterator(max(_root)));
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(min(_root)));
	}

	node_pointer	find_val(node_pointer node, const value_type &val) const
	{
		if (node == _sentinal)
			return node;
		if (_comp(val, node->_data))
			return find_val(node->_left, val);
		if (_comp(node->_data, val))
			return find_val(node->_right, val);
		return node;
	}

	void preOrderHelper(node_pointer node) {
		if (node != _sentinal) {
			std::cout<<node->_data<<" ";
			preOrderHelper(node->_left);
			preOrderHelper(node->_right);
		} 
	}

	void inOrderHelper(node_pointer node) {
		if (node != _sentinal) {
			inOrderHelper(node->_left);
			std::cout<<node->data<<" ";
			inOrderHelper(node->_right);
		} 
	}

	void postOrderHelper(node_pointer node) {
		if (node != _sentinal) {
			postOrderHelper(node->_left);
			postOrderHelper(node->_right);
			std::cout<<node->data<<" ";
		} 
	}

	// fix the rb tree modified by the delete operation
	void fixDelete(node_pointer x) {
		node_pointer s;
		while (x != _root && x->_color == 0) {
			if (x == x->_parent->_left) {
				s = x->_parent->_right;
				if (s->_color == 1) {
					// case 3.1
					s->_color = 0;
					x->_parent->_color = 1;
					leftRotate(x->_parent);
					s = x->_parent->_right;
				}

				if (s->_left->_color == 0 && s->_right->_color == 0) {
					// case 3.2
					s->_color = 1;
					x = x->_parent;
				} else {
					if (s->_right->_color == 0) {
						// case 3.3
						s->_left->_color = 0;
						s->_color = 1;
						rightRotate(s);
						s = x->_parent->_right;
					} 

					// case 3.4
					s->_color = x->_parent->_color;
					x->_parent->_color = 0;
					s->_right->_color = 0;
					leftRotate(x->_parent);
					x = _root;
				}
			} else {
				s = x->_parent->_left;
				if (s->_color == 1) {
					// case 3.1
					s->_color = 0;
					x->_parent->_color = 1;
					rightRotate(x->_parent);
					s = x->_parent->_left;
				}

				if (s->_right->_color == 0 && s->_right->_color == 0) {
					// case 3.2
					s->_color = 1;
					x = x->_parent;
				} else {
					if (s->_left->_color == 0) {
						// case 3.3
						s->_right->_color = 0;
						s->_color = 1;
						leftRotate(s);
						s = x->_parent->_left;
					} 

					// case 3.4
					s->_color = x->_parent->_color;
					x->_parent->_color = 0;
					s->_left->_color = 0;
					rightRotate(x->_parent);
					x = _root;
				}
			} 
		}
		x->_color = 0;
	}


	void rbTransplant(node_pointer u, node_pointer v){
		if (u->_parent == nullptr) {
			_root = v;
		} else if (u == u->_parent->_left){
			u->_parent->_left = v;
		} else {
			u->_parent->_right = v;
		}
		v->_parent = u->_parent;
	}
	
	// fix the red-black tree
	void fixInsert(node_pointer k){
		node_pointer u;
		while (k->_parent->_color == 1) {
			if (k->_parent == k->_parent->_parent->_right) {
				u = k->_parent->_parent->_left; // uncle
				if (u->_color == 1) {
					// case 3.1
					u->_color = 0;
					k->_parent->_color = 0;
					k->_parent->_parent->_color = 1;
					k = k->_parent->_parent;
				} else {
					if (k == k->_parent->_left) {
						// case 3.2.2
						k = k->_parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->_parent->_color = 0;
					k->_parent->_parent->_color = 1;
					leftRotate(k->_parent->_parent);
				}
			} else {
				u = k->_parent->_parent->_right; // uncle

				if (u->_color == 1) {
					// mirror case 3.1
					u->_color = 0;
					k->_parent->_color = 0;
					k->_parent->_parent->_color = 1;
					k = k->_parent->_parent;	
				} else {
					if (k == k->_parent->_right) {
						// mirror case 3.2.2
						k = k->_parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->_parent->_color = 0;
					k->_parent->_parent->_color = 1;
					rightRotate(k->_parent->_parent);
				}
			}
			if (k == _root) {
				break;
			}
		}
		_root->_color = 0;
	}

	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder() {
		preOrderHelper(this->_root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder() {
		inOrderHelper(this->_root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder() {
		postOrderHelper(this->_root);
	}

	// find the successor of a given node
	node_pointer successor(node_pointer x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != _sentinal) {
			return min(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		node_pointer y = x->parent;
		while (y != _sentinal && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	node_pointer predecessor(node_pointer x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != _sentinal) {
			return max(x->left);
		}

		node_pointer y = x->parent;
		while (y != _sentinal && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// rotate left at node x
	void leftRotate(node_pointer x) {
		node_pointer y = x->_right;
		x->_right = y->_left;
		if (y->_left != _sentinal) {
			y->_left->_parent = x;
		}
		y->_parent = x->_parent;
		if (x->_parent == nullptr) {
			this->_root = y;
		} else if (x == x->_parent->_left) {
			x->_parent->_left = y;
		} else {
			x->_parent->_right = y;
		}
		y->_left = x;
		x->_parent = y;
	}

	// rotate _right at node x
	void rightRotate(node_pointer x) {
		node_pointer y = x->_left;
		x->_left = y->_right;
		if (y->_right != _sentinal) {
			y->_right->_parent = x;
		}
		y->_parent = x->_parent;
		if (x->_parent == nullptr) {
			this->_root = y;
		} else if (x == x->_parent->_right) {
			x->_parent->_right = y;
		} else {
			x->_parent->_left = y;
		}
		y->_right = x;
		x->_parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	node_pointer insert(const value_type &val) {
		// Ordinary Binary Search Insertion
		node_pointer node = create_node(val);
		node->_parent = _sentinal;
		node->_left = _sentinal;
		node->_right = _sentinal;
		node->_color = 1; // new node must be red

		node_pointer y = nullptr;
		node_pointer x = this->_root;

		while (x != _sentinal)
        {
			y = x;
			if (_comp(node->_data, x->_data))
            {
				x = x->_left;
			}
            else
            {
				x = x->_right;
			}
		}

		// y is parent of x
		node->_parent = y;
		if (y == _sentinal) {
			_root = node;
		} else if (node->_data.first < y->_data.first) {
			y->_left = node;
		} else {
			y->_right = node;
		}

		// if new node is a _root node, simply return
		if (node->_parent == _sentinal){
			node->_color = 0;
			return (node);
		}

		// if the grandparent is null, simply return
		if (node->_parent->_parent == _sentinal) {
			return (node);
		}

		// Fix the tree
		fixInsert(node);
		return (node);
	}

	node_pointer getRoot(){
		return this->_root;
	}

	void deleteNodeHelper(node_pointer node, node_pointer delete_node) {

		node_pointer z = _sentinal;
		node_pointer x, y;

		while (node != _sentinal){
			if (node->_data == delete_node) {
				z = node;
			}

			if (_comp(node->_data, delete_node)) {
				node = node->_right;
			} else {
				node = node->_left;
			}
		}

		if (z == _sentinal) {
			std::cout<<"Couldn't find key in the tree"<<std::endl;
			return;
		} 

		y = z;
		int y_original_color = y->_color;
		if (z->_left == _sentinal) {
			x = z->_right;
			rbTransplant(z, z->_right);
		} else if (z->_right == _sentinal) {
			x = z->_left;
			rbTransplant(z, z->_left);
		} else {
			y = min(z->_right);
			y_original_color = y->_color;
			x = y->_right;
			if (y->_parent == z) {
				x->_parent = y;
			} else {
				rbTransplant(y, y->_right);
				y->_right = z->_right;
				y->_right->_parent = y;
			}

			rbTransplant(z, y);
			y->_left = z->_left;
			y->_left->_parent = y;
			y->_color = z->_color;
		}
		_node_alloc.deallocate(z);
		if (y_original_color == 0){
			fixDelete(x);
		}
	}

	void deleteNode(key_type key) {
		node_pointer val = find_val(key);
		deleteNodeHelper(_root, val);
	}

	void printHelper(node_pointer root, std::string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != _sentinal) {
		   std::cout<<indent;
		   if (last) {
		      std::cout<<"R----";
		      indent += "     ";
		   } else {
		      std::cout<<"L----";
		      indent += "|    ";
		   }
            
           std::string sColor = root->color?"RED":"BLACK";
		   std::cout<<root->data<<"("<<sColor<<")"<<std::endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
		// cout<<root->left->data<<endl;
	}

	void prettyPrint() {
	    if (_root) {
    		printHelper(_root, "", true);
	    }
	}
};
}

