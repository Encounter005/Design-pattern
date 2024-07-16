#pragma once

#include <iostream>
#include <memory>
#include <unordered_set>
namespace observer {
class Observer {
public:
    virtual void update(
        float temperature, float humidity, float pressure ) = 0;
};

class WeatherStation {
public:
    void registerObserver( std::shared_ptr<Observer> obs ) {
        observers.insert( obs );
    }

    void removeObserver( std::shared_ptr<Observer> obs ) {
        observers.erase( obs );
    }

    void notifyObservers() {
        for ( auto &observer : observers ) {
            observer->update( temperature, humidity, pressure );
        }
    }

    void setMeasurements( float temp, float hum, float press ) {
        temperature = temp;
        humidity    = hum;
        pressure    = press;
        notifyObservers();
    }

private:
    float temperature, humidity, pressure;
    std::unordered_set<std::shared_ptr<Observer>> observers;
};

class Display : public Observer {
public:
    void update( float temperature, float humidity, float pressure ) {
        std::cout << "Display update: " << temperature << ", " << humidity
                  << ", " << pressure << std::endl;
    }
};

inline void test_func() {
    WeatherStation weatherstation;
    std::shared_ptr<Display> dis1 = std::make_shared<Display>(),
                             dis2 = std::make_shared<Display>();
    weatherstation.registerObserver( dis1 );
    weatherstation.registerObserver( dis2 );

    weatherstation.setMeasurements( 25.5, 60, 1013.2 );
    weatherstation.setMeasurements( 24.8, 68, 114514 );
}
}; // namespace observer
