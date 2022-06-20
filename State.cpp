// Состояние — это поведенческий паттерн проектирования,
// который позволяет объектам менять поведение в
// зависимости от своего состояния. Извне создаётся
// впечатление, что изменился класс объекта.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Cup;
// Общий интерфейс всех состояний.
class CupState {
public:
    virtual void drink(Cup* cup) = 0;
    virtual void fill(Cup* cup) = 0;
};
// Конкретные состояния реализуют методы абстрактного состояния
// по-своему.
class EmptyCup : public CupState
{
public:
    void drink(Cup* cup);
    void fill(Cup* cup);
};
class HaflFullCup : public CupState
{
public:
    void drink(Cup* cup);
    void fill(Cup* cup);
};
class HaflEmptyCup : public CupState
{
public:
    void drink(Cup* cup);
    void fill(Cup* cup);
};
class FullCup : public CupState
{
public:
    void drink(Cup* cup);
    void fill(Cup* cup);
};
// Cup выступает в роли контекста.
class Cup
{
private:
    CupState* state;
public:
    Cup() {state = new EmptyCup();}

    void drink() {
        state->drink(this);
    }
    void fill() {
        state->fill(this);
    }

    CupState *getState() const {
        return state;
    }

    void setState(CupState *state) {
        Cup::state = state;
    }
};

// Методы будут делегировать работу активному состоянию.
void EmptyCup::drink(Cup *cup) {
    cout << "You can't drink from the empty cup\n";
}
void EmptyCup::fill(Cup *cup) {
    cout << "Cup is now half-full\n";
    cup->setState(new HaflFullCup());
}
void HaflFullCup::drink(Cup *cup) {
    cout << "Cup is now empty\n";
    cup->setState(new EmptyCup());
}
void HaflFullCup::fill(Cup *cup) {
    cout << "Cup is now full\n";
    cup->setState(new FullCup());
}
void HaflEmptyCup::drink(Cup *cup) {
    cout << "Cup is now empty\n";
    cup->setState(new EmptyCup());
}
void HaflEmptyCup::fill(Cup *cup) {
    cout << "Cup is full\n";
    cup->setState(new FullCup());
}
void FullCup::drink(Cup *cup) {
    cout << "Cup is now half-empty\n";
    cup->setState(new HaflEmptyCup());
}
void FullCup::fill(Cup *cup) {
    cout << "You've spilled water\n";
}

int main() {
    Cup* glass = new Cup();
    glass->fill();
    glass->fill();
    glass->fill();
    glass->drink();
    glass->drink();
    glass->drink();
}