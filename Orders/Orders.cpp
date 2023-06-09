#include "Orders.h"
#include <iostream>

/*
* Constructor
*/
Orders::Orders() {
	this->player = NULL;
	this->target = NULL;
	this->armyCount = 0;
	this->targetLocation = 0;
	this->fromLocation = 0;
	this->orderNumber = 0;
}

/*
* Deconstructor
*/
Orders::~Orders() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;
}

/*
* Gets the current order type as a string.
*/
string Orders::getCurrentOrder(void) {
	return currentOrder;
}

/*
* Gets the current player ID the order is targeted to.
*/
Player* Orders::getOrderTargetPlayer(void) {
	return target;
}

/*
* Gets the current army count affected with the order
*/
int Orders::getOrderArmyCount(void) {
	return armyCount;
}

/*
* Gets the current player ID the order is assigned to.
*/
Player* Orders::getOrderIssuer(void) {
	return player;
}

/*
* Gets the order ID.
*/
int Orders::getOrderNumber() {
	return orderNumber;
}

/*
* Gets the target the location ID
*/
Territory* Orders::getTargetLocation() {
	return targetLocation;
}

/*
* Gets the location ID the order is coming from
*/
Territory* Orders::getIssuerLocation() {
	return fromLocation;
}

/*
* Validate function, will be overriden by the subclasses
*/
bool Orders::validate() {
	return false;
}

/*
* execute function, will be overriden by the subclasses
*/
bool Orders::execute() {
	notify(this);
	return false;
}

/*
* Stream Insertion operator
*/
ostream& operator << (ostream& out, const Orders& o)
{
	out << "Order ID: " << o.orderNumber;
	out << " - Player " << o.player->pName;
	out << " issued the order: \"" << o.currentOrder;
	out << "\" to target Player: \"" << o.target->pName;
	out << "\" from: \"" << o.fromLocation->name;
	out << "\" to \"" << o.targetLocation->name << "\".";
	return out;
}

/*
* Stream Input Operator TODO
*/
istream& operator >> (istream& in, Orders& o)
{
	return in;
}


/*
* toString() Implementation.
*/
string Orders::toString(void) {
	string returnString;
	returnString.append("Order#: ");
	returnString.append(to_string(orderNumber));
	returnString.append(" - Player ");
	returnString.append(player->pName);
	returnString.append(" issued the order: \"");
	returnString.append(currentOrder);
	returnString.append("\" to target Player: \"");
	returnString.append(target->pName);
	returnString.append("\" from: \"");
	returnString.append(getIssuerLocation()->name);
	returnString.append("\" to \"");
	returnString.append(getTargetLocation()->name);
	returnString.append("\".");

	return returnString;
}

/*
* Assignment Operator
*/
void Orders::operator = (const Orders& o) {
	this->target = o.target;
	this->player = o.player;
	this->armyCount = o.armyCount;
	this->targetLocation = o.targetLocation;
	this->fromLocation = o.fromLocation;
	this->orderNumber = o.orderNumber;
	this->currentOrder = o.currentOrder;
}

/****************ORDERS LIST CLASS****************/

/*
* This class creates a doubly linked list to store all the ORders currently requested by a player.
*/

/*
* Constructor
*/
OrdersList::OrdersList(int player) {
	this->player = player;
	hasOrdersInList = false;
	lastOrderModifiedIndex = 0;
	orderNumber = 0;
}

/*
* Deconstructor
*/
OrdersList::~OrdersList() {
	ordersList.clear();
}

/*
* Copy function (REQUIREMENT).
*/
OrdersList* OrdersList::copy(OrdersList* orderList) {
	OrdersList* copy = new OrdersList(orderList->getPlayerID());

	copy->lastOrderModifiedIndex = orderList->getLastOrderModified();
	copy->ordersList = orderList->getCurrentOrdersList();
	copy->hasOrdersInList = orderList->hasOrdersInList;
	copy->orderNumber = orderList->orderNumber;

	return copy;
}

/*
* clears the Orders List.
*/
void OrdersList::clearOrdersList() {
	ordersList.clear();
}


/*
* Returns the Player ID this list is attributed to
*/
int OrdersList::getPlayerID() {
	return player;
}


/*
* Adds an Order to the list.
*/
void OrdersList::add(Orders* order) {
	ordersList.push_back(order);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = (int)ordersList.size() - 1;
	hasOrdersInList = true;
	notify(this);
}

/*
* Moves the order in the list. Takes an index of the order to move, and a target index.
*
* Moves order from index "index" to index "toIndex"
*
*/
void OrdersList::move(int index, int toIndex) {
	//Creates Iterator
	list<Orders*>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Copy the Order.
	Orders* orderToMove = *it;
	//Erase the Order.
	ordersList.erase(it);

	//Start at the beginning of the list
	it = ordersList.begin();
	//Advance to new index
	advance(it, toIndex);
	//Insert the previously Copied Order.
	ordersList.insert(it, orderToMove);

	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = toIndex;
}

/*
* Removes the order at the requested Index
*/
void OrdersList::remove(int index) {
	//Creates Iterator
	list<Orders*>::iterator it;
	//Starts at the beginning of the list.
	it = ordersList.begin();
	//Advances to the desired Index
	advance(it, index);
	//Check if the order is correct
	Orders* orderToRemove = *it;

	//Erase the Order.
	ordersList.erase(it);
	//Update lastOrderModifiedIndex
	lastOrderModifiedIndex = index;

	if ((int)ordersList.size() == 0) {
		hasOrdersInList = false;
	}
}

/*
* Validates the whole orders lists.
*/
bool OrdersList::validate()
{
	list<Orders*>::iterator it;

	for (it = ordersList.begin(); it != ordersList.end(); it++) {
		Orders* current = *it;
		if (!current->validate()) {
			return false;
		}
	}

	return true;
}

/*
* Executes all the orders.
*/
bool OrdersList::execute()
{
	list<Orders*>::iterator it;
	bool flag = true;
	Orders* current;

	for (auto it = ordersList.begin(); it != ordersList.end();) {
		current = *it;
		if (current->execute()) {
			it = ordersList.erase(it);
		}
		else {
			cout << "\nOrder number " << current->getOrderNumber() << " failed to execute.";
			flag = false;
			++it;
		}
	}

	return flag;
}

/*
* Removes a specific order
*/
void OrdersList::removeOrder(Orders* order) {
	//Creates Iterator
	list<Orders*>::iterator it;
	Orders* current;
	for (auto it = ordersList.begin(); it != ordersList.end();) {
		current = *it;
		if (current == order) {
			it = ordersList.erase(it);
		}
		else {
			++it;
		}
	}
}

/*
* Gets the current size of the list, i.e. the number of orders the player has.
*/
int OrdersList::getCurrentNumberOfOrders()
{
	return (int)ordersList.size();
}

/*
* Helper function, returns the index of the last modified order (addition, deletion, etc..)
*/
int OrdersList::getLastOrderModified()
{
	return lastOrderModifiedIndex;
}

/*
* Gets the last Order in the list.
*/
Orders* OrdersList::getLastOrder()
{
	return ordersList.back();
}

/*
* Gets the first Order in the list.
*/
Orders* OrdersList::getNextOrder()
{
	return ordersList.front();
}

/*
* Returns the list.
*/
list<Orders*> OrdersList::getCurrentOrdersList()
{
	return ordersList;
}

/*
* Assignment Operator
*/
void OrdersList::operator = (const OrdersList& o) {
	this->ordersList = o.ordersList;
	this->player = o.player;
	hasOrdersInList = o.hasOrdersInList;
	lastOrderModifiedIndex = o.lastOrderModifiedIndex;
	orderNumber = o.orderNumber;
}


/****************DEPLOY ORDER LIST CLASS****************/

/*
* Constructor
*/
Deploy::Deploy(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Deploy";
}

/*
* Deconstructor
*/
Deploy::~Deploy() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;
}

/*
* Validates the order, returns true or false
*/
bool Deploy::validate() {
	cout << "\nValidating Deploy order: \"" << this->toString();
	if (targetLocation->owner != player) {
		cout << "\nThe player doesn't own the selected territory.";
		return false;
	}
	return true;
}

/*
* Executes the Order returns true is successful
*/
bool Deploy::execute() {
	if (validate()) {
		targetLocation->addArmies(armyCount);

		notify(this);
		return true;
	}
	return false;
}


/*
* Copy function (REQUIREMENT).
*/
Deploy Deploy::copy(Deploy order) {
	Deploy copy = Deploy(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************ADVANCE ORDER LIST CLASS****************/

/*
* Constructor
*/
Advance::Advance(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Advance";
}

/*
* Deconstructor
*/
Advance::~Advance() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;

}

/*
* Validates the order, returns true or false
*/
bool Advance::validate() {
	cout << "\nValidating Advance order: \n\"" << this->toString() << "\"";
	bool flag = true;

	//Check ownerships
	if (fromLocation->owner != player) {
		cout << "\nFAILED: The player doesn't own the source territory to advance.";
		flag = false;
		return flag;
	}

	//check if the player has enough army.
	if (fromLocation->numArmies < armyCount) {
		cout << "\nFAILED: The player doesn't have enough armies asked by the order in the source territory to advance.";
		return false;
	}

	bool found = false;
	found = fromLocation->isAnEdge(targetLocation);


	if (!found) {
		cout << "\nFAILED: The source territory doesn't have a connected edge with the target territory to advance.";
		flag = false;
		return flag;
	}

	for (Player* p : player->negociatedPlayers) {
		if (p == target) {
			cout << "\nFAILED: The target player currently has a negociated contract and cannot be attacked.";
			return false;
		}
	}

	cout << "\nVALIDATED.";
	return flag;
}

/*
* Executes the Order returns true is successful
*/
bool Advance::execute() {

	int probabilityAttackers = 60;
	int probabilityDefenders = 70;
	bool prob;
	int attackingKillsCounter = 0;
	int defendingKillsCounter = 0;
	srand((unsigned int)time(NULL));

	if (validate()) {
		//if the target location is owned by the player:
		if (targetLocation->owner == player) {
			fromLocation->addArmies(-armyCount);
			targetLocation->addArmies(armyCount);
		}
		else {
			//attacking probabilities
			for (int i = 0; i < armyCount; i++) {
				prob = (rand() % 100) < probabilityAttackers;
				if (prob) {
					attackingKillsCounter++;
				}
			}
			//Defending probabilities
			for (int i = 0; i < targetLocation->numArmies; i++) {
				prob = (rand() % 100) < probabilityDefenders;
				if (prob) {
					defendingKillsCounter++;
				}
			}

			//Check for capture
			if (targetLocation->numArmies <= attackingKillsCounter) {
				player->addOwnedTerritory(targetLocation);
				target->removeOwnedTerritory(targetLocation->id);
				targetLocation->numArmies = (fromLocation->numArmies) - defendingKillsCounter;
				fromLocation->numArmies = 0;
				Deck d{};
				d.draw(player->getHand());
				player->setConqueredFlag(true); //this is to set a success flag so that the player recieves a card at the end of the turn. (only once for at leat one successful conquer)
			}
			else {
				//capture failed.
				fromLocation->addArmies(-attackingKillsCounter);
				targetLocation->addArmies(-defendingKillsCounter);
			}
		}
		notify(this);
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Advance Advance::copy(Advance order) {
	Advance copy = Advance(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************BOMB ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Bomb::Bomb(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Bomb";
}

/*
* Deconstructor
*/
Bomb::~Bomb() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;
}

/*
* Validates the order, returns true or false
*/
bool Bomb::validate() {
	cout << "\nValidating Bomb order: \"" << this->toString();
	if (targetLocation->owner == player) {
		cout << "\nFAILED: The target territory is owned by the same player issuing the bomb order.";
		return false;
	}

	vector<Territory*> currentedges;

	currentedges = fromLocation->edges;

	bool found = false;
	for (auto i : currentedges) {
		if (i == targetLocation) {
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "\nFAILED: The source territory doesn't have a connected edge with the target territory to BOMB.";
		player->getHand()->addCard(new Card(2));
		return false;
	}

	for (Player* p : player->negociatedPlayers) {
		if (p == target) {
			cout << "\nFAILED: The target player currently has a negociated contract and cannot be attacked.";
			player->getHand()->addCard(new Card(2));
			return false;
		}
	}



	cout << "\nVALIDATED.";
	return true;
}

/*
* Executes the Order returns true is successful
*/
bool Bomb::execute() {
	if (validate()) {
		targetLocation->addArmies(-(int)targetLocation->numArmies / 2);
		notify(this);
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Bomb Bomb::copy(Bomb order) {
	Bomb copy = Bomb(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************BLOCKADE ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Blockade::Blockade(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Blockade";
}

/*
* Deconstructor
*/
Blockade::~Blockade() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;
}

/*
* Validates the order, returns true or false
*/
bool Blockade::validate() {
	cout << "\nValidating Blockade order: \"" << this->toString();
	if (targetLocation->owner != player) {
		cout << "\nFAILED: The target territory is not owned by the same player issuing the blockade order.";
		player->getHand()->addCard(new Card(1));
		return false;
	}

	cout << "\nVALIDATED.";
	return true;
}

/*
* Executes the Order returns true is successful
*/
bool Blockade::execute() {
	if (validate()) {
		targetLocation->addArmies(targetLocation->numArmies);
		player->removeOwnedTerritory(targetLocation->id);
		targetLocation->changeOwner(target);
		notify(this);
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Blockade Blockade::copy(Blockade order) {
	Blockade copy = Blockade(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************AIRLIFT ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Airlift::Airlift(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Airlift";

}

/*
* Deconstructor
*/
Airlift::~Airlift() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;
}

/*
* Validates the order, returns true or false
*/
bool Airlift::validate() {
	cout << "\nValidating Airlift order: \"" << this->toString();

	//Checks if both the source and target belong to the player.
	if (targetLocation->owner != player && fromLocation->owner == player) {
		cout << "\nFAILED: The player doesn't own the target territory.\n";
		player->getHand()->addCard(new Card(0));
		return false;
	}

	//check if the player has enough army.
	if (fromLocation->numArmies < armyCount) {
		cout << "\nFAILED: The player doesn't have enough armies asked by the order in the source territory to airlift.";
		player->getHand()->addCard(new Card(0));
		return false;
	}

	cout << "\nVALIDATED.";
	return true;
}

/*
* Executes the Order returns true is successful
*/
bool Airlift::execute() {
	if (validate()) {
		fromLocation->addArmies(-armyCount);
		targetLocation->addArmies(armyCount);
		notify(this);
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Airlift Airlift::copy(Airlift order) {
	Airlift copy = Airlift(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

/****************NEGOCIATE ORDER LIST SUB CLASS****************/

/*
* Constructor
*/
Negociate::Negociate(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Negociate";
}

/*
* Deconstructor
*/
Negociate::~Negociate() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;
}

/*
* Validates the Negociate order, returns true or false
*/
bool Negociate::validate() {
	cout << "\nValidating Negociate order: \"" << this->toString();

	if (targetLocation->owner == player) {
		cout << "\nFAILED: The target territory is owned by the same player issuing the negociate order.";
		player->getHand()->addCard(new Card(3));
		return false;
	}
	cout << "\nVALIDATED.";
	return true;
}

/*
* Executes the Order returns true is successful
*/
bool Negociate::execute() {
	if (validate()) {
		player->addPlayerToNegociatedList(target);
		return true;
	}
	return false;
}

/*
* Copy function (REQUIREMENT).
*/
Negociate Negociate::copy(Negociate order) {
	Negociate copy = Negociate(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}

// Override method from Iloggable
string OrdersList::stringToLog() {
	string message = "Order Issued: " + this->getLastOrder()->getCurrentOrder() + "; ";
	return message;
}

// Override method from Iloggable
string Orders::stringToLog() {
	string message = "Order Executed: " + this->getCurrentOrder() + "; ";
	return message;
}


/****************STEAL ORDER LIST SUB CLASS****************/

Steal::Steal(Player* target, Player* player, int armyCount, Territory* targetLocation, Territory* fromLocation, int orderNumber) {
	this->target = target;
	this->player = player;
	this->armyCount = armyCount;
	this->targetLocation = targetLocation;
	this->fromLocation = fromLocation;
	this->orderNumber = orderNumber;

	currentOrder = "Steal";
}

Steal::~Steal() {
	delete target;
	target = nullptr;
	delete player;
	player = nullptr;
	delete targetLocation;
	targetLocation = nullptr;
	delete fromLocation;
	fromLocation = nullptr;;
}

bool Steal::validate() {
    return this->player->isCheater();
}

bool Steal::execute() {
    if(validate()){
        cout << "Cheater player stealing territories" << endl;
        for(Territory* territory: player->toAttack()) {
            cout << "Stole: " << territory->name << endl;
            player->addOwnedTerritory(territory);
        }
		return true;
    }
	return false;
}

Steal Steal::copy(Steal order) {
    Steal copy = Steal(this->target, this->player, this->armyCount, this->targetLocation, this->fromLocation, this->orderNumber);
	return copy;
}