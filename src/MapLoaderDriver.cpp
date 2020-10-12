//
// Created by Ruslan Dallin on 2020-09-20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include "MapLoader.h"

/**
 * Helper method. Split input into string vector
 * @param str
 * @param delimiter
 * @return
 */
std::vector<std::string> split (const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss (str);
    std::string line;

    while (getline (ss, line, delimiter))
        result.push_back (line);

    return result;
}

/**
 * Helper Method. Validate if file is valid map file
 * @param v
 * @return
 */
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
        if (v[i].length() == 0 || v[i].at(0) == ';')
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
    DIR  *dirp;
    struct dirent *directory;

    dirp = opendir("../comp345-risk");
    if (dirp)
    {
        //look through all files in the current directory
        while ((directory = readdir(dirp)) != NULL)
        {
            std::string fileName = directory->d_name;
            //if file is a map file process it
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

                //check if valid map file
                std::cout << "\nTesting : " << fileName;
                if (validateFile(v))
                    std::cout << "Testing successful \nBuilding Map\n";
                else{
                    std::cout << "Invalid Map\n";
                    continue;
                }

                //Map::Map mapObj;

                std::vector<Continent> vectorCont = Continent::extractContinents(v);
                for (auto i : vectorCont) { std::cout << i << " \n";}

                //mapObj.addContinents(mapObj, vectorCont);

                std::vector<Territory> vectorTerr = Territory::extractTerritories(v);
                for (auto i : vectorTerr) { std::cout << i << " \n";}

                //mapObj.addTerritories(mapObj, vectorTerr);

                Territory::addBorders(v);

                //mapObj.validate();

            }
        }
        closedir(dirp);
    }
    return 0;

}




