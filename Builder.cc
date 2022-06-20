// Строитель — это порождающий паттерн проектирования,
// который позволяет создавать сложные объекты пошагово.
// Строитель даёт возможность использовать один и тот же
// код строительства для получения разных представлений объектов.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Wheels {
private:
    int size;
public:
    Wheels(const int &size) : size(size) {}

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        Wheels::size = size;
    }
};

class Engine {
private:
    int power;
public:
    Engine(const int &power) : power(power) {}

    int getPower() const {
        return power;
    }

    void setPower(int power) {
        Engine::power = power;
    }
};

class Hull {
private:
    string type;
public:
    Hull(const string &type) : type(type) {}

    const string &getType() const {
        return type;
    }

    void setType(const string &type) {
        Hull::type = type;
    }
};

// Строитель может создавать различные машинки, используя один
// и тот же процесс строительства
class Car
{
private:
    Wheels* wheels;
    Engine* engine;
    Hull* hull;
    string model;
public:
    Car(
        Wheels *wheels,
        Engine *engine,
        Hull *hull,
        const string &model
    ) : wheels(wheels),
        engine(engine),
        hull(hull),
        model(model) {}

    void show() {
        cout << model << " components: " << hull->getType() << " hull, " << wheels->getSize() << "' wheels, "
        << engine->getPower() << "hp engine\n";
    }

};

// По-хорошему здесь нужен интерфейс строителя,
// который объявляет все возможные этапы и шаги
// конфигурации машинки.
// Все конкретные строители реализуют общий интерфейс по-своему.

// В отличие от других порождающих паттернов, где продукты
// должны быть частью одной иерархии классов или следовать
// общему интерфейсу, строители могут создавать совершенно
// разные продукты, которые не имеют общего предка.
class Storage {
private:
    vector<Wheels*> wheels;
    vector<Engine*> engines;
    vector<Hull*> hulls;
public:
    Storage() {
        wheels = {};
        engines = {};
        hulls = {};
    }

    Wheels* getWheels() {
        Wheels* returnValue = wheels.back();
        wheels.pop_back();
        return returnValue;
    }

    Engine* getEngine() {
        Engine* returnValue = engines.back();
        engines.pop_back();
        return returnValue;
    }

    Hull* getHull() {
        Hull* returnValue = hulls.back();
        hulls.pop_back();
        return returnValue;
    }

    // Тут должны быть еще функции на добавление деталей в запас.

    void setWheels(const vector<Wheels*> &wheels) {
        Storage::wheels = wheels;
    }

    void setEngines(const vector<Engine*> &engines) {
        Storage::engines = engines;
    }

    void setHulls(const vector<Hull*> &hulls) {
        Storage::hulls = hulls;
    }
};

// Директор знает, в какой последовательности нужно заставлять
// работать строителя, чтобы получить ту или иную версию
// продукта. Заметьте, что директор работает со строителем через
// общий интерфейс, благодаря чему он не знает тип продукта,
// который изготовляет строитель.
class Factory
{
private:
    Storage* storage;
    string type;
public:
    Factory(Storage *storage, const string &type) : storage(storage), type(type) {}

    Car* buildCar() {
        return new Car(storage->getWheels(), storage->getEngine(),
                       storage->getHull(), type);
    }

};

int main()
{
    // Директор получает объект конкретного строителя.
    // Приложение само знает, какого строителя нужно
    // использовать, чтобы получить определённую машинку.
    Storage* storage = new Storage;
    storage->setEngines({new Engine(120)});
    storage->setHulls({new Hull("cool")});
    storage->setWheels({new Wheels(18)});

    Factory* factory = new Factory(storage, "carName");
    Car* newCar = factory->buildCar();
    // Готовый продукт возвращает строитель, так как
    // директор чаще всего не знает и не зависит от
    // конкретных классов строителей и продуктов.
    // Но в нашем случае это делает директор
    newCar->show();
}