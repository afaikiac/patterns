// Стратегия — это поведенческий паттерн проектирования,
// который определяет семейство схожих алгоритмов и
// помещает каждый из них в собственный класс, после чего
// алгоритмы можно взаимозаменять прямо во время
// исполнения программы.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Clothes {
public:
    virtual void wear(int temp) = 0;
};
class WinterClothes : public Clothes {
public:
    void wear(int temp) override {
        if (temp < -30) {
            cout << "You froze to death\n";
        }
        else if (temp < -15) {
            cout << "You're feeling cold\n";
        }
        else if (temp < 0) {
            cout << "You're feeling comfortable\n";
        }
        else if (temp < 15) {
            cout << "You're feeling hot\n";
        }
        else{
            cout << "You've got heatstroke and died\n";
        }
    }
};
class FallSpringClothes : public Clothes {
public:
    void wear(int temp) override {
        if (temp < -15) {
            cout << "You froze to death\n";
        }
        else if (temp < 0) {
            cout << "You're feeling cold\n";
        }
        else if (temp < 15) {
            cout << "You're feeling comfortable\n";
        }
        else if (temp < 30) {
            cout << "You're feeling hot\n";
        }
        else{
            cout << "You've got heatstroke and died\n";
        }
    }
};
class SummerClothes : public Clothes {
public:
    void wear(int temp) override {
        if (temp < 0) {
            cout << "You froze to death\n";
        }
        else if (temp < 10) {
            cout << "You're feeling cold\n";
        }
        else if (temp < 25) {
            cout << "You're feeling comfortable\n";
        }
        else if (temp < 40) {
            cout << "You're feeling hot\n";
        }
        else{
            cout << "You've got heatstroke and died\n";
        }
    }
};

class Wardrobe {
private:
    Clothes* content;
public:
    Wardrobe(Clothes* clothes) : content(clothes) {}
    void getDressed(int temp) {
        content->wear(temp);
    }
    Clothes *getContent() const {
        return content;
    }
    void setContent(Clothes *content) {
        Wardrobe::content = content;
    }
};

int main()
{
    Wardrobe* wardrobe = new Wardrobe(nullptr);
    wardrobe->setContent(new WinterClothes());
    wardrobe->getDressed(-10);
    wardrobe->getDressed(10);
    wardrobe->setContent(new FallSpringClothes());
    wardrobe->getDressed(-10);
    wardrobe->getDressed(10);
    wardrobe->setContent(new SummerClothes());
    wardrobe->getDressed(-10);
    wardrobe->getDressed(50);
}
