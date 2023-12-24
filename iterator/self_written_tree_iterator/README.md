# Self written Iterator for a Tree Datastructure

## Implementation details
+ The traversable datastructure is the `BinaryTree` class
+ The `Node<T>->set_tree(this)` method of the node will set all leaps of the root node to the tree of the root node.
	- This will be done after all nodes are initialized (with `nullptr` as their tree)
	- Only after the BinaryTree is constructed with the root node associated with it, the tree gets assigned to the nodes, triggered by the constructor of the binary tree

### Implementation of the iterator class
+ The (self-written) iterator class is a subclass of the datastructure (aka class) that it should be able to traverse
	- By putting it into the traversable datatstructures class definition, it has access to all members of that class. Therefore we can access the traversable datastructure as we need it
+ The iterator subclass defines the strategy how the superior datastructure (in our case the BinaryTree) can be traversed
+ The `BinaryTree::begin()` and `BinaryTree::end()` methods define the start and end elements where the traversing should start
	- In our case the left most leaf of the tree
+ Be careful while implementing the `begin()` and `end()` methods as well as the iterator class (especially the traversing functionallity)! They must fit together!
	- If they are not corresponding to each other, we might not encounter every element within the datastructure while traversing it with the iterator (since the travsering strategy needs to have an assumption where it starts and from there onwards how to travse the complete datastructure)
