#pragma once
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
