#include "shaderprogram.hpp"

#include <iostream>
#include <stdexcept>

#include "shader.hpp"

namespace engine {

ShaderProgram::ShaderProgram() : d_programId(glCreateProgram()) {}

ShaderProgram::ShaderProgram(const Shader& vertexShader,
                             const Shader& fragmentShader)
    : ShaderProgram() {
    if (vertexShader.shaderType() != GL_VERTEX_SHADER) {
        throw std::runtime_error(
            "Error constructing Shader program. vertexShader is not of type "
            "GL_VERTEX_SHADER");
    }
    if (fragmentShader.shaderType() != GL_FRAGMENT_SHADER) {
        throw std::runtime_error(
            "Error constructing Shader program. fragmentShader is not of type "
            "GL_FRAGMENT");
    }

    glAttachShader(d_programId, vertexShader.shaderObject());
    glAttachShader(d_programId, fragmentShader.shaderObject());
    glLinkProgram(d_programId);

    // Check for linking errors
    GLint success;
    glGetProgramiv(d_programId, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(d_programId, 512, nullptr, infoLog);
        std::cerr << "Error while linking shader program\n";
        throw std::runtime_error(infoLog);
    }
}

ShaderProgram::ShaderProgram(const std::string& vertFilePath,
                             const std::string& fragFilePath)
    : ShaderProgram(
          Shader::createShaderFromFile(vertFilePath, GL_VERTEX_SHADER),
          Shader::createShaderFromFile(fragFilePath, GL_FRAGMENT_SHADER)) {}

void ShaderProgram::bind() const { glUseProgram(d_programId); }

}  // namespace engine
