#include <iostream>
#include <algorithm>

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

    bool isNodeInVector(const std::vector<Node<T>*>& vec, const Node<T>* nodeToFind) {
        return std::find(vec.begin(), vec.end(), nodeToFind) != vec.end();
    }
    // traverse the node and its children preorder
    // and put all the results into `result`

    void preorder_traversal(vector<Node<T>*>& result)
    {
        Node<T>* rootNode = this;
        result.push_back(rootNode);
        
        Node<T>* tmpNode = this;
        std::vector<Node<T>*> rightVisited{};
        while ((tmpNode == rootNode) && isInVector(rightVisited, tmpNode)) {
            if ((tmpNode->left != nullptr) && !isInVector(result, tmpNode)) {
                tmpNode = tmpNode->left;
                result.push_back(tmpNode);
                continue;
            }
            else {
                if (tmpNode->right != nullptr && isInVector(rightVisuted, tmpNode)) {
                    tmpNode = tmpNode->right;
                    result.push_back(tmpNode);
                    rightVisited.push_back(tmpNode);
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
                        if (tmpNode->right) {
                            tmpNode = tmpNode->right;
                            result.push_back(tmpNode);
                            rightVisited.push_back(tmpNode->parent);
                            continue;
                        }
                        else {
                            // parent has no right node
                            tmpNode = tmpNode->parent;
                        }
                    }
                }
            }
        }
    }
};

int main() {
	std::cout << "Hello World\n";
	return 0;
}