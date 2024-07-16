#pragma once

#include <mutex>
#include <atomic>
#include <memory>
#include <condition_variable>

template <typename T> class ThreadSafeQue {
private:
    struct node {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node *tail;
    std::condition_variable data_cond;
    std::atomic<bool> bstop{ false };

    node *get_tail() {
        std::lock_guard<std::mutex> lock( tail_mutex );
        return tail;
    }

    std::unique_ptr<node> pop_head() {
        std::unique_ptr<node> old_head = std::move( head );
        head                           = std::move( old_head->next );
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data() {
        std::unique_lock<std::mutex> lock( head_mutex );
        data_cond.wait(
            lock, [this] { return bstop.load() || head.get() != get_tail(); } );
        return std::move( lock );
    }

    std::unique_ptr<node> pop_head( bool &is_stop ) {
        is_stop = bstop.load();
        if ( is_stop ) {
            return nullptr;
        }
        return pop_head();
    }

public:
    ThreadSafeQue() : head( new node ), tail( head.get() ) {}

    ThreadSafeQue( const ThreadSafeQue & )            = delete;
    ThreadSafeQue &operator=( const ThreadSafeQue & ) = delete;

    void NotifyStop() {
        bstop.store( true );
        data_cond.notify_one();
    }

    std::shared_ptr<T> WaitAndPop() {
        std::unique_ptr<node> old_head = wait_pop_head();
        if ( !old_head ) {
            return nullptr;
        }
        return old_head->data;
    }

    bool WaitAndPop( T &value ) {
        std::unique_ptr<node> old_head = wait_pop_head( value );
        return !!old_head;
    }

    std::shared_ptr<T> TryPop() {
        std::unique_ptr<node> old_head = try_pop_head();
        return old_head ? old_head->data : nullptr;
    }

    bool TryPop( T &value ) {
        std::unique_ptr<node> old_head = try_pop_head( value );
        return !!old_head;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock( head_mutex );
        return head.get() == get_tail();
    }

    void push( T new_value ) {
        auto new_data = std::make_shared<T>( std::move( new_value ) );
        std::unique_ptr<node> new_node( new node );
        {
            std::lock_guard<std::mutex> lock( tail_mutex );
            new_node->data = new_data;
            tail->next     = std::move( new_node );
            tail           = tail->next.get();
        }
        data_cond.notify_one();
    }

private:
    std::unique_ptr<node> wait_pop_head() {
        std::unique_lock<std::mutex> lock( wait_for_data() );
        return pop_head( bstop.load() );
    }

    std::unique_ptr<node> wait_pop_head( T &value ) {
        std::unique_lock<std::mutex> lock( wait_for_data() );
        std::unique_ptr<node> node = pop_head( bstop.load() );
        if ( node ) {
            value = std::move( *node->data );
        }
        return node;
    }

    std::unique_ptr<node> try_pop_head() {
        std::lock_guard<std::mutex> lock( head_mutex );
        return pop_head( bstop.load() );
    }

    std::unique_ptr<node> try_pop_head( T &value ) {
        std::lock_guard<std::mutex> lock( head_mutex );
        std::unique_ptr<node> node = pop_head( bstop.load() );
        if ( node ) {
            value = std::move( *node->data );
        }
        return node;
    }
};
