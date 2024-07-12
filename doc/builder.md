# 建造者模式简介

建造者模式（Builder Pattern）是一种在软件设计中用来组织对象的构造过程的方法。它将对象的构建和表示分离，允许独立改变构建过程或生成不同的表示形式。这种模式特别适用于那些需要创建复杂对象的场景，在这些场景中，对象的组成部分可能相互依赖或者取决于外部环境条件。

## 建造者模式的主要组件

建造者模式通常包含以下主要组件：

1. **产品（Product）接口**：定义了一个通用的产品或对象结构。所有具体产品的构建都会遵循这个接口。

2. **抽象建造者（Builder Interface）**：为创建特定产品提供一组方法，这些方法用于设置产品的不同部分。该接口是所有具体建造者的超类。

3. **具体建造者（Concrete Builder）**：实现抽象建造者接口，并定义了如何构建具体的产品实例。每个具体的建造者将根据需要构建不同的部分或选择不同的配置来创建产品。

4. **产品工厂（Product Factory）** 或 **导演（Director）**：在一些情况下，可以使用一个中心类来调用特定的建造者方法并构建出一个完整的产品对象。这个类通常不直接与产品的具体实现交互，而是通过调用建造者的接口来完成构建过程。

## 应用场景

建造者模式适用于以下几种情况：

- **复杂对象构造**：当创建对象时涉及多个步骤或依赖于外部环境条件（例如操作系统版本、网络配置等）。
- **可选功能构建**：在产品中包含可选择的组件或选项，如定制电脑配置（CPU类型、内存大小、硬盘驱动器类型等）。

## 实例说明

为了更好地理解建造者模式，我们可以使用一个简单的例子来说明如何应用这个设计模式。假设我们正在组装一台电脑开发一个构建过程，允许用户根据需求自定义电脑的配置

```cpp
#include <iostream>
#include <string>
#include <memory>

// Product
class Computer {
public:
    explicit Computer() = default;
    void setCPU( const std::string &cpu ) { cpu_ = cpu; }
    void setMemory( const std::string &memory ) { memory_ = memory; }
    void setStorage( const std::string &storage ) { storage_ = storage; }
    void print() const {
        std::cout << "CPU:     " << cpu_ << std::endl;
        std::cout << "Memory:  " << memory_ << std::endl;
        std::cout << "Storage: " << storage_ << std::endl;
    }

private:
    std::string cpu_;
    std::string memory_;
    std::string storage_;
};

// Builder interface
class ComputerBuilder {
public:
    virtual ~ComputerBuilder()                       = default;
    virtual void buildCPU( const std::string & )     = 0;
    virtual void buildMemory( const std::string & )  = 0;
    virtual void buildStorage( const std::string & ) = 0;
    virtual std::shared_ptr<Computer> getResult()    = 0;
};

// Concrete Builder
class DesktopComputerBuilder : public ComputerBuilder {
public:
    DesktopComputerBuilder() : computer_( std::make_shared<Computer>() ) {}

    void buildCPU( const std::string &cpu ) override {
        computer_->setCPU( cpu );
    }
    void buildMemory( const std::string &memory ) override {
        computer_->setMemory( memory );
    }
    void buildStorage( const std::string &storage ) override {
        computer_->setStorage( storage );
    }

    std::shared_ptr<Computer> getResult() override { return computer_; }

private:
    std::shared_ptr<Computer> computer_;
};

// Director

class ComputerAssembler {
public:
    std::shared_ptr<Computer> assembleComputer( ComputerBuilder &builder ) {
        builder.buildCPU( "Inter i7" );
        builder.buildStorage( "980 PRO 1TB SSD" );
        builder.buildMemory( "16GB" );
        return builder.getResult();
    }
};

void test_func() {
    DesktopComputerBuilder builder;
    ComputerAssembler assembler;
    auto computer = assembler.assembleComputer( builder );
    computer->print();
}

```

### 分析

在给出的代码示例中，实现了建造者模式的主要组成部分：

1. **产品接口**（`Computer`）：定义了一个用于创建电脑的基本接口。所有的具体产品（如台式电脑、笔记本电脑等）都必须遵循这个接口。

2. **抽象建造者（Builder Interface）**（`ComputerBuilder`）：定义了构建电脑所需的通用方法，比如设置CPU、内存和存储设备等。这些方法对所有具体的建造者类开放，允许它们独立于具体产品来操作构建过程。

3. **具体建造者**（`DesktopComputerBuilder`）：实现了抽象建造者接口并提供了具体实现的方法。每个具体建造者会根据自己的规则和逻辑来执行构建步骤，比如在台式电脑上选择不同的组件配置。

4. **导演类（Director）**（`ComputerAssembler`）：负责调用具体的建造者类进行构建过程。它不直接与产品接口或具体的产品实例交互，而是通过调用抽象建造者的接口方法完成构建。

5. `test_func` 函数展示了如何使用这些组成部分来构建一个台式电脑的例子：

```cpp
DesktopComputerBuilder builder;
ComputerAssembler assembler;
auto computer = assembler.assembleComputer( builder );
computer->print();
```

在这个例子中：

- **Builder** (`DesktopComputerBuilder`) 实例化并执行了具体的构建步骤，比如选择CPU型号、内存大小和存储设备类型。
- **Director** (`ComputerAssembler`) 负责调用 `DesktopComputerBuilder` 的方法来逐步构造电脑。

通过这样的结构设计，建造者模式使得在不同场景下可以有不同的构建过程（不同的具体产品），同时保持了代码的可扩展性和灵活性。例如，我们可以轻松地添加新的构建步骤或创建完全不同的产品类型而无需修改现有的组装逻辑。

## 结论

建造者模式是一种强大的设计模式，尤其在需要创建具有复杂构造过程的对象时非常有用。它通过封装构建过程和分离产品构建逻辑来提高系统的灵活性、可扩展性和可维护性。
