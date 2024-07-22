#pragma once
#include <memory>
#include <iostream>

namespace prototype {

// interface

class Shape {
public:
    virtual std::unique_ptr<Shape>clone() const = 0;
    virtual void draw() const    = 0;
    virtual ~Shape() {}
};

// Concrete prototypes
class Circle : public Shape {
public:
    Circle( double r ) : radius( r ) {}

    std::unique_ptr<Shape>clone() const override { return std::make_unique<Circle>(this->radius); }

    void draw() const override {
        std::cout << "Drawing a circle with radius " << radius << std::endl;
    }

private:
    double radius;
};

class Rectangle : public Shape {
public:
    Rectangle( double w, double h ) : width( w ), height( h ) {}
    std::unique_ptr<Shape> clone() const {
        return std::make_unique<Rectangle>(this->width, this->height);
    }

    void draw() const override {
        std::cout << "Drawing a rectangle with width " << width << " and height " << height << std::endl;
    }
private:
    double width, height;
};


inline void test_func() {
    Circle circlePrototype(5.0);
    Rectangle rectanglePrototype(10.0, 5.0);

    auto shape1 = circlePrototype.clone();
    auto shape2 = rectanglePrototype.clone();
    shape1->draw();
    shape2->draw();
}

}; // namespace prototype
