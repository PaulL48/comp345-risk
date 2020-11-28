#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "Map.h"
#include <string>


namespace MapLoader
{
    Map loadMapValidated(const std::string &path, bool &valid);
    void addTerritories(Map &map, const std::vector<std::string> &v);
    void addBorders(Map &map, const std::vector<std::string> &v);
    void addContinents(Map &map, const std::vector<std::string> &v);
    std::vector<std::string> readFile(std::ifstream &file);
    bool validateFile(const std::vector<std::string> &v);

} // namespace MapLoader

class FileReader{
public:
    FileReader();
    FileReader(const FileReader &other);
    FileReader &operator=(const FileReader &other);
    ~FileReader();

    Map read(const std::string &path, bool &valid){
        return MapLoader::loadMapValidated(path, valid);
    }
};

class ConquestFileReader{
public:
    ConquestFileReader();
    ConquestFileReader(const ConquestFileReader &other);
    ConquestFileReader &operator=(const ConquestFileReader &other);
    ~ConquestFileReader();

    Map read(const std::string &path, bool &valid){
        return loadMapValidated(path,valid);
    }
    Map loadMapValidated(const std::string &path, bool &valid);
    void addTerritories(Map &map, const std::vector<std::string> &v);
    void addBorders(Map &map, const std::vector<std::string> &v);
    void addContinents(Map &map, const std::vector<std::string> &v);
    std::vector<std::string> readFile(std::ifstream &file);
    bool validateFile(const std::vector<std::string> &v);
};

class ConquestFileReaderAdapter: public FileReader{
private:
    ConquestFileReader conquestFileReader;
public:
    ConquestFileReaderAdapter(ConquestFileReader reader){
        conquestFileReader = reader;
    }
    Map read(const std::string &path, bool &valid){
        return conquestFileReader.read(path, valid);
    }
};


#endif // MAPLOADER_H
