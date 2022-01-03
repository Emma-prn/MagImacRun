#pragma once

#include <GL/glew.h>
#include <vector>

class IBO {
private:
    GLuint m_ibo; // NOLINT

public:
    explicit IBO(const std::vector<uint32_t>& indices)
    {
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    IBO(const IBO&) = delete;
    IBO& operator=(const IBO&) = delete;

    IBO(IBO&& other)
    noexcept
        : m_ibo{other.m_ibo}
    {
        other.m_ibo = 0;
    }

    IBO& operator=(IBO&& other) noexcept
    {
        if (this != &other) {
            glDeleteBuffers(1, &m_ibo);
            m_ibo       = other.m_ibo;
            other.m_ibo = 0;
        }
        return *this;
    }

    ~IBO()
    {
        glDeleteBuffers(1, &m_ibo);
    }

    GLuint operator*() const { return m_ibo; }
};