#pragma once
#include <glimac/glm.hpp> 

class Case
{
    public:
        virtual void draw(glm::mat4 view, glm::mat4 proj) = 0;
        virtual glm::vec2 getPos() = 0;
        virtual ~Case() = default;
};