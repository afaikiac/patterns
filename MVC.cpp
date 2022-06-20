#include <iostream>
#include <string>


class View {
private:
    std::string base;
public:
    View(const std::string &base) : base(base) {}

    void writeNumber(int n) {
        std::cout << base << ": " <<  n << "\n";
    }
};

class Model {
private:
    View view;
    int number;

public:
    Model(const View &view) : view(view) {
        number = 0;
    }

    int getNumber() const {
        return number;
    }

    void setNumber(int n) {
        number = n;
        view.writeNumber(n);
    }
};

class Controller {
private:
    Model model;

public:
    Controller(Model model) : model(model) {}

    void add(int n) {
        model.setNumber(model.getNumber() + n);
    }

    void sub(int n) {
        model.setNumber(model.getNumber() - n);
    }

};

int main() {
   View view("cout");
   Model model(view);
   Controller controller(model);
   controller.add(10);
   controller.sub(5);
}