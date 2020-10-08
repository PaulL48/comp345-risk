//
// Created by Ruslan Dallin on 2020-10-05.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include "MapLoader.h"

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

bool validateFile (const std::vector<std::string> &v) {
    std::cout << "\nVerifing Map\n";
    bool continentsSwitch;
    bool countriesSwitch;
    bool bordersSwitch;
    std::string first;

    for (std::string::size_type i = 0; i < v.size(); i++) {
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
    return false;
}



int main( )
{

    DIR           *dirp;
    struct dirent *directory;

    dirp = opendir("../comp345-risk");
    if (dirp)
    {
        while ((directory = readdir(dirp)) != NULL)
        {
            //printf("%s\n", directory->d_name);
            std::string fileName = directory->d_name;
            if (fileName.find(".map") != std::string::npos){
                std::cout << fileName << "\n";
            }
        }
        closedir(dirp);
    }

    std::string mapMame = "brasilBadMap.map";
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

    if (validateFile(v))
        std::cout << "Map Valid";

    std::vector<Continent> vectorCont = Continent::extractContinents(v);
    for (auto i : vectorCont) { std::cout << i << " \n";}

    //addContinents(vectorCont);

    std::vector<Territory> vectorTerr = Territory::extractTerritories(v);
    for (auto i : vectorTerr) { std::cout << i << " \n";}

    //addTerritories(vectorTerr);

    Territory::addBorders(v);

    return 0;

}
