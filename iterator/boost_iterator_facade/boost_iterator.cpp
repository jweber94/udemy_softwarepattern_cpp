#include <iostream>
#include <string>
#include <algorithm>
#include <boost/iterator.hpp>
#include <boost/iterator/iterator_facade.hpp>

struct Node {
	std::string value;
	Node* next{ nullptr };

	Node(const std::string& val) : value(val)
	{}

	Node(const std::string& val, Node* parent) : value(val)
	{
		parent->next = this; // linking the parent to me (= its successor node)
	}
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag>
{
	Node* current{ nullptr };
	ListIterator() = default;

	ListIterator(Node* current) :
		current(current)
	{}

	// the boost::iterator_facade<> expects some specifically named methods that are used within the operators that are used with boost iterators
		// see https://www.boost.org/doc/libs/1_50_0/libs/iterator/doc/iterator_facade.html for details
		// boost does NOT force us to overload all iterator methods. Be careful - if some method is not implemented they mostly are used as empty methods/functions. This could lead to unexpected behaviour
		// Just by implementing the following functions, we defined a simple forward iterator for our linked list datastructure
	void increment() {
		current = current->next;
	}

	bool equal(const ListIterator& other) const {
		return other.current == current;
	}

	Node& dereference() const {
		return *current;
	}

private:
	friend class boost::iterator_core_access; // needed to allow the boost iterator framework access to the class that implement the concrete iterator object
};


int main() {
	// defining the linked list - CAUTION: If we want to do it properly, we would implement a list class which might abstract away the iterator even more. This linkage based on the plain nodes is just for demonstration purposes
	Node alpha{ "alpha" };
	Node beta{ "beta", &alpha };
	Node gamma{ "gamma", &beta };

	for_each(
		ListIterator{&alpha},
		ListIterator{},
		[&](const Node& n) -> void
		{
			std::cout << n.value << std::endl;
		}
	);
	return 0;
}