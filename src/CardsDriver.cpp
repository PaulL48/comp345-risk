// #include "Cards.h"
// #include <iostream>

// int main()
// {

//     // Creating a deck or 30 assorted cards
//     Deck deck;

//     std::cout << std::endl;

//     // Initializing and empty hand
//     Hand hand;

//     std::cout << std::endl;
//     std::cout << "The deck contains " << deck.deckSize() << " cards" << std::endl;
//     std::cout << std::endl;
//     std::cout << "The hand contains " << hand.handSize() << " cards" << std::endl;
//     std::cout << std::endl;

//     // Drawing 5 card from the deck and adding them to the hand
//     Card *cardDrawn;

//     for (int i = 0; i < 5; i++)
//     {
//         cardDrawn = deck.draw();
//         std::cout << std::endl;
//         hand.addToHand(cardDrawn);
//         std::cout << std::endl;
//     }

//     std::cout << std::endl;
//     std::cout << "The deck now contains " << deck.deckSize() << " cards" << std::endl;
//     std::cout << std::endl;
//     std::cout << "The hand now contains " << hand.handSize() << " cards" << std::endl;
//     std::cout << std::endl;

//     // Playing a bomb card which creates an order and returns card to deck
//     Bombcard *bomb = new Bombcard();
//     bomb->play(deck);
//     std::cout << std::endl;

//     // Playing a blockade card which creates an order and returns card to deck
//     Blockadecard *blockade = new Blockadecard();
//     blockade->play(deck);
//     std::cout << std::endl;

//     // Playing an airlift card which creates an order and returns card to deck
//     Airliftcard *airlift = new Airliftcard();
//     airlift->play(deck);
//     std::cout << std::endl;

//     // Playing an reinforcement card which creates an order and returns card to deck
//     Reinforcementcard *reinforcementcard = new Reinforcementcard();
//     reinforcementcard->play(deck);
//     std::cout << std::endl;

//     // Playing an diplomacycard card which creates an order and returns card to deck
//     Diplomacycard *diplomacycard = new Diplomacycard();
//     diplomacycard->play(deck);
//     std::cout << std::endl;

//     std::cout << "The deck now contains " << deck.deckSize() << " cards" << std::endl;

//     std::cout << std::endl;
// }