#pragma once

#include <iostream>

namespace adapter {

// Target Interface

class Printer {
public:
    virtual void print() = 0;
};

// Adaptee
class LegacyPrinter {
public:
    void printDocument() {
        std::cout << "Legacy Printer is printing a document" << std::endl;
    }
};

// Adapter
class PrinterAdapter : public Printer {
public:
    virtual void print() override {
        legacyPrinter.printDocument();
    }
private:
    LegacyPrinter legacyPrinter;
};
inline void test_func() {
    PrinterAdapter print;
    print.print();
}

};
