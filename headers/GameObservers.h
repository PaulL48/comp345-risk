#ifndef GAME_OBSERVERS_H
#define GAME_OBSERVERS_H

#include <set>
#include <vector>

constexpr int SMALL_COLUMN = 10;
constexpr int MED_COLUMN = 20;
const std::string VICTORY_BANNER =
        " .d8888b.                                              888             888          888    d8b                            \n"
        "d88P  Y88b                                             888             888          888    Y8P                            \n"
        "888    888                                             888             888          888                                   \n"
        "888         .d88b.  88888b.   .d88b.  888d888  8888b.  888888 888  888 888  8888b.  888888 888  .d88b.  88888b.  .d8888b  \n"
        "888        d88\"\"88b 888 \"88b d88P\"88b 888P\"       \"88b 888    888  888 888     \"88b 888    888 d88\"\"88b 888 \"88b 88K      \n"
        "888    888 888  888 888  888 888  888 888     .d888888 888    888  888 888 .d888888 888    888 888  888 888  888 \"Y8888b. \n"
        "Y88b  d88P Y88..88P 888  888 Y88b 888 888     888  888 Y88b.  Y88b 888 888 888  888 Y88b.  888 Y88..88P 888  888      X88 \n"
        " \"Y8888P\"   \"Y88P\"  888  888  \"Y88888 888     \"Y888888  \"Y888  \"Y88888 888 \"Y888888  \"Y888 888  \"Y88P\"  888  888  88888P' \n"
        "                                  888                                                                                     \n"
        "                             Y8b d88P                                                                                     \n"
        "                              \"Y88P\"                                                                                      ";
// used the text generator: https://www.messletters.com/en/big-text/

class Observer
{
public:
    // TODO: Fill required methods
    ~Observer();
    virtual void update() const = 0;
protected:
    Observer();
};

class Subject
{
public:
    // TODO: Fill required methods
    Subject();
    ~Subject();

    virtual void attach(Observer *o);
    virtual void detach(Observer *o);
    virtual void notify();
private:
    std::vector<Observer *> *observers;
};

class GameEngine;
class Map;


class StatisticsObserver : public Observer
{
public:
    // TODO: Fill required methods
    StatisticsObserver(GameEngine& game);

    // If active, a statistics box should always be active in the view
    virtual void update() const;
private:
    const GameEngine* game;

    void displayTopDeployed() const;

    void displayTopReinforced() const;

    // Display percentage ownership by players
    void displayPlayers() const;

    // Display a congratulatory message to the one that dominates the map
    void displayVictory() const;
};

class PhaseObserver : public Observer
{
public:
    // TODO: Fill required methods
    PhaseObserver(GameEngine& game);

    // If active, display important phase information below statistics information
    virtual void update() const;
private:
    const GameEngine* game;

    void displayReinforcementsPhase() const;
    void displayIssueOrdersPhase() const;
    void displayOrdersExecutionPhase() const;
};

#endif // GAME_OBSERVERS_H
