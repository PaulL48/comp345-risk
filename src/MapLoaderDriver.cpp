//
// Created by Ruslan Dallin on 2020-10-05.
//
#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

bool validate (const std::vector<std::string> &v) {
    std::cout << "\nVerifing Map\n";
    bool continentsSwitch;
    bool countriesSwitch;
    bool bordersSwitch;
    std::string first;

    for (int i = 0; i < v.size(); i++) {
        std::stringstream line;
        line << v[i];
        line >> first;
        if (v[i].at(0) == ';' || v[i].at(0) == '\r' || v[i].at(0) == '\n')
            continue;
        if (first == "[continents]")
            continentsSwitch = true;
        if (first == "[countries]")
            countriesSwitch = true;
        if (first == "[countries]")
            bordersSwitch = true;
    }
    if (continentsSwitch && countriesSwitch && bordersSwitch)
        return true;

}



int main( )
{
    std::string mapMame = "europass.map";
    std::ifstream input;
    input.open(mapMame);
    if (input.fail( ))
    {
        std::cout << "Input file opening failed.\n";
        exit(1);
    }

    std::stringstream ss;
    std::string s;
    while (std::getline(input,s) ){
        ss << s << "\n";
    }

    std::vector<std::string> v = split (ss.str(), '\n');

    std::cout << "Testing : " << mapMame;

    if (validate(v))
        std::cout << "Map Valid";

    std::vector<Continent> vectorCont = Continent::extractContinents(v);
    for (auto i : vectorCont) { std::cout << i << " \n";}

    //addContinents(vectorCont);

    std::vector<Territory> vectorTerr = Territory::extractTerritories(v);
    for (auto i : vectorTerr) { std::cout << i << " \n";}

    //addTerritories(vectorTerr);

    Territory::addBorders(v, vectorTerr);



    return 0;

}
