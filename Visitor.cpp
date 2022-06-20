// Посетитель — это поведенческий паттерн проектирования,
// который позволяет добавлять в программу новые операции,
// не изменяя классы объектов, над которыми эти операции
// могут выполняться.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Player;

class GameServer
{
protected:
    int type;
public:
    virtual void accept(Player* player) = 0;

    int getType() const {
        return type;
    }
};

class Player
{
public:
    virtual void play(GameServer* server) = 0;
};

class GoodServer : public GameServer
{
public:
    GoodServer() {type = 1;}

    void accept(Player* player) override {
        player->play(this);
    }
};

class DecentServer : public GameServer
{
public:
    DecentServer() {type = 2;}

    void accept(Player* player) override {
        player->play(this);
    }
};

class ToxicServer : public GameServer
{
public:
    ToxicServer() {type = 3;}

    void accept(Player* player) override {
        player->play(this);
    }
};

class GoodPlayer : public Player
{
public:
    void play(GameServer *server) override {
        switch (server->getType()) {
            case 1:
                cout << "Good player had fun on good server\n";
                break;
            case 2:
                cout << "Good player had fun on decent server\n";
                break;
            case 3:
                cout << "Good player quickly left toxic server\n";
                break;
        }
    }
};

class DecentPlayer : public Player
{
public:

    void play(GameServer *server) override {
        switch (server->getType()) {
            case 1:
                cout << "Decent player had fun on good server\n";
                break;
            case 2:
                cout << "Decent player had average experience on decent server\n";
                break;
            case 3:
                cout << "Decent player quickly left toxic server\n";
                break;
        }
    }
};

class ToxicPlayer : public Player
{
public:

    void play(GameServer *server) override {
        switch (server->getType()) {
            case 1:
                cout << "Toxic player was kicked from good server\n";
                break;
            case 2:
                cout << "Toxic player ruined other players experience on decent server\n";
                break;
            case 3:
                cout << "Toxic player relished on toxic server\n";
                break;
        }
    }
};

int main()
{
    GameServer* goodServer = new GoodServer();
    GameServer* decentServer = new DecentServer();
    GameServer* toxicServer = new ToxicServer();

    Player* goodPlayer = new GoodPlayer();
    Player* decentPlayer = new DecentPlayer();
    Player* toxicPlayer = new ToxicPlayer();

    goodServer->accept(goodPlayer);
    goodServer->accept(decentPlayer);
    goodServer->accept(toxicPlayer);
    decentServer->accept(toxicPlayer);
    toxicServer->accept(goodPlayer);
    toxicServer->accept(toxicPlayer);
}