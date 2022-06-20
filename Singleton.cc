// Одиночка — это порождающий паттерн проектирования,
// который гарантирует, что у класса есть только один
// экземпляр, и предоставляет к нему глобальную
// точку доступа.

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Logger {
private:
    // Поле для хранения объекта-одиночки должно быть объявлено
    // статичным
    static Logger* logger;
    string target;
    // Конструктор одиночки всегда должен оставаться приватным,
    // чтобы клиенты не могли самостоятельно создавать
    // экземпляры этого класса через оператор `new`.
    Logger() {};
public:
    // Класс одиночки определяет статический метод `getLogger`,
    // который позволяет клиентам повторно использовать один и тот же logger.

    // Основной статический метод одиночки служит альтернативой
    // конструктору и является точкой доступа к экземпляру этого
    // класса.
    static Logger* getLogger(string target) {
        // На всякий случай ещё раз проверим, не был ли
        // объект создан другим потоком, пока текущий
        // ждал освобождения блокировки.
        if (logger == nullptr) {
            logger = new Logger();
            logger->target = target;
        }
        return logger;
    };

    static void close() {
        logger = nullptr;
    }

    // Наконец, любой класс одиночки должен иметь какую-то
    // полезную функциональность, которую клиенты будут
    // запускать через полученный объект одиночки.
    const string &getTarget() const {
        return target;
    }
};

Logger* Logger::logger = nullptr;

int main()
{
    Logger* coutLogger = Logger::getLogger("cout");
    Logger* fileLogger = Logger::getLogger("file");
    cout << coutLogger->getTarget() << "\n";
    cout << fileLogger->getTarget() << "\n";
    Logger::close();
    fileLogger = Logger::getLogger("file");
    coutLogger = Logger::getLogger("cout");
    cout << coutLogger->getTarget() << "\n";
    cout << fileLogger->getTarget() << "\n";
}