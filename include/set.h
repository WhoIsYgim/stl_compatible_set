#ifndef STL_COMPATIBLE_SET_SET_H
#define STL_COMPATIBLE_SET_SET_H

#include <functional>
#include <memory>

#include "tree.hpp"

template <class Key, class Compare = std::less<Key>>
class set {
    //TODO add using = ...
    std::shared_ptr<typename Tree<Key, Compare>::Node> root;
    std::shared_ptr<typename Tree<Key, Compare>::Node> end_node;
    std::shared_ptr<typename Tree<Key, Compare>::Node> rend_node;

    Tree<Key, Compare> tree_;
public:
    struct iterator {
        iterator() = delete;

        const Key& operator*();
        iterator& operator++();
        iterator& operator--();
        bool operator==(const iterator& rhs);
        bool operator!=(const iterator& rhs);

    private:
        iterator(std::shared_ptr<typename Tree<Key, Compare>::Node> ptr,
                 std::shared_ptr<typename Tree<Key, Compare>::Node> eptr);
        std::shared_ptr<typename Tree<Key, Compare>::Node> ptr_;
        std::shared_ptr<typename Tree<Key, Compare>::Node> eptr_;

        friend class set<Key, Compare>;
    };

    set();
    set(const iterator& lhs, const iterator& rhs);
    set(std::initializer_list<Key>);
    set(const set& other);
    set(set&& other);
    ~set();

    using reverse_iterator = std::reverse_iterator<iterator>;

    iterator begin() const;
    iterator end()   const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

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
    root(nullptr), end_node(std::make_shared<Node>()), rend_node(std::make_shared<Node>()), tree_(Tree<Key,Compare>())
    {}


template<class Key, class Compare>
set<Key, Compare>::set(const set::iterator& lhs, const set::iterator& rhs):
    root(nullptr), end_node(std::make_shared<Node>()), rend_node(std::make_shared<Node>()), tree_(Tree<Key, Compare>())
{
    set::iterator cur = lhs;
    for(; cur != rhs; ++cur){
        insert(*cur);
        //TODO check end iterator
    }
    end_node->parent = tree_.max_node();
    rend_node->parent = tree_.min_node();
}


template<class Key, class Compare>
set<Key, Compare>::set(std::initializer_list<Key> list):
    root(nullptr), end_node(std::make_shared<Node>()), rend_node(std::make_shared<Node>()), tree_(Tree<Key, Compare>())
{
    for(auto item: list){
        insert(item);
    }

    end_node->parent = tree_.max_node();
    rend_node->parent = tree_.min_node();
}


template<class Key, class Compare>
set<Key, Compare>::set(const set &other):
    tree_(other.tree_)
{
    root = tree_.root();
    end_node->parent = tree_.max_node();
    rend_node->parent = tree_.min_node();
}


template<class Key, class Compare>
set<Key, Compare>::set(set &&other):
    root(std::move(other.root)), tree_(std::move(other.tree_))
    {}


template<class Key, class Compare>
set<Key, Compare>::~set() {
    //TODO might be set to default
}


template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::begin() const{
    return iterator(tree_.min_node(), end_node);
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::end() const{
    return iterator(end_node, end_node);
}

template<class Key, class Compare>
typename set<Key, Compare>::reverse_iterator set<Key, Compare>::rbegin() const {
    return set::reverse_iterator(tree_.max_node(), rend_node);
}

template<class Key, class Compare>
typename set<Key, Compare>::reverse_iterator set<Key, Compare>::rend() const {
    return set::reverse_iterator(rend_node, rend_node);
}


template<class Key, class Compare>
void set<Key, Compare>::insert(const Key &key) {
    root = tree_.insert(key);
    end_node->parent = tree_.max_node();
    rend_node->parent = tree_.min_node();
}

template<class Key, class Compare>
void set<Key, Compare>::erase(const Key &key) {
    root = tree_.erase(key);
    end_node->parent = tree_.max_node();
    rend_node->parent = tree_.min_node();
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
    if(!node){
        return iterator(end_node, end_node);
    }
    return iterator(node, end_node);
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::lower_bound(const Key &key) {
    auto node = tree_.lower_bound(key);
    if(!node){
        return iterator(end_node, end_node);
    }
    return iterator(node, end_node);
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
set<Key, Compare>::iterator::iterator(std::shared_ptr<typename Tree<Key, Compare>::Node> ptr,
                                      std::shared_ptr<typename Tree<Key, Compare>::Node> eptr):
    ptr_(ptr), eptr_(eptr)
    {}

template<class Key, class Compare>
typename set<Key, Compare>::iterator &set<Key, Compare>::iterator::operator++() {
    if(!ptr_->right){
        while(ptr_->parent.lock() && ptr_->parent.lock()->right == ptr_){
            ptr_ = ptr_->parent.lock();
        }
        ptr_ = ptr_->parent.lock();
        if(!ptr_){
            ptr_ = eptr_;
        }
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
        ptr_ = ptr_->parent.lock();
        if(!ptr_){
            ptr_ = eptr_;
        }
        return *this;
    }
    ptr_ = ptr_->left;
    while (ptr_->right){
        ptr_= ptr_->right;
    }
    return *this;
}

#endif //STL_COMPATIBLE_SET_SET_H
