#pragma once

#include <GL/glew.h>
#include <vector>
#include "IBO.hpp"
#include "VBO.hpp"

template<typename VertexData>
class VAO {
private:
    GLuint m_vao; // NOLINT

public:
    VAO()
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
    }

    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;

    VAO(VAO&& other)
    noexcept
        : m_vao{other.m_vao}
    {
        other.m_vao = 0;
    }

    VAO& operator=(VAO&& other) noexcept
    {
        if (this != &other) {
            glDeleteVertexArrays(1, &m_vao);
            m_vao       = other.m_vao;
            other.m_vao = 0;
        }
        return *this;
    }

    ~VAO()
    {
        glDeleteVertexArrays(1, &m_vao);
    }

    GLuint operator*() const { return m_vao; }
};