// Цепочка обязанностей — это поведенческий паттерн
// проектирования, который позволяет передавать запросы
// последовательно по цепочке обработчиков. Каждый
// последующий обработчик решает, может ли он обработать
// запрос сам и стоит ли передавать запрос дальше по цепи.

// С помощью Цепочки обязанностей вы можете связать потен-
// циальных обработчиков в одну цепь и при получении запро-
// са поочерёдно спрашивать каждого из них, не хочет ли он
// обработать запрос.

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// Интерфейс обработчиков.
class Student {
protected:
    Student *comrade;
public:
    virtual string doTask() {};
};

// Базовый класс простых компонентов.
class BestStudent : public Student {
public:
    BestStudent(Student *comrade) {
        Student::comrade = comrade;
    }

    string doTask() override {
        return "done by best student";
    }
};

class GoodStudent : public Student {
public:
    GoodStudent(Student *comrade) {
        Student::comrade = comrade;
    }

    string doTask() override {
        if (1 + rand() % 10 >= 3) {
            return "done by good student";
        }
        return comrade->doTask();

    }
};

class OkStudent : public Student {
public:
    OkStudent(Student *comrade) {
        Student::comrade = comrade;
    }

    string doTask() override {
        if (1 + rand() % 10 >= 5) {
            return "done by ok student";
        }
        return comrade->doTask();

    }
};

class BadStudent : public Student {
public:
    BadStudent(Student *comrade) {
        Student::comrade = comrade;
    }

    string doTask() override {
        if (1 + rand() % 10 >= 8) {
            return "done by bad student";
        }
        return comrade->doTask();
    }
};

class Me : public Student {
public:
    Me(Student *comrade) {
        Student::comrade = comrade;
    }

    string doTask() override {
        if (1 + rand() % 100 >= 100) {
            return "miracle";
        }
        return comrade->doTask();

    }
};

int main() {
    std::srand(std::time(nullptr));
    Student *bestStudent = new BestStudent(nullptr);
    Student *goodStudent = new GoodStudent(bestStudent);
    Student *okStudent = new OkStudent(goodStudent);
    Student *badStudent = new BadStudent(okStudent);
    Me *me = new Me(badStudent);

    cout << me->doTask() << "\n";
    cout << me->doTask() << "\n";
    cout << me->doTask() << "\n";
    cout << me->doTask() << "\n";
    cout << me->doTask() << "\n";
}