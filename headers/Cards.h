#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <ostream>

using namespace std;

class Deck; 
const std::size_t decksize = 30;

class Card{
public:
    Card();
    virtual ~Card();
    virtual Card* clone() const = 0;
    virtual void play(Deck& deck) = 0;
    Card& operator=(const Card& card);
    friend std::ostream &operator<<(std::ostream& out, const Card& card);
private:
    virtual std::ostream& print(std::ostream& out) const=0; 
};

class Bombcard : public Card{
public:
    Bombcard();
    virtual ~Bombcard()=default;
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Bombcard& operator=(const Bombcard& bomb);
private:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Reinforcementcard : public Card{
public:
    Reinforcementcard();
    virtual ~Reinforcementcard()=default;
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Reinforcementcard& operator=(const Reinforcementcard& reinforcementcard);
private:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Blockadecard : public Card{
public:
    Blockadecard();
    virtual ~Blockadecard()=default;
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Blockadecard& operator=(const Blockadecard& blockadecard);
private:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Airliftcard : public Card{
public:
    Airliftcard();
    virtual ~Airliftcard()=default;
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Airliftcard& operator=(const Airliftcard& airliftcard);
private:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Diplomacycard : public Card{
public:
    Diplomacycard();
    virtual ~Diplomacycard()=default;
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Diplomacycard& operator=(Diplomacycard& diplomacycard);
private:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Deck{ 
public:
    Deck();
    ~Deck();
    Card* draw(); 
    void backToDeck(const Card* playedCard);
    int deckSize();
    Deck& operator=(const Deck&); 
    friend std::ostream &operator<<(std::ostream& out, const Deck& deck);
private:
    vector<Card*> deck;
};

class Hand{
public:
    Hand();
    ~Hand();
    void addToHand(const Card* cardDrawn);
    int handSize();
    Hand& operator=(const Hand&); 
    friend std::ostream &operator<<(std::ostream& out, const Hand& hand);
private:
    vector<Card*> hand; 
};

template <typename T>
void polymorphicDeepCopy(std::vector<T*>& dest, const std::vector<T*>& source)
{
    // Free previous elements
    for (T* element : dest)
    {
        delete element;
    }

    dest.resize(source.size());

    // Clone polymorphic elements 
    for (std::size_t i = 0; i < dest.size(); ++i)
    {
        dest.at(i) = source.at(i)->clone();
    }
}

#endif