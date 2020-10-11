#include "Cards.h"
//#include "Orders.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>


using namespace std;

Card::Card(){}
Card::~Card(){}

//copy assignment operator
Card &Card::operator=(const Card& card){
    if(&card == this)
        return *this; 

    return *this; 
}

//stream insertion operator
std::ostream &operator<<(std::ostream& out, const Card& card){
    return card.print(out);  
}

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

//copy assignment operator
Deck& Deck::operator=(const Deck& deck){
    if(&deck == this)
        return *this;  

    polymorphicDeepCopy(this->deck, deck.deck);

    return *this; 
}

//draw method removes a card from the deck and returns it. 
Card* Deck::draw(){
    Card* cardDrawn = deck.back();
    deck.pop_back();
    cout << "A card has been drawn" << endl;
    
    return cardDrawn;
}

//stream insertion operator
std::ostream &operator<<(std::ostream& out, const Deck& deck){
    out << "Hand: "; 

    for(const Card* card : deck.deck){
        out << card << ", "; 
    }

    return out; 
}

//backToDeck method is used to return a card to the deck once it has been played
void Deck::backToDeck(const Card* playedCard){
    deck.push_back(playedCard->clone());
    cout << "Card has been returned to deck" << endl;
}

//returns size of deck
int Deck::deckSize(){
    return deck.size();
}

Hand::Hand(){
    hand = {};
    cout << "**  An empty hand has been created  **" << endl;
}

Hand::~Hand(){}

//stream operator
std::ostream &operator<<(std::ostream& out, const Hand& hand){
    out << "Hand: "; 

    for(const Card* card : hand.hand){
        out << card << ", "; 
    }

    return out; 
}

//copy assignment operator
Hand& Hand::operator=(const Hand& hand){
    if(&hand == this)
        return *this;

    polymorphicDeepCopy(this->hand, hand.hand);

    return *this;
}

//addToHand method takes a drawn card and adds it to the players hand
void Hand::addToHand(const Card* cardDrawn){
    hand.push_back(cardDrawn->clone()); 
    cout << "Card has been added to your hand" << endl;
}

//returns the size of the hand
int Hand::handSize(){
    return hand.size();
}

Bombcard::Bombcard(){}

//Stream insertion operator
std::ostream& Bombcard::print(std::ostream& out) const{
    out << "Bomb card";

    return out; 
}

//copy assignment operator
Bombcard &Bombcard::operator=(const Bombcard& bomb){
    if(&bomb == this)
        return *this;
    
    Card::operator=(bomb);

    return *this; 
}

Card* Bombcard::clone() const{
    return new Bombcard(*this);
}

//Plays the card  and creates an order
void Bombcard::play(Deck& deck){
//create an order using orders list Bomb constructor
   // Bomb bomb;
    cout << "Bomb order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this);
}

Reinforcementcard::Reinforcementcard(){}

//stream insertion operator
std::ostream& Reinforcementcard::print(std::ostream& out) const{
    out << "Reinforcement card";

    return out; 
}

//copy assignment operator
Reinforcementcard &Reinforcementcard::operator=(const Reinforcementcard& reinforcement){
    if(&reinforcement == this)
        return *this;
    
    Card::operator=(reinforcement);

    return *this; 
}

Card* Reinforcementcard::clone() const{
    return new Reinforcementcard(*this);
}

//Plays the card  and creates an order
void Reinforcementcard::play(Deck& deck){
//create an order using orders list Reinforcement constructor
   // Reinforcement reinforcement;
    cout << "Reinforcement order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this);
}

Blockadecard::Blockadecard(){}

//stream operator
std::ostream& Blockadecard::print(std::ostream& out) const{
    out << "Blockade card";

    return out; 
}

//copy assignment operator
Blockadecard &Blockadecard::operator=(const Blockadecard& blockadecard){
    if(&blockadecard == this)
        return *this;
    
    Card::operator=(blockadecard);

    return *this; 
}


Card* Blockadecard::clone() const{
    return new Blockadecard(*this);
}

//Plays the card  and creates an order
void Blockadecard::play(Deck& deck){
//create an order using orders list Blockade constructor
  //  Blockade blockade;
    cout << "Blockade order has been created" << endl;
//return card to deck once played
    deck.backToDeck(this);
}

Airliftcard::Airliftcard(){}

//Stream operator
std::ostream& Airliftcard::print(std::ostream& out) const{
    out << "Airlift card";

    return out; 
}

//copy assignmnet operator
Airliftcard &Airliftcard::operator=(const Airliftcard& airliftcard){
    if(&airliftcard == this)
        return *this;
    
    Card::operator=(airliftcard);

    return *this; 
}


Card* Airliftcard::clone() const{
    return new Airliftcard(*this);
}

//Plays the card  and creates an order
void Airliftcard::play(Deck& deck){
//create an order using orders list Airlift constructor
   // Airlift airlift;
    cout << "Airlift order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this);
}

Diplomacycard::Diplomacycard(){}

//Stream operator
std::ostream& Diplomacycard::print(std::ostream& out) const{
    out << "Diplomacy card";

    return out; 
}

//copy assignment operator
Diplomacycard &Diplomacycard::operator=(Diplomacycard& diplomacycard){
    if(&diplomacycard == this)
        return *this;
    
    Card::operator=(diplomacycard);

    return *this; 
}

Card* Diplomacycard::clone() const{
    return new Diplomacycard(*this);
}

//Plays the card  and creates an order
void Diplomacycard::play(Deck& deck){
//create an order using orders list Diplomacy constructor
  //  Diplomacy diplomacy;
    cout << "Diplomacy order has been created" << endl;

//return card to deck once played
    deck.backToDeck(this);
}