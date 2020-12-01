#include "Cards.h"
#include "Orders.h"

#include "Orders.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

Card::Card()
{
}

Card::~Card()
{
}

Card::Card(const Card &)
{
}

Card &Card::operator=(const Card &card)
{
    if (&card == this)
        return *this;

    return *this;
}

std::ostream &operator<<(std::ostream &out, const Card &card)
{
    return card.print(out);
}

bool Card::operator==(const Card &card) const
{
    return this->discriminant() == card.discriminant();
}

// Deck constructor initializes a deck of 30 assorted cards
Deck::Deck() : deck(new std::vector<Card *>())
{
    std::srand(time(0));

    std::cout << "Initializing the deck..." << std::endl;
    std::cout << std::endl;

    for (std::size_t i = 0; i < DECK_SIZE; i++)
    {

        int randomIndex = 1 + (rand() % 5);

        switch (randomIndex)
        {
        case 1:
            deck->push_back(new Bombcard());
            std::cout << "Added Bomb to deck" << std::endl;
            break;
        case 2:
            deck->push_back(new Reinforcementcard());
            std::cout << "Added Reinforcementcard to deck" << std::endl;
            break;
        case 3:
            deck->push_back(new Blockadecard());
            std::cout << "Added Blockade to deck" << std::endl;
            break;
        case 4:
            deck->push_back(new Airliftcard());
            std::cout << "Added Airlift to deck" << std::endl;
            break;
        case 5:
            deck->push_back(new Diplomacycard());
            std::cout << "Added Diplomacy to deck" << std::endl;
            break;
        }
    }
    std::cout << std::endl;
    std::cout << "**  Deck has been created  **" << std::endl;
    std::cout << "---------------------------------------------------------------"
              << std::endl;
}

Deck::~Deck()
{
    delete deck;
}

Deck::Deck(const Deck &deck) : deck(clone(*deck.deck))
{
}

// copy assignment operator
Deck &Deck::operator=(const Deck &deck)
{
    if (&deck == this)
        return *this;

    polymorphicDeepCopy(*this->deck, *deck.deck);

    return *this;
}

// draw method removes a card from the deck and returns it.
Card *Deck::draw()
{
    Card *cardDrawn = deck->back();
    deck->pop_back();
    std::cout << "A card has been drawn" << std::endl;

    return cardDrawn;
}

// stream insertion operator
std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    out << "Hand: ";

    for (const Card *card : *deck.deck)
    {
        out << card << ", ";
    }

    return out;
}

// backToDeck method is used to return a card to the deck once it has been played
void Deck::backToDeck(const Card *playedCard)
{
    deck->push_back(playedCard->clone());
    std::cout << "Card has been returned to deck" << std::endl;
}

// returns size of deck
int Deck::deckSize()
{
    return deck->size();
}

Hand::Hand() : hand(new std::vector<Card *>())
{
    std::cout << "**  An empty hand has been created  **" << std::endl;
}

Hand::~Hand()
{
}

Hand::Hand(const Hand &hand) : hand(clone(*hand.hand))
{
}

// stream operator
std::ostream &operator<<(std::ostream &out, const Hand &hand)
{
    out << "Hand: ";

    for (const Card *card : *hand.hand)
    {
        out << *card << ", ";
    }

    return out;
}

// copy assignment operator
Hand &Hand::operator=(const Hand &hand)
{
    if (&hand == this)
        return *this;

    polymorphicDeepCopy(*this->hand, *hand.hand);

    return *this;
}

// addToHand method takes a drawn card and adds it to the players hand
void Hand::addToHand(const Card *cardDrawn)
{
    hand->push_back(cardDrawn->clone());
    std::cout << "Card has been added to your hand" << std::endl;
}

// returns the size of the hand
int Hand::handSize()
{
    return hand->size();
}

void Hand::playNextCard(Deck &deck, OrdersList &ordersList)
{
    this->hand->back()->play(deck, ordersList);
    this->hand->pop_back();
}

std::vector<Card*> &Hand::getList()
{
    return *this->hand;
}

Order *Hand::playCard(const Card& card, Deck &deck, OrdersList &ordersList)
{
    auto it = std::find(this->hand->begin(), this->hand->end(), &card);
    if (it == this->hand->end())
    {
        return nullptr;
    }

    return (*it)->play(deck, ordersList);
}

Bombcard::Bombcard()
{
}

Bombcard::~Bombcard()
{
}

Bombcard::Bombcard(const Bombcard &bombcard) : Card(bombcard)
{
}

// Stream insertion operator
std::ostream &Bombcard::print(std::ostream &out) const
{
    out << "Bomb card";
    return out;
}

// copy assignment operator
Bombcard &Bombcard::operator=(const Bombcard &bomb)
{
    if (&bomb == this)
        return *this;

    Card::operator=(bomb);

    return *this;
}

Card *Bombcard::clone() const
{
    return new Bombcard(*this);
}

// Plays the card  and creates an order
Order *Bombcard::play(Deck &deck, OrdersList &)
{
    std::cout << "Bomb order has been created" << std::endl;
    deck.backToDeck(this); // return card to deck once played
    return new Bomb();
}

int Bombcard::discriminant() const
{
    return 0;
}

Reinforcementcard::Reinforcementcard()
{
}

Reinforcementcard::~Reinforcementcard()
{
}

Reinforcementcard::Reinforcementcard(const Reinforcementcard &reinforcementcard) :
    Card(reinforcementcard)
{
}

// stream insertion operator
std::ostream &Reinforcementcard::print(std::ostream &out) const
{
    out << "Reinforcement card";
    return out;
}

// copy assignment operator
Reinforcementcard &Reinforcementcard::operator=(const Reinforcementcard &reinforcement)
{
    if (&reinforcement == this)
        return *this;

    Card::operator=(reinforcement);

    return *this;
}

Card *Reinforcementcard::clone() const
{
    return new Reinforcementcard(*this);
}

// Plays the card  and creates an order
Order *Reinforcementcard::play(Deck &deck, OrdersList &)
{
    std::cout << "Reinforcement order has been created" << std::endl;
    deck.backToDeck(this);
    return new Reinforcement();
}

int Reinforcementcard::discriminant() const
{
    return 1;
}

Blockadecard::Blockadecard()
{
}

Blockadecard::~Blockadecard()
{
}

Blockadecard::Blockadecard(const Blockadecard &blockadecard) : Card(blockadecard)
{
}

// stream operator
std::ostream &Blockadecard::print(std::ostream &out) const
{
    out << "Blockade card";
    return out;
}

// copy assignment operator
Blockadecard &Blockadecard::operator=(const Blockadecard &blockadecard)
{
    if (&blockadecard == this)
        return *this;

    Card::operator=(blockadecard);

    return *this;
}

Card *Blockadecard::clone() const
{
    return new Blockadecard(*this);
}

// Plays the card  and creates an order
Order *Blockadecard::play(Deck &deck, OrdersList &)
{
    std::cout << "Blockade order has been created" << std::endl;
    deck.backToDeck(this);
    return new Blockade();
}

int Blockadecard::discriminant() const
{
    return 2;
}

Airliftcard::Airliftcard()
{
}

Airliftcard::~Airliftcard()
{
}

Airliftcard::Airliftcard(const Airliftcard &airliftcard) : Card(airliftcard)
{
}

// Stream operator
std::ostream &Airliftcard::print(std::ostream &out) const
{
    out << "Airlift card";

    return out;
}

// copy assignmnet operator
Airliftcard &Airliftcard::operator=(const Airliftcard &airliftcard)
{
    if (&airliftcard == this)
        return *this;

    Card::operator=(airliftcard);

    return *this;
}

Card *Airliftcard::clone() const
{
    return new Airliftcard(*this);
}

// Plays the card  and creates an order
Order *Airliftcard::play(Deck &deck, OrdersList &)
{
    std::cout << "Airlift order has been created" << std::endl;
    deck.backToDeck(this);
    return new Airlift();
}

int Airliftcard::discriminant() const
{
    return 3;
}

Diplomacycard::Diplomacycard()
{
}

Diplomacycard::~Diplomacycard()
{
}

Diplomacycard::Diplomacycard(const Diplomacycard &diplomacycard) : Card(diplomacycard)
{
}

std::ostream &Diplomacycard::print(std::ostream &out) const
{
    out << "Diplomacy card";

    return out;
}

Diplomacycard &Diplomacycard::operator=(Diplomacycard &diplomacycard)
{
    if (&diplomacycard == this)
        return *this;

    Card::operator=(diplomacycard);

    return *this;
}

Card *Diplomacycard::clone() const
{
    return new Diplomacycard(*this);
}

Order *Diplomacycard::play(Deck &deck, OrdersList &)
{
    std::cout << "Diplomacy order has been created" << std::endl;
    deck.backToDeck(this);
    return new Negotiate();
}

int Diplomacycard::discriminant() const
{
    return 4;
}