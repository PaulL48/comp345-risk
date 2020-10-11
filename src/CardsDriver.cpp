// #include <iostream>
// #include "Cards.h"


// int main(){


//     //Creating a deck or 30 assorted cards
//     Deck deck; 

//     cout << endl;

//     //Initializing and empty hand
//     Hand hand;

//     cout << endl;

//     cout << "The deck contains " << deck.deckSize() << " cards" << endl;

//     cout << endl;

//     cout << "The hand contains " << hand.handSize() << " cards" << endl;

//     cout << endl;

//     //Drawing 5 card from the deck and adding them to the hand
//     Card* cardDrawn;

//     for(int i=0;i<5;i++){
//         cardDrawn = deck.draw();
//         cout << endl;
//         hand.addToHand(cardDrawn);
//         cout << endl;
//     }

//     cout << endl;

//     cout << "The deck now contains " << deck.deckSize() << " cards" << endl;

//     cout << endl;

//     cout << "The hand now contains " << hand.handSize() << " cards" << endl;

//     cout << endl;

//     //Playing a bomb card which creates an order and returns card to deck
//     Bombcard* bomb = new Bombcard(); 
//     bomb->play(deck);
//     cout << endl;

//     //Playing a blockade card which creates an order and returns card to deck
//     Blockadecard* blockade = new Blockadecard();
//     blockade->play(deck);
//     cout << endl;

//     //Playing an airlift card which creates an order and returns card to deck
//     Airliftcard* airlift = new Airliftcard();
//     airlift->play(deck);
//     cout << endl;

//     //Playing an reinforcement card which creates an order and returns card to deck
//     Reinforcementcard* reinforcementcard = new Reinforcementcard();
//     reinforcementcard->play(deck);
//     cout << endl;


//     //Playing an diplomacycard card which creates an order and returns card to deck
//     Diplomacycard* diplomacycard = new Diplomacycard();
//     diplomacycard->play(deck);
//     cout << endl;

//     cout << "The deck now contains " << deck.deckSize() << " cards" << endl;

//     cout << endl;
    
// }