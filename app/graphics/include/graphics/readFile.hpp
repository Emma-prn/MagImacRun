#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <glimac/FilePath.hpp>
#include <graphics/case.hpp>
#include <graphics/tile.hpp>
#include <graphics/wall.hpp>
#include <geometry/joueur.hpp>
#include <graphics/crystal.hpp>

struct Map
{
    int height;
    int width;
    std::vector<std::unique_ptr<Case>> tiles;
    std::vector<std::unique_ptr<Crystal>> crystals;

    bool isAlive(geo::Joueur joueur);
};

float length(glm::vec2 v);
std::pair<Map, geo::Joueur> readMap(std::string filename, const glimac::FilePath& applicationPath);