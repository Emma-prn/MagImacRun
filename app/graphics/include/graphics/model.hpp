#pragma once
#include <assimp/postprocess.h> // Post processing flags
#include <assimp/scene.h>       // Output data structure
#include <stb_image.h>
#include <assimp/Importer.hpp> // C++ importer interface
#include <fstream>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "Mesh.hpp"

class Model {
public:
    Model(std::string path)
    {
        loadModel(path);
    }
    void Draw(glimac::Program& program);

private:
    std::vector<Mesh>        m_meshes;
    std::string              m_directory;
    std::vector<TextureMesh> m_texturesLoaded;

    void                     loadModel(std::string path);
    void                     processNode(aiNode* node, const aiScene* scene);
    Mesh                     processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<TextureMesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};