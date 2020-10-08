#include "Cards.h"
#include "Orders.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>


using namespace std;

//Deck constructor initializes a deck of 30 assorted cards
Deck::Deck(){
    
    srand (time(0));

    for(std::size_t i=0; i<decksize; i++){
        
        int randomIndex = 1 + (rand() %5); 

           switch(randomIndex){
               case 1: 
                deck.push_back(new Bombcard()); 
                cout << "Added Bomb to deck" << endl;
                break;
               case 2:  
                deck.push_back(new Reinforcementcard()); 
                cout << "Added Reinforcementcard to deck" << endl;
                break;
               case 3:  
                deck.push_back(new Blockadecard()); 
                cout << "Added Blockade to deck" << endl;
                break;
               case 4: 
                deck.push_back(new Airliftcard()); 
                cout << "Added Airlift to deck" << endl;
                break;
               case 5:
                deck.push_back(new Diplomacycard()); 
                cout << "Added Diplomacy to deck" << endl;
                break;    
           }
       }        
       cout << "**  Deck has been created  **" << endl;
    }

Deck::~Deck(){}

//draw method removes a card from the deck and returns it. 
Card* Deck::draw(){
    Card* cardDrawn = deck.back();
    deck.pop_back();
    cout << "A card has been drawn" << endl;
    
    return cardDrawn;
}

//backToDeck method is used to return a card to the deck once it has been played
void Deck::backToDeck(Card* playedCard){
    deck.push_back(playedCard);
    cout << "Card has been returned to deck" << endl;
}

int Deck::deckSize(){
    return deck.size();
}

Hand::Hand(){
    hand = {};
    cout << "**  An empty hand has been created  **" << endl;
}

Hand::~Hand(){}

//addToHand method takes a drawn card and adds it to the players hand
void Hand::addToHand(const Card* cardDrawn){
    hand.push_back(cardDrawn->clone()); 
    cout << "Card has been added to your hand" << endl;
}

int Hand::handSize(){
    return hand.size();
}

Bombcard::Bombcard(){}

Card* Bombcard::clone() const{
    return new Bombcard(*this);
}

void Bombcard::play(Deck& deck){
//create an order using orders list Bomb constructor
    Bomb bomb;
    cout << "Bomb order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this->clone());
}

Reinforcementcard::Reinforcementcard(){}

Card* Reinforcementcard::clone() const{
    return new Reinforcementcard(*this);
}

void Reinforcementcard::play(Deck& deck){
//create an order using orders list Reinforcement constructor
// Reinforcement reinforcement;
    cout << "Reinforcement order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this->clone());
}

Blockadecard::Blockadecard(){}

Card* Blockadecard::clone() const{
    return new Blockadecard(*this);
}

void Blockadecard::play(Deck& deck){
//create an order using orders list Blockade constructor
    Blockade blockade;
    cout << "Blockade order has been created" << endl;
//return card to deck once played
    deck.backToDeck(this->clone());
}

Airliftcard::Airliftcard(){}

Card* Airliftcard::clone() const{
    return new Airliftcard(*this);
}

void Airliftcard::play(Deck& deck){
//create an order using orders list Airlift constructor
    Airlift airlift;
    cout << "Airlift order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this->clone());
}

Diplomacycard::Diplomacycard(){}

Card* Diplomacycard::clone() const{
    return new Diplomacycard(*this);
}

void Diplomacycard::play(Deck& deck){
//create an order using orders list Diplomacy constructor
    
//return card to deck once played
    deck.backToDeck(this->clone());
}