#include "Cards.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//Deck constructor initializes a deck of 30 assorted cards
Deck::Deck(){
    deckSize = 30; 

    for(int i=0; i<deckSize; i++){
        srand (time(NULL));
        int randomIndex = rand() % 4 + 1; 

           switch(randomIndex){
               case 1:  
                Bomb* card1 = new Bomb(); 
                deck.push_back(card1->clone()); 
                break;
               case 2: 
                Reinforcement* card2 = new Reinforcement(); 
                deck.push_back(card2->clone()); 
                break;
               case 3: 
                Blockade* card3 = new Blockade(); 
                deck.push_back(card3->clone()); 
                break;
               case 4: 
                Airlift* card4 = new Airlift(); 
                deck.push_back(card4->clone()); 
                break;
               case 5:
                Diplomacy* card5 = new Diplomacy(); 
                deck.push_back(card5->clone()); 
                break;    
           }
       }        
    }

Deck::~Deck(){}

//draw method removes a card from the deck and returns it. 
Card* Deck::draw(){
    Card* cardDrawn = deck.back();
    deck.pop_back();

    return cardDrawn;
}

//backToDeck method is used to return a card to the deck once it has been played
void Deck::backToDeck(Card* playedCard){
    deck.push_back(playedCard.clone());
}

Hand::Hand(){
    hand = {};
}

Hand::~Hand(){}

//addToHand method takes a drawn card and adds it to the players hand
void Hand::addToHand(const Card& cardDrawn){
    hand.push_back(cardDrawn.clone()); 
}

Bomb::Bomb(){}

Card* Bomb::clone() const{
    return new Bomb(*this);
}

void Bomb::play(Bomb bombCard, Deck deck){
//create an order using orders list Bomb constructor

//return card to deck once played
    deck.backToDeck(bombCard.clone());
}

Card* Reinforcement::clone() const{
    return new Reinforcement(*this);
}

void Reinforcement::play(Reinforcement reinforcementCard, Deck deck){
//create an order using orders list Reinforcement constructor


//return card to deck once played
    deck.backToDeck(reinforcementCard.clone());
}

Card* Blockade::clone() const{
    return new Blockade(*this);
}

void Blockade::play(Blockade blockadeCard, Deck deck){
//create an order using orders list Blockade constructor

//return card to deck once played
    deck.backToDeck(blockadeCard.clone());
}

Card* Airlift::clone() const{
    return new Airlift(*this);
}

void Airlift::play(Airlift airliftCard, Deck deck){
//create an order using orders list Airlift constructor

//return card to deck once played
    deck.backToDeck(airliftCard.clone());
}

Card* Diplomacy::clone() const{
    return new Diplomacy(*this);
}

void Diplomacy::play(Diplomacy diplomacyCard, Deck deck){
//create an order using orders list Diplomacy constructor
    
//return card to deck once played
    deck.backToDeck(diplomacyCard.clone());
}