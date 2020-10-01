#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <stdio.h>

#include "Cards.h"

using namespace std; 

class Card {
public:
	Card();
	void play();
};

class Spy: public Card {
	void play(){

    }
};

class Bomb: public Card{
	void play(){

    }
};

class Blockade: public Card{
	void play(){

    }
};

class Airlift: public Card{
	void play(){

    }
};

class Diplomacy: public Card{
	void play(){

    }
};


class Deck {
private:
    static const unsigned long deckSize = 30;
    const Card* cards[deckSize];
    int deckTracker = 0;
public:
	Deck(){
       //Initializing the deck with a random assortion of 30 cards 
       for(int i=0; i<deckSize; i++){
           srand (time(NULL));
           int randomIndex = rand() % 5 + 1; 

           switch(randomIndex){
               case 1: 
                Spy* card = new Spy(); 
                cards[i] = card; 
                break;
               case 2: 
                Bomb* card = new Bomb(); 
                cards[i] = card; 
                break;
               case 3: 
                Blockade* card = new Blockade(); 
                cards[i] = card;
                break;
               case 4: 
                Airlift* card = new Airlift(); 
                cards[i] = card;
                break;
               case 5:
                Diplomacy* card = new Diplomacy(); 
                cards[i] = card;
                break;    
           }
       }
    }

	Card draw(){
        Card cardDrawn = *cards[deckTracker];
        deckTracker += 1; 

        return cardDrawn; 
    }
};

class Hand {
private:
    static const unsigned long handSize = 15;
    const Card* cards[handSize]; 
    int handTracker = 0;
public:
    void addToHand(Card card){
        cards[handTracker] = &card;
        handTracker += 1;
    }

};