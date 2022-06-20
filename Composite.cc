// Компоновщик — это структурный паттерн проектирования,
// который позволяет сгруппировать множество объектов в
// древовидную структуру, а затем работать с ней так, как
// будто это единичный объект.

// Паттерн Компоновщик предлагает хранить в составных объ-
// ектах ссылки на другие простые или составные объекты. Те,
// в свою очередь, тоже могут хранить свои вложенные объ-
// екты и так далее. В итоге вы можете строить сложную дре-
// вовидную структуру данных, используя всего две основные
// разновидности объектов.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Общий интерфейс компонентов
class Readable {
public:
    virtual void read() {};
    virtual int getSize() {return 0;};
};

// Простой компонент
class Page : public Readable {
private:
    string content;
public:
    Page(const string &content) : content(content) {};

    void read() override {
        cout << content << "\n";
    }

    int getSize() override {
        return 1;
    }
};

// Компоненты могут расширять другие компоненты.
class Book : public Readable {
private:
    vector<Page *> pages;
    string title;
public:
    Book(const string &title, const vector<Page *> &pages) : pages(pages), title(title) {}

    void read() override {
        cout << title << ":\n";
        for (int i = 0; i < pages.size(); ++i) {
            pages[i]->read();
        }
    }

    int getSize() override {
        return pages.size();
    }

};

// Контейнер содержит операции добавления/удаления дочерних
// компонентов. Все стандартные операции интерфейса компонентов
// он делегирует каждому из дочерних компонентов.
class Bookshelf : public Readable {
private:
    vector<Book *> books;
    string section;
public:
    Bookshelf(const string &section) : section(section) {};

    // Добавить компонент в список дочерних.
    void addBook(Book *book) {
        books.push_back(book);
    }

    void read() override {
        // Граница всей области
        cout << "---" << section << "---\n";
        //  Для каждого дочернего компонента прочитать его.
        for (int i = 0; i < books.size(); ++i) {
            books[i]->read();
        }
    }

    int getSize() override {
        return books.size();
    }
};

int main() {
    Bookshelf *bookshelf = new Bookshelf("Fantasy");
    bookshelf->addBook(new Book("short book", {new Page("page of the short book")}));
    bookshelf->addBook(new Book("long book", {new Page("first page"), new Page("..."),
                                              new Page("last page")}));
    bookshelf->read();
}
