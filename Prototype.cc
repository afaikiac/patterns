// Прототип — это порождающий паттерн проектирования,
// который позволяет копировать объекты, не вдаваясь в
// подробности их реализации.

#include <iostream>
#include <string>

// Базовый прототип
class Text {
    protected:
        std::string* content;
    public:
        virtual void setContent(std::string* content) {}
        virtual std::string getContent() = 0;
        virtual Text* clone() const = 0;
};

// Конкретный прототип. Метод клонирования создаёт новый объект
// текущего класса, передавая в его конструктор ссылку на
// собственный объект. Благодаря этому операция клонирования
// получается атомарной — пока не выполнится конструктор, нового
// объекта ещё не существует. Но как только конструктор завершит
// работу, мы получим полностью готовый объект-клон, а не пустой
// объект, который нужно ещё заполнить.
class TermPaper : public Text {
    private:
        std::string author;

        TermPaper(const TermPaper& donor, std::string& author) {
            this->content = donor.content;
            this->author = author;
        }
    
    public:
        TermPaper() {};
        ~TermPaper() {
            delete content;
        }

        void setContent(std::string* content) override {
            this->content = content;
        }

        void setAuthor(std::string& author) {
            this->author = author;
        }

        std::string getContent() override {
            return *content;
        }

        std::string getAuthor() {
            return author;
        }

        TermPaper* clone() const {
            return new TermPaper(*this);
        }
};

int main() {
    TermPaper* termPaperDonor = new TermPaper();
    std::string content = "Very interesting content";
    std::string cleverAuthor = "Clever Author";
    termPaperDonor->setContent(&content);
    termPaperDonor->setAuthor(cleverAuthor);

    TermPaper* termPaperClone = termPaperDonor->clone();
    std::string sillyAuthor = "Silly Author";
    termPaperClone->setAuthor(sillyAuthor);

    std::cout << termPaperDonor->getAuthor() << ": " << termPaperDonor->getContent() << std::endl;
    std::cout <<termPaperClone->getAuthor() << ": " << termPaperClone->getContent() << std::endl;
}
