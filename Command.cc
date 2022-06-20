// Команда — это поведенческий паттерн проектирования,
// который превращает запросы в объекты, позволяя
// передавать их как аргументы при вызове методов, ставить
// запросы в очередь, логировать их, а также поддерживать
// отмену операций.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Абстрактная команда задаёт общий интерфейс для конкретных
// классов команд и содержит базовое поведение отмены операции.
class Task {
private:
    int difficulty;
    string name;
public:
    Task(int difficulty, const string &name) : difficulty(difficulty), name(name) {}

    int getDifficulty() const {
        return difficulty;
    }

    const string &getName() const {
        return name;
    }
};

// Класс содержит непосредственно метод выполнения таски.
// Он отыгрывает роль получателя — команды делегируют
// ему свои действия.
class Cook {
private:
    string name;
public:
    Cook(const string &name) : name(name) {}

    string doTask(Task* task) {
        return "Task " + task->getName() + " is done by " + name + "\n";
    }
};

// Класс настраивает объекты для совместной работы.
// Он выступает в роли отправителя — создаёт команды, чтобы
// выполнить какие-то действия.
class Chief {
private:
    vector<Task*> tasks;
    vector<Cook*> cooks;
    string name;
public:
    Chief(const string &name) : name(name) {}

    const vector<Task *> &getTasks() const {
        return tasks;
    }

    void setTasks(const vector<Task *> &tasks) {
        Chief::tasks = tasks;
    }

    const vector<Cook *> &getCooks() const {
        return cooks;
    }

    void setCooks(const vector<Cook *> &cooks) {
        Chief::cooks = cooks;
    }

    void doTasks() {
        for (int i = 0; i < tasks.size(); ++i) {
            if (tasks[i]->getDifficulty() <= 5) {
                cout << "delegating " << tasks[i]->getName() << " to cooks: "
                << cooks[rand() % cooks.size()]->doTask(tasks[i]);
            }
            else {
                cout << "doing " << tasks[i]->getName() << " by myself\n";
            }
        }
    }
};

int main() {
    Chief* chief = new Chief("Remy");
    chief->setCooks({new Cook("Alfredo"), new Cook("Horst"), new Cook("Colette")});
    chief->setTasks({new Task(2, "task1"), new Task(7, "task2"),
                     new Task(4, "task3"), new Task(3, "task4"),
                     new Task(10, "come up with task names")});
    chief->doTasks();

}