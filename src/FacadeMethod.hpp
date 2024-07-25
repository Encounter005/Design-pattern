#pragma once
#include <iostream>

namespace Facade {

// SubSystem1
class Engine {
public:
    void Start() { std::cout << "Engine Started" << std::endl; }

    void Stop() { std::cout << "Engine Stopped" << std::endl; }
};

class Lights {
public:
    void TurnOn() { std::cout << "Lights On" << std::endl; }
    void TurnOff() { std::cout << "Lights Off" << std::endl; }
};

// Facade
class Car {
public:
    void StartCar() {
        engine.Start();
        lights.TurnOn();
        std::cout << "Car is ready to drive" << std::endl;
    }

    void StopCar() {
        lights.TurnOff();
        engine.Stop();
        std::cout << "Car has stopped" << std::endl;
    }

private:
    Engine engine;
    Lights lights;
};

inline void test_func() {
    Car car;
    car.StartCar();
    car.StopCar();
}

}; // namespace Facade
