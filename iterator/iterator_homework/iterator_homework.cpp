#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

template <typename T>
struct Node
{
    T value;
    Node* left{ nullptr }, * right{ nullptr }, * parent{ nullptr };

    Node(T value) : value(value) {}

    Node(T value, Node<T>* left, Node<T>* right) : value(value), left(left), right(right) {
        left->parent = right->parent = this;
    }

    bool isInVector(const std::vector<Node<T>*>& vec, const Node<T>* nodeToFind) {
        return std::find(vec.begin(), vec.end(), nodeToFind) != vec.end();
    }
    // traverse the node and its children preorder
    // and put all the results into `result`


    void preorder_traversal(vector<Node<T>*>& result)
    {
        Node<T>* tmpNode = this;            // start with the node as root
        std::stack<Node<T>*> nodeStack;     // use empty stack to be able to go back and check the right child

        while (tmpNode != nullptr || !nodeStack.empty()) {  // valid node and there is at least one node within the stack
            while (tmpNode != nullptr) {    // go left until no valid node is found and put ALL nodes on the stack
                result.push_back(tmpNode);  // visite the node
                nodeStack.push(tmpNode);    // put the visited node on the stack
                tmpNode = tmpNode->left;    // go further left
            }

            // if we have gone left until we could not go deeper
                // use the last valid node and go right - then start from the top and try to go left
            tmpNode = nodeStack.top();
            nodeStack.pop();
            tmpNode = tmpNode->right;
        }
    }


    /*
    // old version without using a stack
    void preorder_traversal(vector<Node<T>*>& result)
    {
        Node<T>* rootNode = this;
        if (this != nullptr) {
            result.push_back(rootNode);
        }
        // process root node separatly because it is contained within the termination condition of the while loop
        Node<T>* tmpNode;
        if (rootNode->left != nullptr) {
            tmpNode = this->left;
        }
        else if (rootNode->right != nullptr) {
            tmpNode = this->right;
        }
        else {
            return;
        }
       result.push_back(tmpNode);
        
       // process the rest of the tree 
       std::vector<Node<T>*> rightVisited{};
        while ((tmpNode != rootNode) && !isInVector(rightVisited, rootNode)) {
            if ((tmpNode->left != nullptr) && !isInVector(result, tmpNode->left)) {
                tmpNode = tmpNode->left;
                result.push_back(tmpNode);
                continue;
            }
            else {
                if (tmpNode->right != nullptr && !isInVector(rightVisited, tmpNode)) {
                    tmpNode = tmpNode->right;
                    rightVisited.push_back(tmpNode->parent);
                    result.push_back(tmpNode);
                    continue;
                }
                else {
                    tmpNode = tmpNode->parent;
                    if (isInVector(result, tmpNode) && isInVector(rightVisited, tmpNode)) {
                        if (tmpNode != rootNode) {
                            tmpNode = tmpNode->parent;
                        }
                        continue;
                    }
                    else {
                        if (tmpNode->right != nullptr) {
                            tmpNode = tmpNode->right;
                            result.push_back(tmpNode);
                            rightVisited.push_back(tmpNode->parent);
                            continue;
                        }
                        else {
                            // parent has no right node
                            tmpNode = tmpNode->parent;
                            continue;
                        }
                    }
                    result.push_back(tmpNode);
                }
            }
        }
    }
    */
};

int main() {
	std::cout << "Building tree" << std::endl;

    Node<std::string> root{ "A",
        new Node<std::string> {"B",
            new Node<std::string> {"D"},
            new Node<std::string> { "E",
                new Node<std::string> {"F",
                    new Node<std::string> {"H"},
                    new Node<std::string> {"I"}
                },
                new Node<std::string>{"G"}
            }
        },
        new Node<std::string> {"C"}
    };

    std::vector<Node<std::string>*> result;
    std::cout << "Calculating the preorder" << std::endl;
    root.preorder_traversal(result);

    std::cout << "The preorder is: " << std::endl;
    for (auto& it : result) {
        std::cout << it->value << std::endl;
    }
    std::cout << "Finished program" << std::endl;
	return 0;
}