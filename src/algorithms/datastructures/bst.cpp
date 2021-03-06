#include <iostream>
#include "bst.hpp"

/*
 * Combines the flexibility of insertion in a linked list with 
 * the efficiency of search in an ordered array.
 *
 * The shape of the tree is dependant on the order of insertion.
 * The number of search/inserts is equal to 1 + depth of node.
 * Best case: random inserted
 * Average case: almost random
 * Worst case: ordered insertion. Is the same as a linked list.
 *
 * If N distinct keys are inserted in random order the expected
 * number of search/inserts is ~2 ln N. (1.39 lg N)
 * Interestingly this is the same as the partitioning in quicksort.
 * But in contrast to quickstort where we randomize the data, the
 * insertion is done by the caller which is out of our control.
 *
 * worst-case cost      average-case cost
 * search: N            1.39 lg N
 * insert: N            1.39 lg N
 *
 */
class BinarySearchTree: public SearchTree {
    private:
        Node *root;
        Node *putNode(Node *node, int key, char value);
        Node *getNode(Node *node, int key);
        Node *min(Node *node);
        Node *max(Node *node);
        int size(Node *node);
        const Node *floor(const Node *node, int key);
        const Node *ceil(const Node *node, int key);
        int rank(const Node *node, int key);
        Node *deleteMin(Node*node);
        Node *deleteMax(Node*node);
        Node *deleteKey(Node*node, int key);

    public:
        BinarySearchTree() : root(nullptr) {
        }
        ~BinarySearchTree() {
        }
        void put(int key, char value);
        char get(int key);
        int size();
        char min();
        char max();
        int floor(int key);
        int ceil(int key);
        int rank(int key);
        void deleteMin();
        void deleteMax();
        void deleteKey(int key);
};

Node *BinarySearchTree::deleteKey(Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->key) {
        // key is to the left so we only need to process the left side
        node->left = deleteKey(node->left, key);
    } else if (key > node->key) {
        // key is to the right so we only need to process the right side
        node->right = deleteKey(node->right, key);
    } else { // keys are equal. This is the node to be deleted.
        // the node to deleted does not have a left node. 
        if (node->left == nullptr) {
            return node->right;
        }
        if (node->right == nullptr) {
            return node->left;
        }
        Node *d = node;
        node = min(node->right);
        node->right = deleteMin(node->right);
        node->left = d->left;
      }
      node->count = size(node->left) + size(node->right) + 1;
      return node;
}

void BinarySearchTree::deleteKey(int key) {
    root = deleteKey(root, key);
}

void BinarySearchTree::deleteMax() {
    root = deleteMax(root);
}

Node *BinarySearchTree::deleteMax(Node *node) {
    if (node->right == nullptr) {
        return node->left;
    }
    node->right = deleteMax(node->right);
    node->count = size(node->left) + size(node->right) + 1;
    return node;
}

Node *BinarySearchTree::deleteMin(Node* node) {
    if (node->left == nullptr) {
        // assign right to left (or null if ther is no left which is ok.
        return node->right;
    }
    // this node was not the min so recurse downwards (to the left)
    node->left = deleteMin(node->left);
    // update the count for each node.
    node->count = size(node->left) + size(node->right) + 1;
    return node;
}

void BinarySearchTree::deleteMin() {
    root = deleteMin(root);
}

/*
*  Return the number of keys that are less than the passed-in key
*/
int BinarySearchTree::rank(const Node *node, int key) {
    if (node == nullptr) {
        return 0;
    }
    if (key == node->key) {
        // return the count of the left. This is not the same as the current nodes count
        // as it also contains the count for its right tree.
        return size(node->left);
    }
    if (key < node->key) {
        // process the left subtree
        return rank(node->left, key);
    }
    // so the key was greater then the current nodes key. 
    // Take the size of the left subtree, plus 1 for this node and 
    // the rank of processing the right subtree.
    return 1 + size(node->left) + rank(node->right, key);
}

int BinarySearchTree::rank(int key) {
    return rank(root, key);
}

const Node * BinarySearchTree::ceil(const Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key == node->key) {
        return node;
    }

    if (key > node->key) {
        return ceil(node->right, key);
    }
    const Node *left = ceil(node->left, key);
    return left == nullptr ? node : left;
}

int BinarySearchTree::ceil(int key) {
    return ceil(root, key)->key;
}

/**
 * Return the Node that has the largest key less than, or equal to key.
 *
 */
const Node * BinarySearchTree::floor(const Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key == node->key) {
        return node;
    } 
    if (key < node->key) {
        // check the left subtree. We know the key should belong 
        return floor(node->left, key);
    } 
    // if key is greater then node->key, then we search the right subtree
    // but the key might not exist at all, in which case we want to return
    // the largest key less than key. This would be the current node.
    const Node * right = floor(node->right, key);
    return right == nullptr ? node : right;
}

int BinarySearchTree::floor(int key) {
    return floor(root, key)->key;
}

void BinarySearchTree::put(int key, char value) {
    root = putNode(root, key, value);
}

char BinarySearchTree::get(int key) {
    Node *node = getNode(root, key);
    if (node == nullptr) {
        throw "No such key";
    }
    return node->value;
}

int BinarySearchTree::size(Node *node) {
    return node == nullptr ? 0 : node->count;
}

int BinarySearchTree::size() {
    return size(root);
}

Node * BinarySearchTree::min(Node *node) {
    if (node->left == nullptr) {
        return node;
    }
    return min(node->left);
}

Node * BinarySearchTree::max(Node *node) {
    if (node->right == nullptr) {
        return node;
    }
    return max(node->right);
}

char BinarySearchTree::min() {
    return min(root)->value;
}

char BinarySearchTree::max() {
    return max(root)->value;
}

Node * BinarySearchTree::putNode(Node *node, int key, char value) {
    if (node == nullptr) {
        return new Node(key, value);
    }
    if (key < node->key) {
        node->left = putNode(node->left, key, value);
    } else if (key > node->key) {
        node->right = putNode(node->right, key, value);
    } else {
        node->value = value;
    }
    // we have to increment the size of all nodes, not just the node added.
    node->count = size(node->left) + size(node->right) + 1;
    return node;
}

Node * BinarySearchTree::getNode(Node *node, int key) {
    if (node == nullptr) {
        return nullptr;
    }
    if (key < node->key) {
        return getNode(node->left, key);
    } else if (key > node->key) {
        return getNode(node->right, key);
    } else {
        return node;
    }
}

