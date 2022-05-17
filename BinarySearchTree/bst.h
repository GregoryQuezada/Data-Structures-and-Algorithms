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
        node() {
            left = nullptr;
            right = nullptr;
        }
        node(Key k, T t) {
            this->key = k;
            this->value = t;
            left = nullptr;
            right = nullptr;
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
    
}

template<typename Key, typename T>
void bst<Key, T>::erase(const Key &key) {
   
    if (contains(key) == false)
        throw out_of_range("Key not found");
    else
    {
        eraseRecursive(root, key);
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
}
