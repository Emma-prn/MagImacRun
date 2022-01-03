#pragma once

#include <GL/glew.h>
#include <vector>

template<typename VertexData>
class VBO {
private:
    GLuint m_vbo; // NOLINT

public:
    explicit VBO(const std::vector<VertexData>& vertices)
    {
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;

    VBO(VBO&& other)
    noexcept
        : m_vbo{other.m_vbo}
    {
        other.m_vbo = 0;
    }

    VBO& operator=(VBO&& other) noexcept
    {
        if (this != &other) {
            glDeleteBuffers(1, &m_vbo);
            m_vbo       = other.m_vbo;
            other.m_vbo = 0;
        }
        return *this;
    }

    ~VBO()
    {
        glDeleteBuffers(1, &m_vbo);
    }

    GLuint operator*() const { return m_vbo; }
};