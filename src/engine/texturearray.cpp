#include "texturearray.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace engine {

ImageData::ImageData(const std::string& filePath) {
    stbi_set_flip_vertically_on_load(true);
    rawData = stbi_load(filePath.c_str(), &width, &height, &numChannels, 4);
    if (!rawData) {
        const std::string errorMessage =
            "Error loading texture image " + filePath;
        throw std::runtime_error(errorMessage);
    }
}

ImageData::~ImageData() {
    if (rawData) {
        stbi_image_free(rawData);
    }
}

ImageData::ImageData(ImageData&& imageData) noexcept
    : width(imageData.width),
      height(imageData.height),
      numChannels(imageData.numChannels),
      rawData(std::exchange(imageData.rawData, nullptr)) {}

ImageData& ImageData::operator=(ImageData&& imageData) {
    width = imageData.width;
    height = imageData.height;
    numChannels = imageData.numChannels;
    rawData = std::exchange(imageData.rawData, nullptr);
    return *this;
}

std::vector<ImageData> generateImageDataVec(
    const std::vector<std::string>& relPaths, size_t width, size_t height) {
    std::vector<ImageData> imageDataVec;
    imageDataVec.reserve(relPaths.size());

    auto toImageData = [](const std::string& relPath) {
        const std::string filePath = "../data/texture/" + relPath;
        return ImageData(filePath);
    };
    std::transform(relPaths.cbegin(), relPaths.cend(),
                   std::back_inserter(imageDataVec), toImageData);

    auto imageDataValid = [width, height](const ImageData& imageData) {
        return (size_t)imageData.width == width &&
               (size_t)imageData.height == height && imageData.numChannels == 4;
    };
    bool isValidVec =
        std::all_of(imageDataVec.cbegin(), imageDataVec.cend(), imageDataValid);

    if (!isValidVec) {
        throw std::runtime_error(
            "Error loading texture array. Textures must all be of equivalent "
            "size");
    }
    return imageDataVec;
}

TextureArray::TextureArray(const std::vector<std::string>& relPaths,
                           size_t width, size_t height) {
    const size_t layerCount = relPaths.size();
    std::vector<ImageData> imageDataVec =
        generateImageDataVec(relPaths, width, height);

    glGenTextures(1, &d_textureArrayObject);
    glBindTexture(GL_TEXTURE_2D_ARRAY, d_textureArrayObject);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, layerCount, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    for (size_t layer = 0; layer != imageDataVec.size(); ++layer)
    {
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
