// Абстрактная фабрика — это порождающий паттерн
// проектирования, который позволяет создавать семейства
// связанных объектов, не привязываясь к конкретным
// классам создаваемых объектов.

#include <iostream>
using namespace std;


// Конкретный класс
class Car {
private:
    int speed;
    std::string model;

public:
    Car(int speed, const string &model) : speed(speed), model(model) {}

    void drive(int time) {
        cout << speed * time << "\n";
    }
};

// Абстрактная фабрика знает обо всех абстрактных типах
class AbstractFactory {
public:
    virtual Car* buildCar() {
        return nullptr;
    };

    virtual ~AbstractFactory() = default;
};

// Каждая конкретная фабрика знает и создаёт только машинки
// своей вариации
class FastFactory : public AbstractFactory {
    Car* buildCar() override {
        return new Car(100, "fast car");
    }
};

class SlowFactory : public AbstractFactory {
    Car* buildCar() override {
        return new Car(25, "slow car");
    }
};

// Для кода, использующего фабрику, не важно, с какой конкретно
// фабрикой он работает. Все получатели машинок работают с
// ними через общие интерфейсы
int main() {
    // Можно навесить какой-нибудь if else,
    // чтобы создавались разные фабрики
    AbstractFactory* baseFactory;
    baseFactory = new FastFactory();
    Car* fastCar = baseFactory->buildCar();
    baseFactory = new SlowFactory();
    Car* slowCar = baseFactory->buildCar();
    fastCar->drive(10);
    slowCar->drive(10);
}
