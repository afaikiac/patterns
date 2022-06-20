// Фасад — это структурный паттерн проектирования, который
// предоставляет простой интерфейс к сложной системе
// классов, библиотеке или фреймворку.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Mathematician {
public:
    void doMath(){
        std::cout << "Mathematician is solving equations\n";
    }
};

class Engineer {
public:
    void doEngineering(){
        std::cout << "Engineer is building some machinery\n";
    }
};

class BioEngineer {
public:
    void doEngineering(){
        std::cout << "BioEngineer is doing what should never be done\n";
    }
};

class Consumer {
public:
    void consume(){
        std::cout << "Consumer consumes\n";
    }
};

// Вместо этого мы создаём Фасад — простой интерфейс для работы
// со сложным фреймворком. Фасад не имеет всей функциональности
// фреймворка, но зато скрывает его сложность от клиентов.
class Lab
{
private:
    Mathematician* mathematician;
    Engineer* engineer;
    BioEngineer* bioEngineer;
    Consumer* consumer;
public:
    Lab(Mathematician *mathematician,
        Engineer *engineer,
        BioEngineer* bioEngineer,
        Consumer *consumer
    ) : mathematician(mathematician),
        engineer(engineer),
        bioEngineer(bioEngineer),
        consumer(consumer) {}

    void buildCar()
    {
        mathematician->doMath();
        engineer->doEngineering();
        consumer->consume();
    }
    
    void recreateDinosaurs()
    {
        bioEngineer->doEngineering();
        consumer->consume();
    }
};

int main()
{
    Lab* lab = new Lab(
        new Mathematician(),
        new Engineer(),
        new BioEngineer(),
        new Consumer()
    );

    lab->buildCar();
    cout << "\n";
    lab->recreateDinosaurs();
    cout << "\n";
}
