//
// Created by Ruslan Dallin on 2020-09-20.
//

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "MapLoader.h"


//============================================================================================================================================================
// CLASS DEFINITIONS: Continent
//============================================================================================================================================================

/**
 * Continent Constructor
 * @param idPar
 * @param namePar
 * @param armyValuePar
 * @param colorPar
 */
Continent::Continent(int idPar, const std::string &namePar, int armyValuePar, const std::string &colorPar){
    id = new int (idPar);
    name = new std::string (namePar);
    armyValue = new int (armyValuePar);
    color = new std::string (colorPar);
}

/**
 * Continent Copy Constructor
 * @param continent
 */
Continent::Continent(const Continent &continent){
    id = new int (*continent.id);
    name = new std::string (*continent.name);
    armyValue = new int (*continent.armyValue);
    color = new std::string (*continent.color);
}

/**
 * Contient Destructor
 */
Continent::~Continent(){
    delete this->id;
    delete this->name;
    delete this->armyValue;
    delete this->color;
}

/**
 * Overloaded Assignement Operator
 * @param rightSide
 * @return
 */
Continent &Continent::operator =(const Continent &rightSide){
    if (this == &rightSide)
        return *this;
    else{
        delete this->id;
        delete this->name;
        delete this->armyValue;
        delete this->color;

        *this->id = *rightSide.id;
        *this->name = *rightSide.name;
        *this->armyValue= *rightSide.armyValue;
        *this->color = *rightSide.color;
        return *this;
    }
}

/**
 * Overloaded string insertion operator
 * @param strm
 * @param territory
 * @return
 */
std::ostream& operator<<(std::ostream &output, const Continent &continent) {
    return output << "[ " << *continent.name << " " << *continent.armyValue << " " << *continent.color << " ]";
}

/**
 * Extracting continents from input vector
 * @param v
 * @return
 */
std::vector<Continent> Continent::extractContinents(const std::vector<std::string> &v) {
    std::cout << "\nextraction continents\n";
    std::vector<Continent> continents;
    bool flag;
    std::string first;
    std::string item;

    // the following will be used as parameters
    int id = 1;
    std::string name;
    int armyValue;
    std::string color;

    for (std::string::size_type i = 0; i < v.size(); i++){
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip
        if (v[i].at(0) == ';' || v[i].at(0) == '\r' || v[i].at(0) == '\n')
            continue;
        // if we reach the next section stop
        if (flag && first == "[countries]")
            break;
        if (flag) {
            std::stringstream cc;
            cc << v[i];
            cc >> name;
            cc >> armyValue;
            cc >> color;
            // constructing continents
            continents.push_back(Continent(id, name, armyValue, color));
            id++;
        }
        // if we reach the continents section start creating
        if (first == "[continents]")
            flag = true;
    }
    std::cout << continents.size() << " extracted\n";
    return continents;
}

/*
void Continent::addContinents(Map &mapObj, const vector<Continent> &v){
    for (std::string::size_type i = 0; i < v.size(); i++){
        mapObj.addContinent(v[i]);
    }
}*/

//============================================================================================================================================================
// CLASS DEFINITIONS: Territory
//============================================================================================================================================================


/**
 * Territory Constructor
 * @param idPar
 * @param namePar
 * @param contIdPar
 * @param xPar
 * @param yPar
 */
Territory::Territory(int idPar, const std::string &namePar, int contIdPar, int xPar, int yPar) {
    id = new int (idPar);
    name = new std::string (namePar);
    contId = new int (contIdPar);
    x = new int (xPar);
    y = new int (yPar);
}

/**
 * Territory Copy Contructor
 * @param territory
 */
Territory::Territory(const Territory &territory){
    id = new int (*territory.id);
    name = new std::string (*territory.name);
    contId = new int (*territory.contId);
    x = new int (*territory.x);
    y = new int (*territory.y);
}

/**
 * Territory Destructor
 */
Territory::~Territory(){
    delete this->id;
    delete this->name;
    delete this->contId;
    delete this->x;
    delete this->y;
}

/**
 * Territory Assignment Operator
 * @param rightSide
 * @return
 */
Territory &Territory::operator =(const Territory &rightSide){
    if (this == &rightSide)
        return *this;
    else{
        delete this->id;
        delete this->name;
        delete this->contId;
        delete this->x;
        delete this->y;

        *this->id = *rightSide.id;
        *this->name = *rightSide.name;
        *this->contId= *rightSide.contId;
        *this->x = *rightSide.x;
        *this->y = *rightSide.y;
        return *this;
    }
}

/**
 * Overloaded string insertion operator
 * @param strm
 * @param territory
 * @return
 */
std::ostream& operator<<(std::ostream &strm, const Territory &territory) {
    return strm << "[ " << *territory.id << " " << *territory.name
                << " " << *territory.contId << " " << *territory.x << " " << *territory.y  << " ]";
}

/**
 * Extracting territories from input vector
 * @param v
 * @return
 */
std::vector<Territory> Territory::extractTerritories(const std::vector<std::string> &v) {
    std::cout << "\nextraction territories\n";
    std::vector<Territory> territories;
    bool flag;
    std::string first;
    std::string item;

    // the following will be used as parameters
    int id;
    std::string name;
    int contId;
    int x;
    int y;

    for (std::string::size_type i = 0; i < v.size(); i++){
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip
        if (v[i].at(0) == ';' || v[i].at(0) == '\r' || v[i].at(0) == '\n')
            continue;
        // if we reach the next section stop
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
            // constructing territories
            territories.push_back(Territory(id, name, contId, x, y));
        }
        // if we reach the countries section start creating
        if (first == "[countries]")
            flag = true;
    }
    std::cout << territories.size() << " extracted\n";
    return territories;
}

/*
void Territory::addTerritories(Map &mapObj, const vector<Territory> &v){
    for (std::string::size_type i = 0; i < v.size(); i++){
        mapObj.addTerritory(v[i], v[i].contId);
    }
}
*/

/**
 * extracting and adding borders
 * @param v
 */
void Territory::addBorders(const std::vector<std::string> &v) {
    std::cout << "\nconnecting territories\n";
    bool flag;
    std::string first;
    std::string item;

    // the following will be used as parameters
    int id;
    int idBorder;

    for (std::string::size_type i = 0; i < v.size(); i++){
        std::stringstream line;
        line << v[i];
        line >> first;
        // if empty line or comment, skip
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
        // if we reach the borders section start adding borders
        if (first == "[borders]")
            flag = true;
    }
}


