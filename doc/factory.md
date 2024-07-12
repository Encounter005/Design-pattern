# 工厂模式简介

在软件开发中，工厂模式是一种设计模式，主要用于创建对象而不暴露具体类的创建细节。这种模式的主要目标是封装创建过程，并将创建逻辑从客户端代码中解耦出来。

## 定义和意图：

**工厂模式**的意图在于提供一个创建一系列相关或相互依赖的对象的过程，而无需指定这些对象的具体类。它通过定义一个工厂类来实现这一功能，该工厂类负责根据输入参数决定创建哪个具体类的实例。

## 常见形式

工厂模式通常有以下几种常见形式：

1. **简单工厂（Simple Factory）**：
   这是最基础的形式，它不依赖于类层次结构，并且通常被用于静态语言中。工厂只创建一个类族中的对象，通过传入参数来决定创建哪个具体类。

2. **抽象工厂（Abstract Factory）**：
   抽象工厂模式提供了一系列的工厂方法，用于创建一组相关的产品对象。这些产品可以属于不同的家族，但必须遵循共同的接口或抽象定义。其目的是在多个产品的上下文之间进行隔离，使得客户端代码只需要知道如何使用产品而不是如何创建它们。

3. **单例工厂（Singleton Factory）**：
   在此模式中，工厂类是单例的，确保了在整个应用范围内只有一个实例存在，并且提供一个公共的方法来访问这个实例。这是一种常见的设计模式，用于限制资源访问或配置设置。

4. **构造函数工厂（Constructor Factory）**：
   这种形式在面向对象语言中较为常见，它通过构造方法创建和初始化对象。构造函数工厂可以接受参数构建具有特定配置的对象，提供了一种动态调整对象属性的机制。

## 使用场景

- 在需要根据环境或运行时条件选择具体类时。
- 当客户端代码不应该依赖于具体的类实现细节，而是应该通过抽象接口进行交互时。
- 当创建复杂对象需要多个步骤、参数和依赖关系时（例如，配置文件中的信息用于决定对象实例的创建）。

## 示例

假设我们有一个简单工厂模式的例子。假设我们要根据用户输入创建不同类型的形状：

```cpp
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
// Client
void test_func() {
    std::unique_ptr<CircleFactory> circleFactory = std::make_unique<CircleFactory>();
    std::unique_ptr<SquareFactory> squareFactory = std::make_unique<SquareFactory>();
    auto circle = circleFactory->createShape();
    auto square = squareFactory->createShape();
    circle->draw();
    square->draw();
}
```

在这个例子中，`Shape` 和 `ShapeFactory` 是接口和抽象类的例子。工厂模式通过创建具体实现的实例（即 `Circle` 或 `Square`）来满足客户端的不同需求，而不需要在代码中硬编码具体的类名。

### 具体分析：

1. **接口（Abstract Class）**：

   - `Shape`：这是抽象产品类，定义了一个纯虚函数`draw()`，用于绘制形状。
   - `CircleFactory`, `SquareFactory`：这些是抽象创建者类的实现。它们都实现了从抽象创建者类继承的`createShape()`接口方法。

2. **具体类**：

   - `Circle` 和 `Square` 是具体产品类。它们各自实现了`draw()`函数以表示不同形状的绘制方式。

3. **工厂模式**：
   - 在这个例子中，通过使用抽象创建者（`ShapeFactory`）和具体创建者（`CircleFactory`, `SquareFactory`），我们可以在不直接引用具体产品类的情况下创建产品对象。这种方法使得客户端代码与具体的产品实现解耦。
4. **测试函数**：
   - `test_func()` 函数展示了如何通过工厂模式实例化不同的产品。它首先创建了`CircleFactory`和`SquareFactory`的实例，然后调用每个工厂的`createShape()`方法来获取相应的形状对象，并调用它们的`draw()`方法来验证是否正确创建并绘制出了圆形和正方形。

## 使用场景：

- 当需要在运行时决定使用哪个具体产品类时。
- 需要将产品的创建过程与产品的客户端代码分离，以提高代码可维护性和灵活性。
- 避免类的爆炸问题（即大量的相似类），通过一个工厂类来管理类的选择和实例化。

通过这种方式，工厂模式提供了一种灵活的方式来根据特定需求动态地生成不同类型的对象。在实际开发中，这种设计模式常用于UI组件、数据库连接器等场景，以提高代码的可扩展性和维护性。

## 总结

工厂模式为创建对象提供了极大的灵活性和封装性，并有助于降低耦合度和提高代码的可维护性。它通过提供一个统一的方式来实例化特定类型的对象或一组相关的对象，使得系统结构更加清晰、更易于调整和扩展。
