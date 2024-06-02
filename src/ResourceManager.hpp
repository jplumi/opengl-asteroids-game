#pragma once

#include <map>
#include "Shader.hpp"
#include "Texture2D.hpp"

class ResourceManager
{
public:
    static Shader LoadShader(const std::string name, const char* vertexPath, const char* fragmentPath);
    static Shader GetShader(const std::string name);
    static Texture2D LoadTexture2D(const std::string name, const char* path, bool alpha);
    static Texture2D GetTexture2D(const std::string name);
    static void Clear();
private:
    static std::map<std::string, Shader> _shaders;
    static std::map<std::string, Texture2D> _textures2D;
};