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

//     OrdersList playerOrdersList;

//     for (std::size_t i = 0; static_cast<int>(i) < 5; ++i)
//     {
//         hand.playNextCard(deck, playerOrdersList);
//     }

//     std::cout << "The deck now contains " << deck.deckSize() << " cards" << std::endl;

//     std::cout << std::endl;
// }