#pragma once
#include <memory>
#include <iostream>


// Abstract product
class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual void draw() = 0;
};
// Concrete Product
class Circle : public Shape {
public:
    virtual void draw() override {
        std::cout << "this is a circle" << std::endl;
    }
};

class Square : public Shape {
public:
    virtual void draw() override {
        std::cout << "this is a square" << std::endl;
    }
};

// Abstract Creator

class ShapeFactory {
public:
    virtual std::shared_ptr<Shape> createShape() = 0;
    virtual ~ShapeFactory() = default;
};

class CircleFactory : public ShapeFactory {
public:
    std::shared_ptr<Shape> createShape() override {
        return std::make_shared<Circle>();
    }
};

class SquareFactory : public ShapeFactory {
public:
    virtual std::shared_ptr<Shape> createShape() override {
        return std::make_shared<Square>();
    }
};

void test_func() {
    std::unique_ptr<CircleFactory> circleFactory = std::make_unique<CircleFactory>();
    std::unique_ptr<SquareFactory> squareFactory = std::make_unique<SquareFactory>();
    auto circle = circleFactory->createShape();
    auto square = squareFactory->createShape();
    circle->draw();
    square->draw();
}

