#ifndef CARDS_H
#define CARDS_H

#include <ostream>
#include <vector>

#include "Orders.h"

const std::size_t DECK_SIZE = 30;

class Deck;
class OrdersList;
class Order;

class Card
{
public:
    Card();
    virtual ~Card();
    virtual Card *clone() const = 0;
    virtual Order *play(Deck &deck, OrdersList &ordersList) = 0;
    Card &operator=(const Card &card);
    bool operator==(const Card &card) const;
    friend std::ostream &operator<<(std::ostream &out, const Card &card);
    virtual int discriminant() const = 0;
protected:
    Card(const Card &card);
    virtual std::ostream &print(std::ostream &out) const = 0;
    
};

class Bombcard : public Card
{
public:
    Bombcard();
    virtual ~Bombcard();
    Bombcard(const Bombcard &bomb);
    virtual Card *clone() const;
    virtual Order *play(Deck &deck, OrdersList &ordersList);
    Bombcard &operator=(const Bombcard &bomb);
    virtual int discriminant() const;
protected:
    virtual std::ostream &print(std::ostream &out) const;
    
};

class Reinforcementcard : public Card
{
public:
    Reinforcementcard();
    Reinforcementcard(const Reinforcementcard &reinforcementcard);
    virtual ~Reinforcementcard();
    virtual Card *clone() const;
    virtual Order *play(Deck &deck, OrdersList &ordersList);
    Reinforcementcard &operator=(const Reinforcementcard &reinforcementcard);
    virtual int discriminant() const;
protected:
    virtual std::ostream &print(std::ostream &out) const;
};

class Blockadecard : public Card
{
public:
    Blockadecard();
    virtual ~Blockadecard();
    Blockadecard(const Blockadecard &blockadecard);
    virtual Card *clone() const;
    virtual Order *play(Deck &deck, OrdersList &ordersList);
    Blockadecard &operator=(const Blockadecard &blockadecard);
    virtual int discriminant() const;
protected:
    virtual std::ostream &print(std::ostream &out) const;
};

class Airliftcard : public Card
{
public:
    Airliftcard();
    virtual ~Airliftcard();
    Airliftcard(const Airliftcard &airliftcard);
    virtual Card *clone() const;
    virtual Order *play(Deck &deck, OrdersList &ordersList);
    Airliftcard &operator=(const Airliftcard &airliftcard);
    virtual int discriminant() const;
protected:
    virtual std::ostream &print(std::ostream &out) const;
};

class Diplomacycard : public Card
{
public:
    Diplomacycard();
    Diplomacycard(const Diplomacycard &diplomacycard);
    virtual ~Diplomacycard();
    virtual Card *clone() const;
    virtual Order *play(Deck &deck, OrdersList &ordersList);
    Diplomacycard &operator=(Diplomacycard &diplomacycard);
    virtual int discriminant() const;
protected:
    virtual std::ostream &print(std::ostream &out) const;
};

class Deck
{
public:
    Deck();
    ~Deck();
    Deck(const Deck &deck);
    Card *draw();
    void backToDeck(const Card *playedCard);
    int deckSize();
    Deck &operator=(const Deck &);
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

protected:
    std::vector<Card *> *deck;
};

class Hand
{
public:
    Hand();
    ~Hand();
    Hand(const Hand &hand);
    void playNextCard(Deck &deck, OrdersList &ordersList);
    void addToHand(const Card *cardDrawn);
    int handSize();
    Hand &operator=(const Hand &);
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);
    std::vector<Card*> &getList();
    Order *playCard(const Card& card, Deck &deck, OrdersList &ordersList);
protected:
    std::vector<Card *> *hand;
};

#endif