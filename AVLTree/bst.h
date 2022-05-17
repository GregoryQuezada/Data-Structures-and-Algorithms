#pragma once
#include <vector>
#include <exception>
using namespace std;

namespace cop3530 {

template<typename Key, typename T>
class bst {
    struct node {
        // key
        Key key;
        // value
        T value;
        // left child
        node* left;
        // right child
        node* right;
        // node height
        int height;
        node() {
            left = nullptr;
            right = nullptr;
            height = 1;
        }
        node(Key k, T t) {
            this->key = k;
            this->value = t;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    // root of tree
    node* root;

    public:
        bst();
        ~bst();
        void insert(const Key &key, const T &t);
        void insertRecursive(node* &current, const Key &key, const T &t);
        void erase(const Key &key);
        node* eraseRecursive(node* &current, const Key &key);
        void eraseAll(node* current);
        T& at(const Key &key);
        T& RecurAt(node* current, const Key &key);
        bool contains(const Key &key) const;
        bool empty() const;
        size_t size() const;
        size_t RecurSize(node* current) const;
        std::vector<std::pair<Key, T>> inorder_contents();
        void RecurInorder(vector<pair<Key, T>> &contents, node* current);
        std::vector<std::pair<Key, T>> preorder_contents();
        void RecurPreorder(vector<pair<Key, T>> &contents, node* current);
        int nodeBalance(node* current);
        node* rotateRight(node* current);
        node* rotateLeft(node* current);
        int getHeight(node* current);


};

template<typename Key, typename T>
bst<Key, T>::bst() {
    root = nullptr;
}

template<typename Key, typename T>
bst<Key, T>::~bst() {
    eraseAll(root);
}

template<typename Key, typename T>
void bst<Key, T>::eraseAll(node* current) {
    
    if (current == nullptr)
        return;
    
    eraseAll(current->left);
    eraseAll(current->right);
    delete current;
    
}

template<typename Key, typename T>
void bst<Key, T>::insert(const Key &key, const T &t) {
    insertRecursive(root, key, t);
}

template<typename Key, typename T>
void bst<Key, T>::insertRecursive(node* &current, const Key &key, const T &t) {
    
    if (current == nullptr)
    {
        node* temp = new node(key, t);
        current = temp;
    }
    else if (current->key == key)
    {
        current->value = t;
    }
    else if (key < current->key)
    {
        insertRecursive(current->left, key, t);
    }
    else
    {
        insertRecursive(current->right, key, t);
    }

    int leftHeight = getHeight(current->left);
    int rightHeight = getHeight(current->right);

    current->height = ((leftHeight > rightHeight)? leftHeight : rightHeight) + 1;

    int balance = nodeBalance(current);

    // LL
    if (balance > 1 && key < current->left->key)
        current = rotateRight(current);
    
    // LR
    if (balance > 1 && key > current->left->key)
    {
        current->left = rotateLeft(current->left);
        current = rotateRight(current);
    }

    // RR
    if (balance < -1 && key > current->right->key)
        current = rotateLeft(current);

    // RL
    if (balance < -1 && key < current->right->key)
    {
        current->right = rotateRight(current->right);
        current = rotateLeft(current);
    }
    
}

template<typename Key, typename T>
void bst<Key, T>::erase(const Key &key) {
   
    if (contains(key) == false)
        throw out_of_range("Key not found");
    else
    {
        root = eraseRecursive(root, key);
    }
        
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::eraseRecursive(node* &current, const Key &key) {

    if (current == nullptr)
        return current;

    if (key < current->key)
        current->left = eraseRecursive(current->left, key);
    else if (key > current->key)
        current->right = eraseRecursive(current->right, key);
    else 
    {

        if (current->right == nullptr && current->left == nullptr)
        {
            delete current;
            current = nullptr;
        }
        else if (current->left == nullptr)
        {
            node* temp = current;
            current = current->right;

            delete temp;
        }
        else if (current->right == nullptr)
        {
            node* temp = current;
            current = current->left;
            
            delete temp;
        }
        else
        {

            node* rightmostNode = current->left;

                while (rightmostNode->right != nullptr)
                {
                    rightmostNode = rightmostNode->right;
                }

                current->key = rightmostNode->key;
                current->value = rightmostNode->value;
                current->left = eraseRecursive(current->left, rightmostNode->key);   
        }         
    }

    if (current == nullptr)
        return current;

    int leftHeight = getHeight(current->left);
    int rightHeight = getHeight(current->right);

    current->height = ((leftHeight > rightHeight)? leftHeight : rightHeight) + 1;

    int balance = nodeBalance(current);

    // LL
    if (balance > 1 && nodeBalance(current->left) >= 0)
        return rotateRight(current);

    // RR
    if (balance < -1 && nodeBalance(current->right) <= 0)
        return rotateLeft(current);

    // LR
    if (balance > 1 && nodeBalance(current->left) < 0)
    {
        current->left = rotateLeft(current->left);
        return rotateRight(current);
    }

    // RL
    if (balance < -1 && nodeBalance(current->right) > 0)
    {
        current->right = rotateRight(current->right);
        return rotateLeft(current);
    }

    return current;
}

template<typename Key, typename T>
T& bst<Key, T>::at(const Key &key) {
    
    if (contains(key) == false)
        throw out_of_range("Key not found");
    else
    {
        return RecurAt(root, key);
    }
}

template<typename Key, typename T>
T& bst<Key, T>::RecurAt(node* current, const Key &key) {
    
    if (current->key == key)
        return current->value;
    else if (current->key > key)
        return RecurAt(current->left, key);
    else
        return RecurAt(current->right, key);
}

template<typename Key, typename T>
bool bst<Key, T>::contains(const Key &key) const {
    
    node* current = root;

    while (true)
    {
        if (current == nullptr)
            return false;
        else if (current->key == key)
            return true;
        else if (current->key > key)
            current = current->left;
        else 
            current = current->right;
    }
    
}

template<typename Key, typename T>
bool bst<Key, T>::empty() const {
    
    if (root == nullptr)
        return true;
    else
        return false;
    
}

template<typename Key, typename T>
size_t bst<Key, T>::size() const {
    return RecurSize(root);
}

template<typename Key, typename T>
size_t bst<Key, T>::RecurSize(node* current) const {

    if (current == nullptr)
        return 0;
    else 
        return 1 + RecurSize(current->left) + RecurSize(current->right);
}

template<typename Key, typename T>
std::vector<std::pair<Key, T>> bst<Key, T>::inorder_contents() {
    std::vector<std::pair<Key, T>> contents;

    RecurInorder(contents, root);

    return contents;
}

template<typename Key, typename T>
void bst<Key, T>::RecurInorder(vector<pair<Key, T>> &contents, node* current) {

    if (current == nullptr)
        return;

    RecurInorder(contents, current->left);
    contents.push_back(make_pair(current->key, current->value));
    RecurInorder(contents, current->right);
}

template<typename Key, typename T>
std::vector<std::pair<Key, T>> bst<Key, T>::preorder_contents() {
    std::vector<std::pair<Key, T>> contents;

    RecurPreorder(contents, root);

    return contents;
}

template<typename Key, typename T>
void bst<Key, T>::RecurPreorder(vector<pair<Key, T>> &contents, node* current) {

    if (current == nullptr)
        return;

    contents.push_back(make_pair(current->key, current->value));
    RecurPreorder(contents, current->left);
    RecurPreorder(contents, current->right);

}

template<typename Key, typename T>
int bst<Key, T>::nodeBalance(node* current) {
    if (current == nullptr)
        return 0;
    else
    {
        int leftHeight = 0;
        int rightHeight = 0;

        if (current->left != nullptr)
            leftHeight = current->left->height;

        if (current->right != nullptr)
            rightHeight = current->right->height;

        return leftHeight - rightHeight;
    }
    
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::rotateRight(node* current) {

    node* newParent = current->left;
    node* grandchild = current->left->right;

    newParent->right = current;
    current->left = grandchild;

    int leftHeight = getHeight(current->left);
    int rightHeight = getHeight(current->right);

    current->height = ((leftHeight > rightHeight)? leftHeight : rightHeight) + 1;

    leftHeight = getHeight(newParent->left);
    rightHeight = getHeight(newParent->right);

    newParent->height = ((leftHeight > rightHeight)? leftHeight : rightHeight) + 1;

    return newParent;
    
}

template<typename Key, typename T>
typename bst<Key, T>::node* bst<Key, T>::rotateLeft(node* current) {

    node* newParent = current->right;
    node* grandchild = current->right->left;

    newParent->left = current;
    current->right = grandchild;

    int leftHeight = getHeight(current->left);
    int rightHeight = getHeight(current->right);

    current->height = ((leftHeight > rightHeight)? leftHeight : rightHeight) + 1;

    leftHeight = getHeight(newParent->left);
    rightHeight = getHeight(newParent->right);

    newParent->height = ((leftHeight > rightHeight)? leftHeight : rightHeight) + 1;

    return newParent;

}

template<typename Key, typename T>
int bst<Key, T>::getHeight(node* current) {
    if (current == nullptr)
        return 0;
    else 
        return current->height;
}

}
