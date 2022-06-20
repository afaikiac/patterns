// Адаптер — это структурный паттерн проектирования,
// который позволяет объектам с несовместимыми
// интерфейсами работать вместе.

#include <iostream>
#include <string>

class FahrenheitThermometer {
private:
    double temp;

public:
    FahrenheitThermometer(double temp) : temp(temp) {}
    FahrenheitThermometer() {temp = 0;}

    virtual double getTemp() {
        return temp;
    }

    virtual void setTemp(double temp) {
        FahrenheitThermometer::temp = temp;
    }
};

// Несовместимый класс
class CelsiusThermometer {
private:
    double temp;

public:
    CelsiusThermometer(double temp) : temp(temp) {}
    CelsiusThermometer() {temp = 0;}

    virtual double getTemp() {
        return temp;
    }

    virtual void setTemp(double temp) {
        CelsiusThermometer::temp = temp;
    }
};

// Адаптер позволяет использовать оба термометра вместе.
class CelsiusAdapter : public CelsiusThermometer {
private:
    FahrenheitThermometer* thermometer;

public:
    CelsiusAdapter(FahrenheitThermometer *thermometer) : thermometer(thermometer) {}

    double getTemp() override {
        return (thermometer->getTemp() - 32) * .5556;
    }
};

class Heater {
public:
    Heater() = default;

    void adjust(CelsiusThermometer* t) {
        if (t->getTemp() > 25) {
            std::cout << "cooling down\n";
        }
        else if (t->getTemp() < 20) {
            std::cout << "heating up\n";
        }
        else {
            std::cout << "comfortable\n";
        }
    }
};

int main()
{
    FahrenheitThermometer* outsideThermometer = new FahrenheitThermometer;
    CelsiusThermometer* insideAdapter = new CelsiusAdapter(outsideThermometer);
    Heater* heater = new Heater();
    outsideThermometer->setTemp(40);
    heater->adjust(insideAdapter);
    outsideThermometer->setTemp(100);
    heater->adjust(insideAdapter);
    outsideThermometer->setTemp(70);
    heater->adjust(insideAdapter);
    return 0;
}
