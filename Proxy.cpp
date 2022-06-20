// Заместитель — это структурный паттерн проектирования,
// который позволяет подставлять вместо реальных объектов
// специальные объекты-заменители. Эти объекты
// перехватывают вызовы к оригинальному объекту, позволяя
// сделать что-то до или после передачи вызова оригиналу.

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Интерфейс удаленного сервиса.
class KitchenStaff {
public:
    virtual void serve(const string& food) {};
};

// Конкретная реализация сервиса.
class Cook : public KitchenStaff{
private:
    string name;
public:
    Cook(const string &name) : name(name) {}

    void serve(const string &food) override {
        cout << food << " have been cooked by: " << name << "\n";
    }
};

// Поместим логику сервировки в отдельный класс-обёртку.
// Он будет делегировать запросы к сервисному объекту.
class Server : public KitchenStaff{
private:
    vector<Cook*> cooks;
public:
    Server() {
        cooks.push_back(new Cook("Microwave"));
        cooks.push_back(new Cook("Fast-food restaurant next door"));
        cooks.push_back(new Cook("Delivery"));
    }

    void serve(const string &food) override {
        cout << "Order recieved: ";
        cooks[rand() % cooks.size()]->serve(food);
    }
};

int main() {
    // Создаем объект класса заместителя
    KitchenStaff* badRestaurant = new Server();
    badRestaurant->serve("Pizza");
    badRestaurant->serve("More pizza");
    badRestaurant->serve("Even more pizza");
    badRestaurant->serve("Ungodly amount of pizza");
}