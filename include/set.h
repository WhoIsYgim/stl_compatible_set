#ifndef STL_COMPATIBLE_SET_SET_H
#define STL_COMPATIBLE_SET_SET_H

#include <functional>
#include <memory>

#include "tree.hpp"

template <class Key, class Compare = std::less<Key>>
class set {
    std::shared_ptr<typename Tree<Key, Compare>::Node> root;
    Tree<Key, Compare> tree_;
    Compare cmp_;

public:
    struct iterator {
        iterator() = delete;

        const Key& operator*();
        iterator& operator++();
        iterator& operator--();
        bool operator==(const iterator& rhs);
        bool operator!=(const iterator& rhs);

    private:
        iterator(std::shared_ptr<typename Tree<Key, Compare>::Node> ptr);
        std::shared_ptr<typename Tree<Key, Compare>::Node> ptr_;

        friend class set<Key, Compare>;
    };

    set();
    set(const iterator& lhs, const iterator& rhs);
    set(std::initializer_list<Key>);
    set(const set& other);
    set(set&& other);
    ~set();

    iterator begin() const;
    iterator end()   const;

    void insert(const Key& key);
    void erase(const Key& key);

    size_t size() const;
    bool empty() const;

    iterator find(const Key& key);
    iterator lower_bound(const Key& key);

    set& operator=(const set& other);

    //TODO deal with usings && reverse iterator
    using Node = typename Tree<Key, Compare>::Node;
};

//  ----------------------------------------
//  |       SET METHODS DEFINITIONS        |
//  ----------------------------------------


template<class Key, class Compare>
set<Key, Compare>::set():
    root(nullptr),tree_(Tree<Key,Compare>()), cmp_(Compare())
    {}


template<class Key, class Compare>
set<Key, Compare>::set(const set::iterator& lhs, const set::iterator& rhs):
    root(nullptr), tree_(Tree<Key, Compare>()), cmp_(Compare())
{
    set::iterator cur = lhs;
    for(; cur != rhs; ++cur){
        insert(*cur);
        //TODO check end iterator
    }
}


template<class Key, class Compare>
set<Key, Compare>::set(std::initializer_list<Key> list):
    root(nullptr), tree_(Tree<Key, Compare>()), cmp_(Compare())
{
    for(auto item: list){
        insert(item);
    }
}


template<class Key, class Compare>
set<Key, Compare>::set(const set &other):
    root(other.root), tree_(other.tree_), cmp_(other.cmp_)
{}


template<class Key, class Compare>
set<Key, Compare>::set(set &&other):
    root(std::move(other.root)), tree_(std::move(other.tree_)), cmp_(std::move(other.cmp_))
    {}


template<class Key, class Compare>
set<Key, Compare>::~set() {
    //TODO might be set to default
}


template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::begin() const{
    if(!root){
        return iterator(root);
    }
    auto node = root;
    while(node->left){
        node = node->left;
    }
    return iterator(node);
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::end() const{
    return set::iterator{nullptr};
}

template<class Key, class Compare>
void set<Key, Compare>::insert(const Key &key) {
    root = tree_.insert(key);
}

template<class Key, class Compare>
void set<Key, Compare>::erase(const Key &key) {
    root = tree_.erase(key);
}

template<class Key, class Compare>
size_t set<Key, Compare>::size() const {
    return tree_.size();
}

template<class Key, class Compare>
bool set<Key, Compare>::empty() const {
    return tree_.empty();
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::find(const Key &key) {
    auto node = tree_.search(key);
    return set::iterator(node);
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::lower_bound(const Key &key) {
    return iterator(tree_.lower_bound(key));
}


//  --------------------------------------------
//  |       ITERATOR METHODS DEFINITION        |
//  --------------------------------------------


template<class Key, class Compare>
const Key &set<Key, Compare>::iterator::operator*() {
    return ptr_->key;
}

template<class Key, class Compare>
bool set<Key, Compare>::iterator::operator==(const set::iterator &rhs) {
    return ptr_ == rhs.ptr_;
}

template<class Key, class Compare>
bool set<Key, Compare>::iterator::operator!=(const set::iterator &rhs) {
    return ptr_ != rhs.ptr_;
}

template<class Key, class Compare>
set<Key, Compare>::iterator::iterator(std::shared_ptr<typename Tree<Key, Compare>::Node> ptr):
    ptr_(ptr)
    {}

template<class Key, class Compare>
typename set<Key, Compare>::iterator &set<Key, Compare>::iterator::operator++() {
    if(!ptr_->right){
        while(ptr_->parent.lock() && ptr_->parent.lock()->right == ptr_){
            ptr_ = ptr_->parent.lock();
        }
        ptr_ = ptr_->parent.lock();
        return *this;
    }
    ptr_ = ptr_->right;
    while (ptr_->left){
        ptr_ = ptr_->left;
    }
    return *this;
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator &set<Key, Compare>::iterator::operator--() {
    if(!ptr_->left){
        while (ptr_->parent.lock() && ptr_->parent.lock()->left == ptr_){
            ptr_ = ptr_->parent.lock();
        }
        ptr_->parent.lock();
        return *this;
    }
    ptr_ = ptr_->left;
    while (ptr_->right){
        ptr_= ptr_->right;
    }
    return *this;
}

#endif //STL_COMPATIBLE_SET_SET_H
