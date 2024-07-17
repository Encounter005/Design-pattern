#pragma once

#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

namespace strategy {

template <typename Iterator> class SortingStrategy {
public:
    virtual void execute( Iterator first, Iterator last ) = 0;
    virtual ~SortingStrategy() {}
};

template <typename Iterator>
class Quick_Sorting : public SortingStrategy<Iterator> {
public:
    virtual void execute( Iterator first, Iterator last ) override {
        if ( first >= last ) return;

        auto pivot = partition( first, last );
        execute( first, pivot );
        execute( std::next( pivot ), last );
    }

private:
    Iterator partition( Iterator first, Iterator last ) {
        auto pivot = *std::prev( last );

        std::iter_swap( first, std::prev( last ) );

        Iterator less_than_pivot = first;

        for ( auto current = first + 1; current != last; ++current ) {
            if ( *current < pivot ) {
                std::iter_swap( ++less_than_pivot, current );
            }
        }

        std::iter_swap( first, less_than_pivot );

        return less_than_pivot;
    }
};

template <typename Iterator>

class Bubble_Sorting : public SortingStrategy<Iterator> {
public:
    virtual void execute( Iterator first, Iterator last ) override {
        for ( auto i = first; i != last; ++i ) {
            for ( auto j = std::next( i ); j != last; ++j ) {
                if ( *i > *j ) {
                    std::iter_swap( i, j );
                }
            }
        }
    }
};

template <typename Iterator>
class Insertion_Sorting : public SortingStrategy<Iterator> {
public:
    virtual void execute( Iterator first, Iterator last ) override {
        for ( auto i = std::next( first ); i != last; ++i ) {
            auto value      = *i;
            auto insert_pos = std::upper_bound( first, i, value );
            std::move_backward( insert_pos, i, i + 1 );
            *insert_pos = value;
        }
    }
};

template <typename Iterator> class SortContext {
public:
    void setStrategy( std::unique_ptr<SortingStrategy<Iterator>> strategy ) {
        this->strategy = std::move( strategy );
    }

    void executeStrategy( Iterator first, Iterator last ) {
        strategy->execute( first, last );
    }

private:
    std::unique_ptr<SortingStrategy<Iterator>> strategy;
};

inline void test_func() {
    std::vector<int> num{
        2, 2, 2, 2, 2, 1892, 23, 12, 22332323, -1213, -1, 223, 0 };
    using iterator = std::vector<int>::iterator;
    Quick_Sorting<iterator> quick_sorting;
    SortContext<iterator> context;
    context.setStrategy(std::make_unique<Quick_Sorting<iterator>>(quick_sorting));
    context.executeStrategy(num.begin(), num.end());

    for(const auto& elm : num) {
        std::cout << elm << " ";
    }

    std::cout << std::endl;
}

}; // namespace strategy
