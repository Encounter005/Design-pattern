#pragma once

#include <memory>
#include <iostream>

namespace proxy {
// Define the Subject interface
class Image {
public:
    virtual void display() = 0;
};

// Implement the Real Object
class RealImage : public Image {
public:
    RealImage( const std::string &filename ) : filename_( filename ) {
        std::cout << "Loading image: " << filename << std::endl;
    }

    virtual void display() override {
        std::cout << "Displaying image: " << filename_ << std::endl;
    }

private:
    std::string filename_;
};

// Create the Proxy
class ImageProxy : public Image {
public:
    ImageProxy( const std::string &filename )
        : realImage( nullptr ), filename_( filename ) {}
    virtual void display() override {
        // The Proxy checks if the Real Object is created and loads it if
        // necessary
        if ( realImage == nullptr ) {
            std::cout << "Proxy loaded" << std::endl;
            realImage = std::make_shared<RealImage>(filename_);
        }
        realImage->display();
    }

private:
    std::shared_ptr<RealImage> realImage;
    std::string filename_;
};


inline void test_func() {
    auto image = std::make_shared<ImageProxy>("example.jpg");
    image->display();
    image->display();
}
}; // namespace proxy

