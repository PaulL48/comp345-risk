#ifndef CARDS_H
#define CARDS_H

#include <vector>

using namespace std;

class Deck; 
const std::size_t decksize = 30;

class Card{
public:
    virtual Card* clone() const = 0;
    virtual void play(Deck& deck) = 0;

};

class Bombcard : public Card{
public:
    Bombcard();
    ~Bombcard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);

};

class Reinforcementcard : public Card{
public:
    Reinforcementcard();
    ~Reinforcementcard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);

};

class Blockadecard : public Card{
public:
    Blockadecard();
    ~Blockadecard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);

};

class Airliftcard : public Card{
public:
    Airliftcard();
    ~Airliftcard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);

};

class Diplomacycard : public Card{
public:
    Diplomacycard();
    ~Diplomacycard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);

};

class Deck{ 
public:
    Deck();
    ~Deck();
    Card* draw(); 
    void backToDeck(Card* playedCard);
    int deckSize();
private:
    vector<Card*> deck;
};

class Hand{
public:
    Hand();
    ~Hand();
    void addToHand(const Card* cardDrawn);
    int handSize();
private:
    vector<Card*> hand; 
};

#endif