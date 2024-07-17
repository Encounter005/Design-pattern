#pragma once

#include <initializer_list>
#include <memory>
#include <queue>
#include <iostream>

namespace visitor {

template <typename DataType> class BinaryTreeNode {
    using TreeType = BinaryTreeNode<DataType>;

public:
    // explicit BinaryTreeNode( const std::initializer_list<DataType> &list={}) {
    //     for(const auto& elm : )
    // }
    explicit BinaryTreeNode( const DataType &value )
        : value_( value ), left_( nullptr ), right_( nullptr ) {}

    DataType value_;
    std::shared_ptr<BinaryTreeNode<DataType>> left_, right_;
};

template <typename DataType> class TreeVisitor {
    using TreeType = BinaryTreeNode<DataType>;

public:
    virtual ~TreeVisitor() {}
    virtual void PreOrderVisit( std::shared_ptr<TreeType> node )   = 0;
    virtual void InOrderVisit( std::shared_ptr<TreeType> node )    = 0;
    virtual void PostOrderVisit( std::shared_ptr<TreeType> node )  = 0;
    virtual void LayerOrderVisit( std::shared_ptr<TreeType> node ) = 0;
    virtual void insert(
        std::shared_ptr<TreeType> node, const DataType &value ) = 0;
    virtual std::shared_ptr<TreeType> find(
        std::shared_ptr<TreeType> node, const DataType &value ) const = 0;
    virtual void remove(
        std::shared_ptr<TreeType> node, const DataType &value ) = 0;
};

template <typename DataType>
class ExampleTreeVisitor : public TreeVisitor<DataType> {
    using TreeType = BinaryTreeNode<DataType>;

public:
    virtual void PreOrderVisit( std::shared_ptr<TreeType> node ) override {
        if ( node == nullptr ) return;
        std::cout << node->value_ << " ";
        PreOrderVisit( node->left_ );
        PreOrderVisit( node->right_ );
    }
    virtual void InOrderVisit( std::shared_ptr<TreeType> node ) override {
        if ( node == nullptr ) return;
        InOrderVisit( node->left_ );
        std::cout << node->value_ << " ";
        InOrderVisit( node->right_ );
    }
    virtual void PostOrderVisit( std::shared_ptr<TreeType> node ) override {
        if ( node == nullptr ) return;
        PostOrderVisit( node->left_ );
        PostOrderVisit( node->right_ );
        std::cout << node->value_ << " ";
    }
    virtual void LayerOrderVisit( std::shared_ptr<TreeType> node ) override {
        if ( node == nullptr ) return;

        std::queue<std::shared_ptr<TreeType>> que_;
        que_.push( node );
        while ( !que_.empty() ) {
            auto node_ = que_.front();
            que_.pop();
            std::cout << node_->value_ << " ";
            if ( node_->left_ ) {
                que_.push( node_->left_ );
            }

            if ( node_->right_ ) {
                que_.push( node_->right_ );
            }
        }
    }
    virtual void insert(
        std::shared_ptr<TreeType> node, const DataType &value ) override {

        if ( value < node->value_ ) {
            if ( node->left_ == nullptr ) {
                node->left_ = std::make_shared<TreeType>( value );
            } else {
                insert( node->left_, value );
            }
        } else {
            if ( node->right_ == nullptr ) {
                node->right_ = std::make_shared<TreeType>( value );
            } else {
                insert( node->right_, value );
            }
        }
    }
    template <typename... Args>
    void emplace( std::shared_ptr<TreeType> node, Args &&...args ) {
        ( insert( node, args ), ... );
    }

    virtual std::shared_ptr<TreeType> find(
        std::shared_ptr<TreeType> node, const DataType &value ) const override {

        if ( value == node->value_ ) {
            return node;
        } else if ( value < node->value_ ) {
            return node->left_ ? find( node->left_, value ) : nullptr;
        } else {
            return node->right_ ? find( node->right_, value ) : nullptr;
        }
    }

    virtual void remove(
        std::shared_ptr<TreeType> node, const DataType &value ) override {
        removeHelper( nullptr, node, value );
    }

private:
    void removeHelper( std::shared_ptr<TreeType> parent,
        std::shared_ptr<TreeType> node, const DataType &value ) {
        if ( node == nullptr ) return;

        if ( value < node->value_ ) {
            removeHelper( node, node->left_, value );
        } else if ( value > node->value_ ) {
            removeHelper( node, node->right_, value );
        } else {
            if ( node->left_ != nullptr && node->right_ != nullptr ) {
                auto successor = findMin( node->right_ );
                node->value_   = successor->value_;
                removeHelper( node, node->right_, successor->value_ );
            } else {
                std::shared_ptr<TreeType> child =
                    node->left_ ? node->left_ : node->right_;
                if ( parent == nullptr ) {
                    // Root node case
                    if ( node->left_ ) {
                        *node = *node->left_;
                    } else if ( node->right_ ) {
                        *node = *node->right_;
                    } else {
                        // Single node tree, do nothing
                    }
                } else {
                    if ( parent->left_ == node ) {
                        parent->left_ = child;
                    } else {
                        parent->right_ = child;
                    }
                }
            }
        }
    }

    std::shared_ptr<TreeType> findMin( std::shared_ptr<TreeType> node ) {
        while ( node->left_ != nullptr ) {
            node = node->left_;
        }
        return node;
    }
};

inline void test_func() {
    std::shared_ptr<BinaryTreeNode<int>> tree =
        std::make_shared<BinaryTreeNode<int>>( 15 );
    // tree.insert(10, 20 , 30 , 40 , 50 , 60 , 70, 80);
    ExampleTreeVisitor<int> visitor;
    visitor.emplace( tree, 10, 20, 8, 11, 16, 17, 6 );
    visitor.LayerOrderVisit( tree );
    std::cout << std::endl;
    visitor.remove( tree, 10 );
    visitor.LayerOrderVisit( tree );
}
}; // namespace visitor
