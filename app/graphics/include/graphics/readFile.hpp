#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glimac/FilePath.hpp>
#include <graphics/case.hpp>
#include <graphics/tile.hpp>
#include <graphics/wall.hpp>


struct Map
{
    int height;
    int width;
    std::vector<std::unique_ptr<Case>> tiles;
};

Map readMap(std::string filename, const glimac::FilePath& applicationPath);