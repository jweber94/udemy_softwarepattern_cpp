#include <iostream>

/* Building up a binary tree datastructure for which we want to implement our own iterator type */
//		A
//	   / \
//    B	  C

// forward declaration - needed because the tree need a fully defined node with all its methods known on its definition
template <typename T>
struct BinaryTree;

template <typename T> 
struct Node {
	// data field of the node
	T value = T(); // initialize the node data field with the default constructor
	Node<T>* left{ nullptr }, * right{ nullptr }, * parent{ nullptr };

	BinaryTree<T>* tree{ nullptr };

	// leap without children constructor
	Node(T value) : value(value) 
	{}

	// leap with children constructor
	Node(T value, Node<T>* left, Node<T>* right)
		: value(value), left(left), right(right)
	{
		if (left) {
			left->tree = tree;
			left->parent = this;
		}
		if (right) {
			right->tree = tree;
			right->parent = this;
		}
	}

	void set_tree(BinaryTree<T>* t) {
		tree = t;
		if (left) {
			left->set_tree(t);
		}
		if (right) {
			right->set_tree(t);
		}
	}

	~Node() {
		if (left) {
			delete left;
		}
		if (right) {
			delete right;
		}
	}
};

template<typename T>
struct BinaryTree {
	Node<T>* root{ nullptr };

	BinaryTree(Node<T>* r) :
		root(r),
		pre_order(*this)
	{
		root->set_tree(this); // after this call on the root node, all nodes that are associated with the root node (directly or indirectly) will receive this tree as their tree member
	}

	~BinaryTree() {
		if (root) {
			delete root;
		}
	}
	
	/* Defining the iterator datastructure - as part of the binary tree structure */
	template <typename U>
	struct PreOrderIterator {
		Node<U>* current; // value ptr

		PreOrderIterator(Node<U>* current) :
			current(current) 
		{}

		bool operator!=(const PreOrderIterator<U>& other) {
			return current != other.current;
		}

		// this is the traversal algorithm for the iterator
		PreOrderIterator<U>& operator++() {
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
			}
			else {
				Node<T>* p = current->parent;
				while (p && (current == p->right)) {
					current = p;
					p = p->parent;
				}
				current = p;
			}
			return *this;
		}

		Node<U>& operator*()
		{
			return *current;
		}
	}; /* PreOrderIterator */

	// make the PreOrderIterator the default iterator of the BinaryTree datastructure
	typedef PreOrderIterator<T> iterator;

	// defining the start and end node for the iterator class - CAUTION: This must fit to the traversing strategy that is implemented within the iterator subclass. If not, you might miss some elements (dependened on the datastructure. At least in our case with a binary tree that is the case)
	iterator begin()
	{
		// starting with the left most element of the binary tree as its iterator
		Node<T>* n = root;
		if (n) {
			while (n->left)
			{
				n = n->left;
			}
		}
		return iterator{ n };
	}

	iterator end() {
		return iterator{ nullptr };
	}

	class PreOrderTraversal // this class definition (alongside with other, similar traversal objects definitions) can be used to have multiple iterator based travsersing startegys at the same time
	{
		BinaryTree& tree;
	public:
		PreOrderTraversal(BinaryTree& tree) :
			tree(tree)
		{}

		iterator begin() {
			return tree.begin();
		}

		iterator end() {
			return tree.end();
		}
	} pre_order;
};

int main() {
	/* Application example: building a family tree with myself as the root node. Visualisation: */
	//				me
	//		     /      \
	//		  mother   father
	//		  /    \
	//		m'm    m'f
	
	// construct the tree 
	BinaryTree<std::string> family
	{
		new Node<std::string> {								// leap with children
			"me",
			new Node<std::string>							// leap with children
			{
				"mother",
				new Node<std::string>{"mothers mother"},	// leap without children
				new Node<std::string>{"mothers father"}		// leap without children
			},
			new Node<std::string>{"father"}					// leap without children
		}
	};

	// use the iterator to traverse the tree
	for (auto it = family.begin(); it != family.end(); ++it) {
		std::cout << (*it).value << "\n";
	}

	// Use the pre_order member class for travsersing without such a complicated for loop definition
	for (const auto& it : family.pre_order) {
		std::cout << it.value << std::endl;
	}

	return 0;
}