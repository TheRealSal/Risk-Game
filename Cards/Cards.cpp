#include "Cards.h"
#include "../Orders/Orders.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// Array of names of card types 
const string cardTypes[6] = {"Airlift", "Blockade", "Bomb", "Diplomacy", "Reinforcement", "Empty"};

// Card definitions

// Default constructor
Card::Card(){
    this->cardType = NULL;
}

// copy constructor
Card::Card(const Card& card) {
    this->cardType = card.cardType;
}

// assignment operator
Card& Card::operator=(const Card& card) {
    this->cardType = card.cardType;
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Card& card) {
    out << "Card Type is " << card.cardType << endl;
    return out;
}

// Destructor
Card::~Card() {
    cardType = NULL;
}

Card::Card(int type){
    cardType = type;
}

// returns an int responding to the card type
int Card::getType(){
    if (this) {
        return cardType;
    }
    else {
        // returns the index of 5 which is "Empty"
        return 5;
    }
}

//return the name of the card by its type.
string Card::getName() {
    return cardTypes[cardType];
}

// sets the card type
void Card::setType(int newType){
    cardType = newType;
}

// plays a card from hand which removes it and returns it to the deck
void Card::play(Hand* hand, int cardNum, Deck* deck, OrdersList* orderList) {		
	// TODO: Create an order and add it to an order list
    Orders* order;
    if (this->cardType == 0){
        order = new Airlift(0,0,0,0,0,0);
        orderList->add(order);
    }
    if (this->cardType == 1){
        order = new Blockade(0,0,0,0,0,0);
        orderList->add(order);
    }
    if (this->cardType == 2){
        order = new Bomb(0,0,0,0,0,0);
        orderList->add(order);
    }
    if (this->cardType == 3){
        order = new Negociate(0,0,0,0,0,0);
        orderList->add(order);
    }
    if (this->cardType == 4){
        order = new Deploy(0,0,0,0,0,0);
        orderList->add(order);
    }
    order = NULL;
    hand->removeCardAtIndex(cardNum);	
	deck->returnCard(this);
}

// Hand definitions

// Default constructor
Hand::Hand(){
    cardAmount = 0;
}

// copy constructor
Hand::Hand(const Hand& hand) {
    for (int i = 0; i < this->cardHand.size(); i++) {
        delete cardHand[i];
        cardHand[i] = NULL;
    }
    cardHand.clear();

    for (int i =0; i < hand.cardHand.size(); i++){
        this->cardHand.push_back(hand.cardHand[i]);
    }
}

// assignment operator
Hand& Hand::operator=(const Hand& hand) {
    for (int i = 0; i < hand.cardHand.size(); i++) {
        this->cardHand.push_back(hand.cardHand[i]);
    }
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Hand& hand) {
    for (int i = 0; i < hand.cardHand.size(); i++) {
        out << "Card " << to_string(i) << " in hand is " << hand.cardHand[i] << endl;
    }
    return out;
}

// Destructor
Hand::~Hand() {
    for (int i = 0; i < this->cardHand.size(); i++) {
        delete cardHand[i];
        cardHand[i] = NULL;
    }
    cardHand.clear();
}

// delete hand
void Hand::del(){
    for (int i =0; i < this->cardHand.size(); i++){
        delete cardHand[i];
        cardHand[i] = NULL;
    }
}

// add a card to the hand (utilized in the deck draw function)
bool Hand::addCard(Card* card) {
    // checks to see if the player doesn't have a full hand of cards (max is set to 7 cards)
    if (cardAmount < MAX_AMOUNT_OF_CARDS) {
        cardHand.push_back(card);
        cardAmount += 1;
        return true;
    }
    else {
        return false;
    }
}

//checks if a card of a specific type is in the hand and returns the quantity
int Hand::contains(int type) {
    int count = 0;

    for (int i = 0; i < this->cardHand.size(); i++) {
        if (cardHand[i]->getType() == type) {
            count++;
        }
    }

    return count;
}

// remove card of the specified type from the hand
void Hand::removeCardOfType(int type) {
    for (int i = 0; i < this->cardHand.size(); i++) {
        if (cardHand[i]->getType() == type) {
            removeCardAtIndex(i);
            cardAmount -= 1;
        }
    }
}

// remove card from the hand
void Hand::removeCardAtIndex(int cardNum) {
    cardHand.erase(cardHand.begin() + cardNum);
}

// gets card the specified card in the hand
Card* Hand::getCard(int cardNum){
    return cardHand[cardNum];
}

// displays hand
void Hand::showHand(){
    for (int i = 0; i < cardHand.size(); i++) {
        cout << cardTypes[cardHand[i]->getType()] << " | ";
    }
}

// returns the amount of cards in the hand
int Hand::getNumberOfCardsInHand() {
    return cardAmount;
}

// Deck definitions

// Default constructor (deck contains 10 fo each card totalling to 50)
Deck::Deck() {
    for (int i = 0; i < 10; i++){
        cardDeck[i] = new Card(0);
    }
    for (int i = 10; i < 20; i++){
        cardDeck[i] = new Card(1);
    }
    for (int i = 20; i < 30; i++){
        cardDeck[i] = new Card(2);
    }
    for (int i = 30; i < 40; i++){
        cardDeck[i] = new Card(3);
    }
    for (int i = 40; i < 50; i++){
        cardDeck[i] = new Card(4);
    }
    // 49 because index starts at 0
    deckAmount = MAX_AMOUNT_IN_DECK;
}

// copy constructor
Deck::Deck(const Deck& deck) {
    for (int i = 0; i < MAX_AMOUNT_IN_DECK; i++){
        this->cardDeck[i] = deck.cardDeck[i];
    }
}

// assignment operator
Deck& Deck::operator=(const Deck& deck) {
    for (int i = 0; i < MAX_AMOUNT_IN_DECK; i++){
        this->cardDeck[i] = deck.cardDeck[i];
    }
    return *this;
}

// stream insertion operator
ostream& operator<<(ostream& out, const Deck& deck) {
    out << "Deck amount is " << deck.deckAmount << endl;
    return out;
}

// Destructor
Deck::~Deck() {
    for (int i = 0; i < MAX_AMOUNT_IN_DECK - 1; i++){
        delete cardDeck[i];
        cardDeck[i] = NULL;
    }
}

// Deletes the whole deck
void Deck::del() {
    for (int i = 0; i < MAX_AMOUNT_IN_DECK - 1; i++){
        delete cardDeck[i];
        cardDeck[i] = NULL;
    }
}

// Draws a random card from the deck 
void Deck::draw(Hand* hand){
    // chooses a random number within range 
    srand((unsigned)time(NULL));
    int randNum = (rand() % deckAmount-1);
    // adds the card into the hand
    hand->addCard(cardDeck[randNum]);
    // if the random number is not the last card in the deck then it swaps with the last one and deletes it
    if (randNum != deckAmount-1){
        cardDeck[randNum] = cardDeck[deckAmount-1];
        cardDeck[deckAmount-1] = NULL;
    }
    // if the random number is the last card then it deletes it
    else {
        cardDeck[randNum] = NULL;
    }
    deckAmount -= 1;
}

// Returns the card to the end of the deck and increases size
void Deck::returnCard(Card* card) {
    deckAmount += 1;
    cardDeck[deckAmount] = card;
}

// Returns the size of the deck
int Deck::getSize() {
    return deckAmount;
}