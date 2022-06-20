// Наблюдатель — это поведенческий паттерн
// проектирования, который создаёт механизм подписки,
// позволяющий одним объектам следить и реагировать на
// события, происходящие в других объектах.

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class PirateCompany;

class Game {
private:
    vector<string> features;
    string name;
public:
    Game(const string &name, const vector<string> &features) : features(features), name(name) {}

    void addFeature(string feature) {
        features.push_back(feature);
    }
    const vector<string> &getFeatures() const {
        return features;
    }

    const string &getName() const {
        return name;
    }

    void describe() {
        string featureList = "";
        for (int i = 0; i < features.size() - 1; ++i) {
            featureList += features[i] + ", ";
        }
        if (!features.empty()) {
            featureList += features[features.size() - 1];
        }
        cout << name << ": " << featureList << "\n";
    }
};

class GameCompany {
    vector<PirateCompany*> pirates;
    string name;
public:
    GameCompany(const string &name) : name(name) {}

    void addPirate(PirateCompany* pirate) {
        pirates.push_back(pirate);
    }
    Game* releaseGame(const string &name, const vector<string> &features);
};

class PirateCompany {
protected:
    vector<GameCompany*> publishers;
    string name;
    int skill;
public:
    PirateCompany(const string &name, const int &skill) : name(name), skill(skill) { }

    const vector<GameCompany *> &getPublishers() const {
        return publishers;
    }
    void addPublisher(GameCompany* publisher) {
        publishers.push_back(publisher);
        publisher->addPirate(this);
    }

    virtual Game* pirateGame(Game* game) {
        if (rand() % 10 + 1 <= skill) {
            vector<string> origFeatures = game->getFeatures();
            vector<string> piratedFeatures;
            for (int i = 0; i < origFeatures.size(); ++i) {
                if (rand() % 100 + 1 <= 70) {
                    piratedFeatures.push_back(origFeatures[i]);
                }
            }
            Game* piratedGame = new Game(game->getName(),  piratedFeatures);
            cout << name << " has pirated new game: ";
            piratedGame->describe();
            return piratedGame;
        }
        cout << name << " has failed to pirate new game\n";
        return nullptr;
    };
};

Game* GameCompany::releaseGame(const string &gameName, const vector<string> &features) {
    Game* newGame = new Game(gameName, features);
    cout << name << " has released new game: ";
    newGame->describe();
    for (int i = 0; i < pirates.size(); i++)
        pirates[i]->pirateGame(newGame);
    return newGame;
}

int main() {
    std::srand(std::time(nullptr));
    GameCompany* goodCompany1 = new GameCompany("Ghost Ship Games");
    GameCompany* goodCompany2 = new GameCompany("Kojima Productions"); // Кодзима гений

    PirateCompany* pirateCompany1 = new PirateCompany("Stronk pirates", 8);
    PirateCompany* pirateCompany2 = new PirateCompany("Pathetic pirates", 3);

    pirateCompany1->addPublisher(goodCompany1);
    pirateCompany1->addPublisher(goodCompany2);
    pirateCompany2->addPublisher(goodCompany1);
    pirateCompany2->addPublisher(goodCompany2);

    goodCompany1->releaseGame("Deep Rock Galactic", { "Danger", "Darkness", "Dwarves", "Multiplayer", "Beer"});
    cout << "-----------\n";
    goodCompany2->releaseGame("Death Stranding", { "Walking", "Cargo", "Plot"});
}