#include <fstream>
#include <sstream>
#include <iostream>
#include <graphics/readFile.hpp>
#include <glimac/glm.hpp>
#include <errno.h>
#include <stdio.h>
#include <string>
#include <cstring>

std::pair<Map, geo::Joueur> readMap(std::string filename, const glimac::FilePath& applicationPath){
    Map newMap;
    std::ifstream infile(filename);
    if(!infile.is_open()){
        std::cerr << "Erreur Reading txt" << std::endl;
    }
    std::string txtExt;
    std::getline(infile, txtExt);
    infile >> newMap.width;
    infile >> newMap.height;
    glm::vec2 positionTile = glm::vec2(0.,0.);
    const auto directionTile = glm::vec2(1.,0.);
    glm::vec2 posJoueur;
    for (std::string line; std::getline(infile, line);)
    {
        for (size_t i = 0; i < line.size(); i++)
        {
            const char c = line[i];
            const auto directionLine = glm::vec2(directionTile.y, -directionTile.x);
            switch (c)
            {
                case 'W':
                    newMap.tiles.push_back(std::make_unique<Wall>(positionTile + static_cast<float>(i) * directionLine, applicationPath)); 
                    break;
                case 'T':
                    newMap.tiles.push_back(std::make_unique<Tile>(positionTile + static_cast<float>(i) * directionLine, applicationPath));
                    break;
                case 'P':
                    posJoueur = positionTile + static_cast<float>(i) * directionLine;
                    newMap.tiles.push_back(std::make_unique<Tile>(positionTile + static_cast<float>(i) * directionLine, applicationPath));
                    break;
                case 'L':
                    newMap.tiles.push_back(std::make_unique<Tile>(positionTile + static_cast<float>(i) * directionLine, applicationPath));
                    break;
                case 'R':
                    newMap.tiles.push_back(std::make_unique<Tile>(positionTile + static_cast<float>(i) * directionLine, applicationPath));
                    break;
                case 'V':
                    break;
                default:
                    break;
            }
        }
        positionTile += directionTile;
    } 
    geo::Joueur J1(posJoueur);
    return std::make_pair(std::move(newMap),std::move(J1));
}