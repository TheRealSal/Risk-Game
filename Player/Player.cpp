#pragma once
#include "Player.h"
#include <algorithm>
#include <cctype>

// Implementation of Player class
Player::Player(){
    this->pName = "default";
    this->territories = vector<Territory *>();
    this->hand = new Hand();
    this->playerID = 0;
    this->orderList = new OrdersList(this->playerID);
    this->orderNumber = 0;
    this->playerStrategy = new DefaultPlayerStrategy();
    
}

// parametrized constructor
Player::Player(string pName, int id, PlayerStrategy* ps){
    this->pName = pName;
    this->territories = vector<Territory*>();
    this->hand = new Hand();
    this->playerID = id;
    this->orderList = new OrdersList(id);
    this->orderNumber = 0;
    this->playerStrategy = ps;
}

// copy constructor
Player::Player(const Player &player){
    pName = player.pName;
    territories = player.territories;
    hand = player.hand;
    orderList = player.orderList;
    this->playerID = player.playerID;
    this->orderNumber = player.orderNumber;
}

// destructor
Player::~Player(){
    territories.clear();
    delete hand;
    hand = nullptr;
    delete orderList;
    orderList = nullptr;
}

// assignment operator
Player& Player::operator=(const Player& player){
    this->pName = player.pName;
    this->territories = player.territories;
    this->hand = player.hand;
    this->orderList = player.orderList;
    this->playerID = player.playerID;
    this->orderNumber = player.orderNumber;
    return *this;
}

// stream insertion operator
ostream &operator <<(std::ostream &strm, const Player &player){
    cout << "Player name = " << player.pName << endl;
    cout << "Player ID = " << player.playerID << endl;
    cout << "\tTerritories = ";
    for (int i = 0; i < player.territories.size(); ++i) {
        cout << player.territories[i] << ", ";
    }
    cout << endl;
    cout << "\tCards in hand = " << player.hand;
    cout << "\tOrder list = " << player.orderList;
    return cout;
}

// getter & setter for player names
void Player:: setName(string name){
    pName = name;
}

//Sets the Player ID
void Player::setPlayerID(int id) {
    playerID = id;
}

//clears the Orders List
void Player::clearOrdersList() {
    orderList->clearOrdersList();
}

string Player::getName(){
    return pName;
}

// getter for territory
vector <Territory *> Player::getTerritory(){
    return territories;
}

// getter for Hand cards
Hand* Player::getHand(){
    return hand;
}

// getter for Order List
OrdersList* Player::getOrderList(){
    return orderList;
}

//Adds a Territory to the list of owned Territory
void Player::addOwnedTerritory(Territory* t) {
    if (t->owner != NULL) {
        t->owner->removeOwnedTerritory(t->id);
    }
    t->changeOwner(this);
    bool found = false;
    for (int i = 0; i < territories.size(); i++) {
        if (territories.at(i) == t) {
            found = true;
            break;
        }
    }
    if (!found) {
        territories.push_back(t);
    }

}

//Removes a Territory from the list of owned Territory with the same territory ID
void Player::removeOwnedTerritory(int id) {
    for (int i = 0; i < territories.size(); i++) {
        if (territories.at(i)->id == id) {
            territories.erase(territories.begin() + i);
        }
    }
}

// print Owned list
void Player::printOwnedTerritoryList() {
    for (int i = 0; i < territories.size(); i++) {
        cout << territories.at(i)->name << "\n";
    }
}

// return a list of territories that are to be defended
vector<Territory *> Player::toDefend(){
    return playerStrategy->to_defend(this);;
}

// print defend list
void Player::printDefendList(vector<Territory *> defendList){
    for (int i = 0; i < defendList.size(); i++) {
        cout << "Defend list = " << defendList.at(i)->name << "\n" ;
    }
    cout << endl;
}

// return a list of territories that are to be attacked
vector<Territory *> Player::toAttack(){
    return playerStrategy->to_attack(this);
}

//Adds a territory to the attack list
void Player::addToAttack(Territory * t) {
    if (t->owner->playerID == this->playerID) {
        cout << "\nCannot add territory to attack list: Territory is owned by the player.\n";
    }
    else if (std::find(attackList.begin(), attackList.end(), t) != attackList.end()){
        cout << "\nCannot add territory to attack list: Territory already in list.\n";
    }
    else {
        attackList.push_back(t);
        cout << "\nAdded territory - " << t->id << " - to " << this->pName << "\'s attack list.\n";
    }
}

//Adds a territory to the defend list
void Player::addToDefend(Territory* t) {
    if (t->owner->playerID != this->playerID) {
        cout << "\nCannot add territory to attack list: Territory is not owned by the player.\n";
    }
    else if (std::find(defendList.begin(), defendList.end(), t) != defendList.end()) {
        cout << "\nCannot add territory to attack list: Territory already in list.\n";
    }
    else {
        defendList.push_back(t);
        cout << "\nAdded territory - " << t->id << " - to " << this->pName << "\'s defend list.\n";
    }
}

// print attack list
void Player::printAttackList(vector<Territory *> attackList){
    for (int i = 0; i < attackList.size(); i++) {
        cout << "Attack list = " << attackList.at(i)->name << "\n";
    }
}

bool Player::issueOrder() {
    return playerStrategy->issueOrder(this);
}

//  creates an order object and adds it to the list of orders.
void Player::issue_Order(string type, Player* target, int armyCount, Territory* targetLocation, Territory* fromLocation) {
    Orders* order{};
    
    std::transform(type.begin(), type.end(), type.begin(),
        [](unsigned char c) { return std::tolower(c); });
    PlayerStrategy* neutral = new NeutralPlayerStrategy();
    if (type == "deploy") {
        order = new Deploy(this, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "airlift") {
        order = new Airlift(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    //Fix the target player to be neutral not by creating a new player but asign it it to the current neutral player.
    else if (type == "blockade") {
        Player* n = new Player("neutralplaceholder", -1, neutral);
        order = new Blockade(n, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "bomb") {
        order = new Bomb(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "advance") {
        order = new Advance(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "negociate") {
        order = new Negociate(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }
    else if (type == "steal") {
        order = new Steal(target, this, armyCount, targetLocation, fromLocation, orderNumber);
    }

    orderNumber++;
    orderList->add(order);  // adding order to the list
    cout << "Order has been added to the list" << endl;
}

//Helper funtion for the driver to show current hand.
void Player::printCurrentHand() {
    for(int i = 0; i < 7; i++) {
        hand->addCard(new Card(rand() % 5));
    }

    hand->showHand();

}

//Sets a flag if the player conquered a territory or not this turn
void Player::setConqueredFlag(bool value) {
    cout << "\nPlayer: " << pName << " is now set to recieve an extra card at the end of turn!\n";
    conqueredTerritoryThisTurn = value;
}

//Adds a player to the list of negociated PLayers
void Player::addPlayerToNegociatedList(Player* p) {
    int count = 0;
    for (Player* i : negociatedPlayers) {
        if (i == NULL) {
            break;
        }
        count++;
    }
    negociatedPlayers[count] = p;
}


//Empty the array of negociated PLayers
void Player::clearNegociatedList() {
    int count = 0;
    for (Player* i : negociatedPlayers) {
        delete i;
        i = NULL;
    }

}

// Adds specified number to the player's reinforcement pool
void Player::addArmies(int num) {
    this->reinforcementPool += num;
}

//returns the PlayerStrategy
PlayerStrategy* Player::getPlayerStrategy() {
    return this->playerStrategy;
}

bool Player::isCheater() {
    return this->playerStrategy->getStrategyName() == "Cheater";
}

bool Player::isNeutral() {
    return this->playerStrategy->getStrategyName() == "Neutral";
}