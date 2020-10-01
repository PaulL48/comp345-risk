
#ifndef CARDS_H_
#define CARDS_H_

class Card {
public:
	Card();
	void play();
};

class Spy: private Card {
	void play();
};

class Bomb: private Card{
	void play();
};

class Blockade: private Card{
	void play();
};

class Airlift: private Card{
	void play();
};

class Diplomacy: private Card{
	void play(); 
};


class Deck {
public:
	Deck();
	void draw(Hand player);

private:
	const int deckSize;
	const Card cards[]; 
};


//To be deleted
 class Hand {
}; 

#endif /* CARDS_H_ */
