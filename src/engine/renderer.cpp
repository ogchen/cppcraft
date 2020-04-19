#include "renderer.hpp"

#include <glad/glad.h>

#include "shaderprogram.hpp"
#include "texturearray.hpp"
#include "vertexbuffer.hpp"

namespace engine {

Renderer::Renderer(ShaderProgram& shader, TextureArray& textures,
                   VertexBuffer& vertices)
    : d_shader(shader), d_textures(textures), d_vertices(vertices) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT);

    d_textures.bind();
    d_shader.bind();
    d_vertices.bind();

    glDrawElements(GL_TRIANGLES, d_vertices.numVertices(), GL_UNSIGNED_INT, 0);
}

}  // namespace engine
