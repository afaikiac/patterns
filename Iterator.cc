// Итератор — это поведенческий паттерн проектирования,
// который даёт возможность последовательно обходить
// элементы составных объектов, не раскрывая их
// внутреннего представления.

// Итератор предоставляет клиенту всего несколько простых
// методов перебора элементов коллекции. Это не только
// упрощает доступ к коллекции, но и защищает её данные от
// неосторожных или злоумышленных действий.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Book {
private:
    vector<string> pages;
    string title;
public:
    Book(const string &title, const vector<string> &pages) : pages(pages), title(title) {}

    int getSize() {
        return pages.size();
    }

    string getPage(int i) {
        return pages[i];
    }

};

// Общий интерфейс коллекций должен определить фабричный метод
// для производства итератора. Можно определить сразу несколько
// методов, чтобы дать пользователям различные варианты обхода
// одной и той же коллекции.
// Конкретная коллекция знает, объекты каких итераторов нужно
// создавать.
class Reader {
private:
    vector<Book*> books;
    int currentBook;
    int currentPage;
public:
    Reader(const vector<Book *> &books) : books(books) {}

    Reader* first() {
        currentBook = 0;
        currentPage = 0;
        return this;
    }
    Reader* next() {
        currentPage++;
        if (currentPage == books[currentBook]->getSize()) {
            currentBook++;
            currentPage = 0;
        }
        return this;
    }
    bool isDone() {
        return currentBook == books.size();
    }
    string currentItem() {
        return books[currentBook]->getPage(currentPage);
    }
};


int main() {
    vector<Book*> bookshelf = {
        new Book("firstBook", {"1", "2", "3"}),
        new Book("secondBook", {"4", "5", "6"}),
        new Book("thirdBook", {"7", "8", "9"})
    };
    Reader* reader = new Reader(bookshelf);
    reader->first();
    while (!reader->isDone()) {
        cout << reader->currentItem() << "\n";
        reader->next();
    }
}