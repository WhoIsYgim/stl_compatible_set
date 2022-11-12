#ifndef SET_TREE_HPP
#define SET_TREE_HPP

#include <memory>

#define MAX_DISBALANCE (1)

template <typename Key, typename Compare = std::less<Key>>
class Tree{
public:
    Tree();
    Tree(const Tree& other);
    Tree(Tree&& other);

    struct Node{
        Key key;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        size_t height;

        explicit Node(const Key& key, std::weak_ptr<Node> parent = std::weak_ptr<Node>(), size_t h = 1):
        key(key), height(h), parent(parent)
        {}
    };


    std::shared_ptr<Node> search(const Key& key) const;
    std::shared_ptr<Node> insert(const Key& key);
    std::shared_ptr<Node> erase(const Key& key);
    std::shared_ptr<Node> lower_bound(const Key& key);

    size_t size() const;
    bool empty() const;

private:
    std::shared_ptr<Node> root;
    size_t size_;
    Compare cmp_;

    std::shared_ptr<Node> insert(std::shared_ptr<Node>& node, const Key& key);
    std::shared_ptr<Node> erase(std::shared_ptr<Node>& node, const Key& key);
    std::shared_ptr<Node> erase_min(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> find_min(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> balance(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> right_rotate(std::shared_ptr<Node>& node);
    std::shared_ptr<Node> left_rotate(std::shared_ptr<Node>& node);

    int8_t balance_factor(std::shared_ptr<Node>& node);
    size_t height(std::shared_ptr<Node>& node);
    void fix_height(std::shared_ptr<Node>& node);
};


//  -------------------------------------
//  |   DEFINITIONS FOR TREE METHODS    |
//  -------------------------------------


template<typename Key, typename Compare>
Tree<Key, Compare>::Tree()
: root(nullptr), size_(0), cmp_(Compare())
{}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node>Tree<Key, Compare>::insert(const Key &key) {
    root = insert(root, key);
    return root;
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::search(const Key &key) const {
    if(!root){
        return nullptr;
    }

    auto current = root;
    while (current){
        if(cmp_(key, current->key)){
            current = current->left;
        } else if (cmp_(current->key, key)){
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr;
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::erase(const Key &key) {
    root = erase(root, key);
    return root;
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::lower_bound(const Key &key) {
    auto node = root;
    std::shared_ptr<typename Tree<Key, Compare>::Node> prev_lb = nullptr;

    while(node){
        if( !cmp_(node->key, key)){
            prev_lb = node;
            node = node->left;
        } else {
            node = node->right;
            if(node && !cmp_(node->key, key)){
                prev_lb = node;
            }
        }
    }
    return prev_lb;
}

template<typename Key, typename Compare>
size_t Tree<Key, Compare>::size() const {
    return size_;
}

template<typename Key, typename Compare>
bool Tree<Key, Compare>::empty() const {
    return size_ == 0;
}


//  --------------------------------------
//  |       INTERNAL TREE METHODS        |
//  --------------------------------------


template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key,Compare>::Node> Tree<Key, Compare>::insert(std::shared_ptr<Node> &node, const Key &key) {
    if(!node){
        node = std::make_shared<Node>(key);
        ++size_;
        return node;
    }

    if(cmp_(key, node->key)){
        node->left = insert(node->left, key);
        node->left->parent = node;
    } else if (cmp_(node->key, key)){
        node->right = insert(node->right, key);
        node->right->parent = node;
    }

    return balance(node);
}


template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::erase(std::shared_ptr<Node>& node, const  Key &key) {
    if(!node){
        return nullptr;
    }
    if(cmp_(key, node->key)){
        node->left = erase(node->left, key);
    } else if (cmp_(node->key, key)){
        node->right = erase(node->right, key);
    } else {
        --size_;

        if(!node->right){
            auto left = node->left;
            node->parent.reset();
            node->right.reset();
            node->left.reset();
            return left;
        }
        auto min = find_min(node->right);
        min->right = erase_min(node->right);
        min->left = node->left;
        if(min->left){
            min->left->parent = min;
        }
        min->parent = node->parent;
        return balance(min);
    }
    return balance(node);
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::erase_min(std::shared_ptr<Node>& node){
    if(!node->left){
        return node->right;
    }
    node->left = erase_min(node->left);
    return balance(node);
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::find_min(std::shared_ptr<Node>& node){
    if(!node){
        return nullptr;
    }
    if(!node->left){
        return node;
    }
    return find_min(node->left);
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::balance(std::shared_ptr<Node> &node) {
    fix_height(node);
    if(balance_factor(node) >  MAX_DISBALANCE){
        if(balance_factor(node->right) < 0){
            node->right = right_rotate(node->right);
        }
        return left_rotate(node);
    }
    if(balance_factor(node) < -MAX_DISBALANCE){
        if(balance_factor(node->left) > 0){
            node->left = left_rotate(node->left);
        }
        return right_rotate(node);
    }
    return node;
}

template<typename Key, typename Compare>
int8_t Tree<Key, Compare>::balance_factor(std::shared_ptr<Node> &node) {
    return height(node->right) - height(node->left);
}

template<typename Key, typename Compare>
size_t Tree<Key, Compare>::height(std::shared_ptr<Node> &node) {
    return node == nullptr ? 0 : node->height;
}

template<typename Key, typename Compare>
void Tree<Key, Compare>::fix_height(std::shared_ptr<Node> &node) {
    auto h_left = height(node->left);
    auto h_right = height(node->right);

    node->height = std::max(h_left, h_right) + 1;
}


//  --------------------------
//  |        ROTATIONS       |
//  --------------------------


template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::right_rotate(std::shared_ptr<Node> &node) {
    if(!node){
        return node;
    }
    auto temp = node->left;
    node->left = temp->right;
    temp->right = node;

    if(node->left){
        node->left->parent = node;
    }
    temp->parent = node->parent;
    node->parent = temp;

    fix_height(node);
    fix_height(temp);
    return temp;
}

template<typename Key, typename Compare>
std::shared_ptr<typename Tree<Key, Compare>::Node> Tree<Key, Compare>::left_rotate(std::shared_ptr<Node> &node) {
    if(!node){
        return node;
    }
    auto temp = node->right;
    node->right = temp->left;
    temp->left = node;

    if(node->right){
        node->right->parent = node;
    }
    temp->parent = node->parent;
    node->parent = temp;

    fix_height(node);
    fix_height(temp);
    return temp;
}

#endif //SET_TREE_HPP
