// Снимок — это поведенческий паттерн проектирования,
// который позволяет сохранять и восстанавливать прошлые
// состояния объектов, не раскрывая подробностей их реализации.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Класс создателя должен иметь специальный метод, который
// сохраняет состояние создателя в новом объекте-снимке.
class Code {
private:
    string code;
public:
    Code() { code = ""; }

    Code(const string &code) : code(code) {}

    const string &getCode() const {
        return code;
    }

    void setCode(const string &code) {
        Code::code = code;
    }
};

// VersionControl хранит прошлое состояние редактора.
class VersionControl {
    // Я не буду тут все дерево строить так что будет тупо мастер ветка
private:
    Branch *master;
public:
    VersionControl(Branch *master) : master(master) {};

    Branch *getMaster() const {
        return master;
    }

    void setMaster(Branch *master) {
        VersionControl::master = master;
    }
};

// В этом случае команда сохраняет состояния объекта -
// получателя, перед тем как передать ему своё действие. А в
// случае отмены команда вернёт объект в прежнее состояние.
class Branch {
private:
    int version;
    Code content;
public:
    Branch(int version, const Code &content
    ) : version(version), content(content) {};

    Branch(int version) : version(version) {
        content = Code("");
    };

    int getVersion() const {
        return version;
    }

    void setVersion(int version) {
        Branch::version = version;
    }

    const Code &getContent() const {
        return content;
    }

    void setContent(const Code &content) {
        Branch::content = content;
    }

    void commit(const Code &commitCode) {
        version++;
        this->content = commitCode;
    }

    void rollback(Code* rollbackCode) {
        rollbackCode->setCode(content.getCode());
    }

    void push(Branch *branch) {
        branch->setVersion(this->getVersion());
        branch->setContent(this->getContent());
    }

    void pull(Branch *branch) {
        this->setVersion(branch->getVersion());
        this->setContent(branch->getContent());
    }
};

int main() {
    Code* code = new Code("empty code");
    Branch *localBranch = new Branch(0, *code);
    Branch *masterBranch = new Branch(0);
    VersionControl *bucket = new VersionControl(masterBranch);
    code->setCode("some code");
    localBranch->commit(*code);
    localBranch->push(bucket->getMaster()); // Forbidden push
    cout << "[initial commit] current master branch code: " << bucket->getMaster()->getContent().getCode() << "\n";
    code->setCode("good code");
    localBranch->commit(*code);
    cout << "[before good changes] current master branch code: " << bucket->getMaster()->getContent().getCode() << "\n";
    localBranch->push(bucket->getMaster());
    cout << "[after good changes] current master branch code: " << bucket->getMaster()->getContent().getCode() << "\n";
    code->setCode("really bad code. Like, really bad");
    localBranch->commit(*code);
    code->setCode("no");
    cout << "[before rollback] current local branch code: " << localBranch->getContent().getCode() << "\n";
    cout << "[before rollback] current master branch code: " << bucket->getMaster()->getContent().getCode() << "\n";
    cout << "[before rollback] current code: " << code->getCode() << "\n";
    localBranch->pull(bucket->getMaster());
    localBranch->rollback(code);
    cout << "[after rollback] current local branch code: " << localBranch->getContent().getCode() << "\n";
    cout << "[after rollback] current master branch code: " << bucket->getMaster()->getContent().getCode() << "\n";
    cout << "[after rollback] current code: " << code->getCode() << "\n";
}