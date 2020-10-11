#ifndef CARDS_H
#define CARDS_H

#include <vector>
#include <ostream>

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
protected:
    Card(const Card & card);
    virtual std::ostream& print(std::ostream& out) const=0; 
};

class Bombcard : public Card{
public:
    Bombcard();
    virtual ~Bombcard();
    Bombcard(const Bombcard& bomb);
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Bombcard& operator=(const Bombcard& bomb);
protected:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Reinforcementcard : public Card{
public:
    Reinforcementcard();
    Reinforcementcard(const Reinforcementcard& reinforcementcard);
    virtual ~Reinforcementcard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Reinforcementcard& operator=(const Reinforcementcard& reinforcementcard);
protected:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Blockadecard : public Card{
public:
    Blockadecard();
    virtual ~Blockadecard();
    Blockadecard(const Blockadecard& blockadecard);
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Blockadecard& operator=(const Blockadecard& blockadecard);
protected:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Airliftcard : public Card{
public:
    Airliftcard();
    virtual ~Airliftcard();
    Airliftcard(const Airliftcard& airliftcard);
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Airliftcard& operator=(const Airliftcard& airliftcard);
protected:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Diplomacycard : public Card{
public:
    Diplomacycard();
    Diplomacycard(const Diplomacycard& diplomacycard);
    virtual ~Diplomacycard();
    virtual Card* clone() const;
    virtual void play(Deck& deck);
    Diplomacycard& operator=(Diplomacycard& diplomacycard);
protected:
    virtual std::ostream& print(std::ostream& out) const; 
};

class Deck{ 
public:
    Deck();
    ~Deck();
    Deck(const Deck& deck);
    Card* draw(); 
    void backToDeck(const Card* playedCard);
    int deckSize();
    Deck& operator=(const Deck&); 
    friend std::ostream &operator<<(std::ostream& out, const Deck& deck);
protected:
    std::vector<Card*> *deck;
};

class Hand{
public:
    Hand();
    ~Hand();
    Hand(const Hand& hand);
    void addToHand(const Card* cardDrawn);
    int handSize();
    Hand& operator=(const Hand&); 
    friend std::ostream &operator<<(std::ostream& out, const Hand& hand);
protected:
    std::vector<Card*> *hand; 
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

template <typename T>
std::vector<T*> *clone(const std::vector<T*>& vector)
{
    std::vector<T*>* result = new std::vector<T*>(vector.size());
    for (std::size_t i = 0; i < result->size(); ++i)
    {
        result->at(i) = vector.at(i)->clone();
    }
    return result;
}

#endif