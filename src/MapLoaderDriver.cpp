//
// Created by Ruslan Dallin on 2020-09-20.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include "MapLoader.h"

int main()
{
    for (auto& directoryEntry : std::filesystem::directory_iterator("./maps"))
    {
        std::string fileName = directoryEntry.path().string();

        
        // std::ifstream input(fileName);
        // if (input.fail())
        // {
        //     std::cout << fileName << " opening failed.\n";
        //     exit(1);
        // }

        // // Read the file into a string stream
        // std::stringstream ss;
        // std::string s;
        // while (std::getline(input,s)){
        //     ss << s << "\n";
        // }

        // std::vector<std::string> v = MapLoader::split (ss.str(), '\n');

        // //check if valid map file
        // std::cout << "Testing : " << fileName;
        // if (MapLoader::validateFile(v))
        //     std::cout << "Testing successful \nBuilding Map\n";
        // else{
        //     std::cout << "Invalid Map\n";
        //     continue;
        // }

        Map map = MapLoader::loadMap(fileName);
        std::cout << "Map file \"" << fileName << "\" status: " << map.getErrorString(map.validate()) << "\n";
        std::cout << "\n";

        // //Map::Map mapObj;

        // std::vector<Continent> vectorCont = Continent::extractContinents(v);
        // for (auto i : vectorCont) { std::cout << i << " \n";}

        // //mapObj.addContinents(mapObj, vectorCont);

        // std::vector<Territory> vectorTerr = Territory::extractTerritories(v);
        // for (auto i : vectorTerr) { std::cout << i << " \n";}

        // //mapObj.addTerritories(mapObj, vectorTerr);

        // Territory::addBorders(v);

        //mapObj.validate();

    }


    // DIR  *dirp;
    // struct dirent *directory;

    // dirp = opendir("../comp345-risk");
    // if (dirp)
    // {
    //     //look through all files in the current directory
    //     while ((directory = readdir(dirp)) != NULL)
    //     {
    //         std::string fileName = directory->d_name;
    //         //if file is a map file process it
    //         if (fileName.find(".map") != std::string::npos){

    //             std::ifstream input;
    //             input.open(fileName);
    //             if (input.fail( ))
    //             {
    //                 std::cout << fileName << " opening failed.\n";
    //                 exit(1);
    //             }

    //             std::stringstream ss;
    //             std::string s;
    //             while (std::getline(input,s) ){
    //                 ss << s << "\n";
    //             }
    //             std::vector<std::string> v = MapLoader::split (ss.str(), '\n');

    //             //check if valid map file
    //             std::cout << "\nTesting : " << fileName;
    //             if (MapLoader::validateFile(v))
    //                 std::cout << "Testing successful \nBuilding Map\n";
    //             else{
    //                 std::cout << "Invalid Map\n";
    //                 continue;
    //             }

    //             //Map::Map mapObj;

    //             std::vector<Continent> vectorCont = Continent::extractContinents(v);
    //             for (auto i : vectorCont) { std::cout << i << " \n";}

    //             //mapObj.addContinents(mapObj, vectorCont);

    //             std::vector<Territory> vectorTerr = Territory::extractTerritories(v);
    //             for (auto i : vectorTerr) { std::cout << i << " \n";}

    //             //mapObj.addTerritories(mapObj, vectorTerr);

    //             Territory::addBorders(v);

    //             //mapObj.validate();

    //         }
    //     }
    //     closedir(dirp);
    // }
    return 0;

}




