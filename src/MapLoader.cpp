#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "MapLoader.h"

Continent::Continent(int idPar, const std::string &namePar, int armyValuePar, const std::string &colorPar){
    id = new int (idPar);
    name = new std::string (namePar);
    armyValue = new int (armyValuePar);
    color = new std::string (colorPar);
}

Continent::Continent(const Continent &continent){
    id = new int (*continent.id);
    name = new std::string (*continent.name);
    armyValue = new int (*continent.armyValue);
    color = new std::string (*continent.color);
}

Continent::~Continent(){
    delete this->id;
    delete this->name;
    delete this->armyValue;
    delete this->color;
}

Continent &Continent::operator =(const Continent &rightSide){
    if (this == &rightSide)
        return *this;
    else{
        delete(this);
        *this->id = *rightSide.id;
        *this->name = *rightSide.name;
        *this->armyValue= *rightSide.armyValue;
        *this->color = *rightSide.color;
        return *this;
    }
}

Territory::Territory(int idPar, const std::string &namePar, int contIdPar, int xPar, int yPar) {
    id = new int (idPar);
    name = new std::string (namePar);
    contId = new int (contIdPar);
    x = new int (xPar);
    y = new int (yPar);
}

Territory::Territory(const Territory &territory){
    id = new int (*territory.id);
    name = new std::string (*territory.name);
    contId = new int (*territory.contId);
    x = new int (*territory.x);
    y = new int (*territory.y);
}

Territory::~Territory(){
    delete this->id;
    delete this->name;
    delete this->contId;
    delete this->x;
    delete this->y;
}

Territory &Territory::operator =(const Territory &rightSide){
    if (this == &rightSide)
        return *this;
    else{
        delete(this);
        *this->id = *rightSide.id;
        *this->name = *rightSide.name;
        *this->contId= *rightSide.contId;
        *this->x = *rightSide.x;
        *this->y = *rightSide.y;
        return *this;
    }
}

std::vector<Continent> Continent::extractContinents(const std::vector<std::string> &v) {
    std::cout << "\nextraction continents\n";
    std::vector<Continent> continents;
    bool flag;
    std::string first;
    std::string item;

    int id = 1;
    std::string name;
    int armyValue;
    std::string color;
    for (int i = 0; i < v.size(); i++){
        std::stringstream line;
        line << v[i];
        line >> first;
        if (v[i].at(0) == ';' || v[i].at(0) == '\r' || v[i].at(0) == '\n')
            continue;
        if (flag && first == "[countries]")
            break;
        if (flag) {
            std::stringstream cc;
            cc << v[i];
            cc >> name;
            cc >> armyValue;
            cc >> color;
            continents.push_back(Continent(id, name, armyValue, color));
            id++;
        }
        if (first == "[continents]")
            flag = true;
    }
    std::cout << continents.size() << " extracted\n";
    return continents;
}

/*
void Continent::addContinents(const vector<Continent> &v){
    for (int i = 0; i < v.size(); i++){
        Map::addContinent(v[i]);
    }
}*/

std::vector<Territory> Territory::extractTerritories(const std::vector<std::string> &v) {
    std::cout << "\nextraction territories\n";
    std::vector<Territory> territories;
    bool flag;
    std::string first;
    std::string item;

    int id;
    std::string name;
    int contId;
    int x;
    int y;
    for (int i = 0; i < v.size(); i++){
        std::stringstream line;
        line << v[i];
        line >> first;
        if (v[i].at(0) == ';' || v[i].at(0) == '\r' || v[i].at(0) == '\n')
            continue;
        if (flag && first == "[borders]")
            break;
        if (flag) {
            std::stringstream cc;
            cc << v[i];
            cc >> id;
            cc >> name;
            cc >> contId;
            cc >> x;
            cc >> y;
            territories.push_back(Territory(id, name, contId, x, y));
        }
        if (first == "[countries]")
            flag = true;
    }
    std::cout << territories.size() << " extracted\n";
    return territories;
}

/*
void Territory::addTerritories(const vector<Territory> &v){
    for (int i = 0; i < v.size(); i++){
        Map::addTerritory(v[i]);
    }
}
*/

void Territory::addBorders(const std::vector<std::string> &v, const std::vector<Territory> &vectorTerr) {
    std::cout << "\nconnecting territories\n";
    bool flag;
    std::string first;
    std::string item;

    int id;
    int idBorder;

    for (int i = 0; i < v.size(); i++){
        std::stringstream line;
        line << v[i];
        line >> first;
        if (v[i].at(0) == ';' || v[i].at(0) == '\r' || v[i].at(0) == '\n')
            continue;
        if (flag) {
            std::stringstream cc;
            cc << v[i];
            cc >> id;

            while (cc >> idBorder){
                //Map::connectTerritories(id, idBorder);
                std::cout << id << " is connected to " << idBorder << " , ";
            }
            std::cout << "\n";
        }
        if (first == "[borders]")
            flag = true;
    }
}


std::ostream& operator<<(std::ostream &output, const Continent &continent) {
    return output << "[ " << *continent.name << " " << *continent.armyValue << " " << *continent.color << " ]";
}

std::ostream& operator<<(std::ostream &strm, const Territory &territory) {
    return strm << "[ " << *territory.id << " " << *territory.name
                << " " << *territory.contId << " " << *territory.x << " " << *territory.y  << " ]";
}
