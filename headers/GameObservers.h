//
// Created by Ruslan Dallin on 2020-11-03.
//

#ifndef COMP345_RISK_GAMEOBSERVERS_H
#define COMP345_RISK_GAMEOBSERVERS_H

#include "Map.h"
#include "Observer.h"
#include <set>
//#include "GameEngine.h"

class MapObserver : public Observer {
public:
    MapObserver(Map* s);
    ~MapObserver();
    void Update();
    void displayMap();
    void displayPlayers();
    bool victory();
    std::set<std::string> getPlayerList();
private:
    Map *_subject;
    const std::string congratulations =
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

};

class PhaseObserver : public Observer {
public:
    PhaseObserver(GameEngine* s);
    ~PhaseObserver();
    void Update();
    void displayPhase();
private:
    GameEngine *_subject;
};

#endif //COMP345_RISK_GAMEOBSERVERS_H
