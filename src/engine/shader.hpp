#ifndef ENGINE_SHADER_HPP
#define ENGINE_SHADER_HPP

#include <glad/glad.h>

#include <string>

namespace engine {

class Shader {
   public:
    /**
     * Compiles shader code into a shader object. Throws a runtime_error if
     * compilation fails.
     *
     * @param shaderCode Shader code to compile.
     * @param shaderType Type of shader, e.g. GL_VERTEX_SHADER or
     * GL_FRAGMENT_SHADER.
     */
    Shader(const char* shaderCode, GLenum shaderType);
    ~Shader();
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& shader);
    Shader& operator=(Shader&& shader);

    /**
     * Constructs a Shader object from a file. Throws an ifstream::failure
     * exception on file read error.
     */
    static Shader createShaderFromFile(const std::string& filePath,
                                       GLenum shaderType);

    /**
     * Indicates if the current object is valid, i.e. if there is an underlying
     * shader object being actively managed.
     */
    bool isValid() const { return d_isValid; };
    GLuint shaderObject() const { return d_shaderObject; };
    GLenum shaderType() const { return d_shaderType; };

   private:
    void compileShader(const char* shaderCode);

    bool d_isValid;
    GLuint d_shaderObject;
    GLenum d_shaderType;
};

}  // namespace engine

#endif
