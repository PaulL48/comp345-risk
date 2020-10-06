#ifndef CARDS_H
#define CARDS_H

#include <vector>

using namespace std;

class Card{
public:
    virtual Card* clone() const;
    virtual void play();
private:
    Card *cardPlayed;
};

class Bomb : public Card{
public:
    Bomb();
    ~Bomb();
    virtual Card* clone() const;
    virtual void play(Bomb bombCard, Deck deck);
private:
    Bomb *cardPlayed;
};

class Reinforcement : public Card{
public:
    Reinforcement();
    ~Reinforcement();
    virtual Card* clone() const;
    virtual void play(Reinforcement reinforcementCard, Deck deck);
private:
    Reinforcement *cardPlayed;
};

class Blockade : public Card{
public:
    Blockade();
    ~Blockade();
    virtual Card* clone() const;
    virtual void play(Blockade blockadeCard, Deck deck);
private:
    Blockade *cardPlayed;
};

class Airlift : public Card{
public:
    Airlift();
    ~Airlift();
    virtual Card* clone() const;
    virtual void play(Airlift airliftCard, Deck deck);
private:
    Airlift *cardPlayed;
};

class Diplomacy : public Card{
public:
    Diplomacy();
    ~Diplomacy();
    virtual Card* clone() const;
    virtual void play(Diplomacy diplomacyCard, Deck deck);
private:
    Diplomacy *cardPlayed;
};

class Deck{ 
public:
    Deck();
    ~Deck();
    Card* draw(); 
    void backToDeck(Card* playedCard);

private:
    static unsigned long deckSize;
    vector<Card*> deck;
};

class Hand{
    Hand();
    ~Hand();
    void addToHand(const Card& cardDrawn);

private:
    vector<Card> hand; 
};

#endif