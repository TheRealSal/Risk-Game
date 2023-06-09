#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H


#include <iostream>
#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "../Strategy/PlayerStrategies.h"

using namespace std;


class Hand;
class Territory;
class OrdersList;

class Player {
public:
    string pName;
    vector<Territory* > territories;
    Hand* hand;
    OrdersList* orderList;
    int playerID;
    bool conqueredTerritoryThisTurn;
    int orderNumber;
    Player* negociatedPlayers[20];
    int reinforcementPool;
    int numPlayers;
    vector<Territory*> attackList;
    vector<Territory *> defendList;
    PlayerStrategy* playerStrategy;


    Player(); // default constructor
    Player(string pName, int id, PlayerStrategy* ps);
    Player(const Player &player);
    ~Player();   // deconstruct
    Player& operator=(const Player &player);


    void addToAttack(Territory *);
    void addToDefend(Territory*);
    void setName(string name);
    string getName();
    void setPlayerID(int id);
    vector<Territory *> getTerritory();
    void addOwnedTerritory(Territory* t);
    void removeOwnedTerritory(int id);
    void clearOrdersList();
    Hand *getHand();
    void addPlayerToNegociatedList(Player* p);
    void clearNegociatedList();
    OrdersList *getOrderList();
    void addArmies(int num);
    PlayerStrategy* getPlayerStrategy();

    bool isCheater();

    void setConqueredFlag(bool value);
    vector<Territory *> toDefend();
    void printDefendList(vector<Territory *> defendList);
    vector<Territory *> toAttack();
    void printAttackList(vector<Territory *> attackList);
    void printOwnedTerritoryList();
    bool issueOrder();
    void issue_Order(string type, Player* target, int armyCount, Territory* targetLocation, Territory* fromLocation);
    void printCurrentHand();

    bool isNeutral();
};

#endif //COMP345_PLAYER_H
