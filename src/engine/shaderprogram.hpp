#ifndef ENGINE_SHADERPROGRAM_HPP
#define ENGINE_SHADERPROGRAM_HPP

#include <glad/glad.h>

#include <string>

namespace engine {
class Shader;

class ShaderProgram {
   public:
    /**
     * Creates an empty shader program.
     */
    ShaderProgram();

    /**
     * Constructs a shader program from a vertex and fragment shader. Throws a
     * runtime_error if a linking error occurs.
     */
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ShaderProgram(const std::string& vertFilePath,
                  const std::string& fragFilePath);

    void use() const;

   private:
    GLuint d_programId;
};

}  // namespace engine

#endif
