// Посредник — это поведенческий паттерн проектирования,
// который позволяет уменьшить связанность множества
// классов между собой, благодаря перемещению этих связей
// в один класс-посредник.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Классы компонентов общаются с посредниками через их общий
// интерфейс. Благодаря этому одни и те же компоненты можно
// использовать в разных посредниках.
class Worker {};

// Общий класс посредников.
class BugTracker {
protected:
    vector<Worker*> devs;
    vector<Worker*> testers;
public:
    virtual void addBug(string bug) {};
    virtual void fixBug(string bug) {};

    virtual void setDevs(const vector<Worker *> &devs) {
        BugTracker::devs = devs;
    }

    virtual void setTesters(const vector<Worker *> &testers) {
        BugTracker::testers = testers;
    }

};

// Конкретные компоненты не связаны между собой напрямую. У них
// есть только один канал общения — через отправку уведомлений
// посреднику.
class DevOps : public Worker {
private:
    BugTracker* bugTracker;
    string name;
public:
    DevOps(
        BugTracker *bugTracker,
        const string &name
    ) : bugTracker(bugTracker), name(name) {}

    void addBug(string bug) {
        cout << name << " added bug: " << bug << "\n";
        bugTracker->addBug(bug);
    }

    void fixBug(string bug) {
        cout << name << " fixed bug: " << bug << "\n";
    }
};

class Tester : public Worker  {
private:
    BugTracker* bugTracker;
    string name;
public:
    Tester(
        BugTracker *bugTracker,
        const string &name
    ) : bugTracker(bugTracker), name(name) {}

    void findBug(string bug) {
        cout << name << " found bug: " << bug << "\n";
        bugTracker->fixBug(bug);
    }
};

// Конкретный посредник. Все связи между конкретными
// компонентами переехали в код посредника.
class Jira : public BugTracker {
protected:
    vector<DevOps*> devs;
    vector<Tester*> testers;
public:

    void addBug(string bug) override {
        Jira::testers[rand() % testers.size()]->findBug(bug);
    }
    void fixBug(string bug) override {
        Jira::devs[rand() % devs.size()]->fixBug(bug);
    }

    void setDevs(const vector<DevOps *> &devs) {
        Jira::devs = devs;
    }

    void setTesters(const vector<Tester *> &testers) {
        Jira::testers = testers;
    }

};

int main()
{
    Jira* bugTracker = new Jira();
    DevOps* dev1 = new DevOps(bugTracker, "Dev1");
    DevOps* dev2 = new DevOps(bugTracker, "Dev2");
    DevOps* dev3 = new DevOps(bugTracker, "Dev3");
    Tester* test1 = new Tester(bugTracker, "Test1");
    Tester* test2 = new Tester(bugTracker, "Test2");
    bugTracker->setDevs({dev1, dev2, dev3});
    bugTracker->setTesters({test1, test2});
    dev1->addBug("bug1");
    dev2->addBug("bug2");
    dev3->addBug("bug3");
}
