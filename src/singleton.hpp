#pragma once
#include <mutex>
#include <memory>
#include <iostream>

template<typename T>
class SingleTon {
protected:
    explicit SingleTon() = default;
    SingleTon(const SingleTon& ) = delete;
    SingleTon& operator=(const SingleTon&) = delete;
    ~SingleTon() {
        std::cout << "This is SingleTon deletor" << std::endl;
    }
    static std::shared_ptr<T> single;
public:

    static std::shared_ptr<T> getInstance() {
        static std::once_flag flag;
        std::call_once(flag, [&](){
            single = std::make_shared<T>(new T);
        });
        return single;
    }
};

template<typename T>
std::shared_ptr<T> SingleTon<T>::single = nullptr;
