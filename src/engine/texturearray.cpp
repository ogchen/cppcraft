#include "texturearray.hpp"

#include <stdexcept>

namespace engine {

TextureArray::TextureArray(const std::vector<std::string>& filePaths,
                           size_t width, size_t height)
    : TextureArray(generateImageDataVec(filePaths), width, height) {}

TextureArray::TextureArray(const std::vector<ImageData>& imageDataVec,
                           size_t width, size_t height) {
    if (!validateImageDataVec(imageDataVec, width, height)) {
        throw std::runtime_error(
            "Error with texture array. Textures must all be of equivalent "
            "size");
    }

    const size_t layerCount = imageDataVec.size();

    glGenTextures(1, &d_textureArrayObject);
    glBindTexture(GL_TEXTURE_2D_ARRAY, d_textureArrayObject);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, layerCount, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    for (size_t layer = 0; layer != imageDataVec.size(); ++layer) {
        const ImageData& imageData = imageDataVec[layer];
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, layer,
                        GL_RGBA, GL_UNSIGNED_BYTE, imageData.rawData);
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
}

}  // namespace engine
