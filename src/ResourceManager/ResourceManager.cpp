#include "ResourceManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::map<std::string, Shader> ResourceManager::_shaders;
std::map<std::string, Texture2D> ResourceManager::_textures2D;

Shader ResourceManager::LoadShader(const std::string name, const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);

    _shaders[name] = shader;

    return shader;
}

Texture2D ResourceManager::LoadTexture2D(const std::string name, const char* path, bool alpha)
{
    Texture2D texture;
    if(alpha)
    {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    texture.Generate(width, height, data);

    stbi_image_free(data);

    _textures2D[name] = texture;

    return texture;
}


Shader ResourceManager::GetShader(const std::string name)
{
    return _shaders[name];
}

Texture2D ResourceManager::GetTexture2D(const std::string name)
{
    return _textures2D[name];
}

void ResourceManager::Clear()
{
    for(auto i : _shaders)
        glDeleteProgram(i.second.ID);
    for(auto i : _textures2D)
        glDeleteTextures(1, &i.second.ID);
}
