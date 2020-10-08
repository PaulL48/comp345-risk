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
            std::string fileName = directory->d_name;
            if (fileName.find(".map") != std::string::npos){

                std::ifstream input;
                input.open(fileName);
                if (input.fail( ))
                {
                    std::cout << fileName << " opening failed.\n";
                    exit(1);
                }

                std::stringstream ss;
                std::string s;
                while (std::getline(input,s) ){
                    ss << s << "\n";
                }

                std::vector<std::string> v = split (ss.str(), '\n');

                std::cout << "\nTesting : " << fileName;
                if (validateFile(v))
                    std::cout << "Testing successful \nBuilding Map\n";

                std::vector<Continent> vectorCont = Continent::extractContinents(v);
                for (auto i : vectorCont) { std::cout << i << " \n";}

                //addContinents(vectorCont);

                std::vector<Territory> vectorTerr = Territory::extractTerritories(v);
                for (auto i : vectorTerr) { std::cout << i << " \n";}

                //addTerritories(vectorTerr);

                Territory::addBorders(v);

            }
        }
        closedir(dirp);
    }


    return 0;

}
