#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace engine {

Shader::Shader(const char* shaderCode, GLenum shaderType)
    : d_isValid(false), d_shaderType(shaderType) {
    compileShader(shaderCode);
}

Shader Shader::createShaderFromFile(const std::string& filePath,
                                    GLenum shaderType) {
    std::string shaderCode;
    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::failbit);

    try {
        std::stringstream stringStream;
        fileStream.open(filePath);
        stringStream << fileStream.rdbuf();
        fileStream.close();
        shaderCode = stringStream.str();
    } catch (const std::ifstream::failure&) {
        std::cerr << "Error while reading shader file " << filePath << "\n";
        throw;
    }

    return Shader(shaderCode.c_str(), shaderType);
}

Shader::~Shader() {
    if (d_isValid) {
        glDeleteShader(d_shaderObject);
    }
}

Shader::Shader(Shader&& shader)
    : d_isValid(std::exchange(shader.d_isValid, false)),
      d_shaderObject(shader.d_shaderObject),
      d_shaderType(shader.d_shaderType) {}

Shader& Shader::operator=(Shader&& shader) {
    d_isValid = std::exchange(shader.d_isValid, false);
    d_shaderObject = shader.d_shaderObject;
    d_shaderType = shader.d_shaderType;
    return *this;
}

void Shader::compileShader(const char* shaderCode) {
    d_shaderObject = glCreateShader(d_shaderType);
    d_isValid = true;
    glShaderSource(d_shaderObject, 1, &shaderCode, nullptr);
    glCompileShader(d_shaderObject);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(d_shaderObject, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(d_shaderObject, 512, nullptr, infoLog);
        std::cerr << "Error occurred during shader compilation\n";

        throw std::runtime_error(infoLog);
    }
}

}  // namespace engine
