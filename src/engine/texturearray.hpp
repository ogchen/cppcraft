#ifndef ENGINE_TEXTUREARRAY_HPP
#define ENGINE_TEXTUREARRAY_HPP

#include <glad/glad.h>

#include <string>
#include <vector>

#include "imagedata.hpp"

namespace engine {

class TextureArray {
   public:
    /**
     * Construct a texture array object from a list of texture files. A
     * runtime_error is thrown if any texture file does not match the
     * width/height parameters, or if a texture file fails to load.
     *
     * @param filePaths Vector of paths to textures
     * @param width Width of texture
     * @param height Height of texture
     */
    TextureArray(const std::vector<std::string>& filePaths, size_t width,
                 size_t height);

    /**
     * Construct a texture array object from a vector of image data. A
     * runtime_error is thrown if some image data does not match the
     * width/height parameters.
     *
     * @param imageDataVec Vector of image data
     * @param width Width of texture
     * @param height Height of texture
     */
    TextureArray(const std::vector<ImageData>& imageDataVec, size_t width,
                 size_t height);

    void bind();

   private:
    GLuint d_textureArrayObject;
};

}  // namespace engine

#endif
