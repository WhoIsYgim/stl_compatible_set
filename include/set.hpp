#ifndef STL_COMPATIBLE_SET_SET_HPP
#define STL_COMPATIBLE_SET_SET_HPP

#include <functional>
#include <iterator>
#include <memory>

#include "tree.hpp"

template <class Key, class Compare = std::less<Key>>
class set {
    using Node = typename Tree<Key, Compare>::Node;

    Tree<Key, Compare> tree_;
    std::shared_ptr<Node> end_node_;
public:
    struct iterator {
    public:
        using difference_type = const std::ptrdiff_t;
        using value_type = const Key;
        using pointer = const Key*;
        using reference = const Key&;
        using iterator_category = std::bidirectional_iterator_tag;
        
        iterator() = default;
        iterator(const iterator& other);
        iterator& operator=(const iterator& other);

        reference operator*();
        pointer   operator->();

        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);

        bool operator==(const iterator& rhs);
        bool operator!=(const iterator& rhs);

    private:
        explicit iterator(std::shared_ptr<Node> ptr);
        std::shared_ptr<Node> ptr_;
        std::shared_ptr<Node> eptr_;

        friend class set<Key, Compare>;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;

    set();
    template< class InputIt >
    set(InputIt first, InputIt last);
    set(std::initializer_list<Key>);
    set(const set& other);
    set(set&& other);
    ~set() = default;

    set& operator=(const set& other);

    iterator begin() const;
    iterator end()   const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    void insert(const Key& key);
    void erase(const Key& key);

    size_t size() const;
    bool empty() const;

    iterator find(const Key& key) const;
    iterator lower_bound(const Key& key) const;
};

//  ----------------------------------------
//  |       SET METHODS DEFINITIONS        |
//  ----------------------------------------


template<class Key, class Compare>
set<Key, Compare>::set():
    tree_(Tree<Key,Compare>())
{
    end_node_ = std::make_shared<Node>();
}


template<class Key, class Compare>
set<Key, Compare>::set(std::initializer_list<Key> list):
    tree_(Tree<Key,Compare>())
{
    end_node_ = std::make_shared<Node>();
    for(auto item: list){
        insert(item);
    }
    end_node_->parent = tree_.max_node();
}


template<class Key, class Compare>
set<Key, Compare>::set(const set &other):
    tree_(other.tree_)
{
    end_node_ = std::make_shared<Node>(tree_.max_node());
}

template<class Key, class Compare>
set<Key, Compare>::set(set &&other):
    tree_(std::move(other.tree_)), end_node_(std::move(other.end_node_))
    {}


template<class Key, class Compare>
template<class InputIt>
set<Key, Compare>::set(InputIt first, InputIt last):
    tree_(Tree<Key, Compare>())
{
    end_node_ = std::make_shared<Node>();
    while (first != last){
        insert(*first);
        ++first;
    }
}

template<class Key, class Compare>
set<Key, Compare>&set<Key, Compare>::operator=(const set &other) {
    tree_ = other.tree_;

    end_node_->parent = tree_.max_node();
    return *this;
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::begin() const{
    if(!tree_.min_node()){
        return end();
    }
    auto it = iterator(tree_.min_node());
    it.eptr_ = end_node_;
    return it;

}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::end() const{
    auto it = iterator(end_node_);
    it.eptr_ = end_node_;
    return it;
}

template<class Key, class Compare>
typename set<Key, Compare>::reverse_iterator set<Key, Compare>::rbegin() const {
    return reverse_iterator(end());
}

template<class Key, class Compare>
typename set<Key, Compare>::reverse_iterator set<Key, Compare>::rend() const {
    return reverse_iterator(begin());
}

template<class Key, class Compare>
void set<Key, Compare>::insert(const Key &key) {
    tree_.insert(key);
    end_node_->parent = tree_.max_node();
}

template<class Key, class Compare>
void set<Key, Compare>::erase(const Key &key) {
    tree_.erase(key);
    end_node_->parent = tree_.max_node();
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
typename set<Key, Compare>::iterator set<Key, Compare>::find(const Key &key) const {
    auto node = tree_.search(key);
    if(!node){
        iterator it(end_node_);
        it.eptr_=end_node_;
        return it;
    }
    iterator it(node);
    it.eptr_=end_node_;
    return it;
}

template<class Key, class Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::lower_bound(const Key &key) const {
    auto node = tree_.lower_bound(key);
    if(!node){
        iterator it(end_node_);
        it.eptr_=end_node_;
        return it;
    }
    iterator it(node);
    it.eptr_=end_node_;
    return it;
}


//  --------------------------------------------
//  |       ITERATOR METHODS DEFINITION        |
//  --------------------------------------------

template<class Key, class Compare>
set<Key, Compare>::iterator::iterator(const set::iterator &other):
ptr_(other.ptr_), eptr_(other.eptr_)
{}

template<class Key, class Compare>
typename set<Key, Compare>::iterator &set<Key, Compare>::iterator::operator=(const iterator& other){
    ptr_ = other.ptr_;
    eptr_ = other.eptr_;
    return *this;
}


template<class Key, class Compare>
const Key &set<Key, Compare>::iterator::operator*() {
    return ptr_->key;
}

template<class Key, class Compare>
const Key* set<Key, Compare>::iterator::operator->() {
    return &ptr_->key;
}

template<class Key, class Compare>
bool set<Key, Compare>::iterator::operator==(const iterator &rhs) {
    return ptr_ == rhs.ptr_;
}

template<class Key, class Compare>
bool set<Key, Compare>::iterator::operator!=(const iterator &rhs) {

    return ptr_ != rhs.ptr_;
}

template<class Key, class Compare>
set<Key, Compare>::iterator::iterator(std::shared_ptr<Node> ptr):
    ptr_(ptr)
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

template<class Key, class Compare>
 typename set<Key, Compare>::iterator set<Key, Compare>::iterator::operator++(int){
    auto tmp = *this;
    ++*this;
    return tmp;
}

template<class Key, class Compare>
 typename set<Key, Compare>::iterator set<Key, Compare>::iterator::operator--(int){
    auto tmp = *this;
    --*this;
    return tmp;
}

#endif //STL_COMPATIBLE_SET_SET_HPP
