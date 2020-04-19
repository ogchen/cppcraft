#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

namespace engine {

class ShaderProgram;
class TextureArray;
class VertexBuffer;

class Renderer {
   public:
    Renderer(ShaderProgram& shader, TextureArray& textures,
             VertexBuffer& vertices);

    void renderFrame();

   private:
    ShaderProgram& d_shader;
    TextureArray& d_textures;
    VertexBuffer& d_vertices;
};

}  // namespace engine

#endif
