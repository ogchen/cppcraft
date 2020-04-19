#include "imagedata.hpp"

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace engine {

ImageData::ImageData(const std::string& filePath) : isValid(true) {
    stbi_set_flip_vertically_on_load(true);
    rawData = stbi_load(filePath.c_str(), &width, &height, &numChannels, 4);
    if (!rawData) {
        const std::string errorMessage =
            "Error loading texture image " + filePath;
        throw std::runtime_error(errorMessage);
    }
}

ImageData::ImageData(int wd, int ht, int nc, unsigned char* data)
    : width(wd), height(ht), numChannels(nc), rawData(data), isValid(false) {}

ImageData::~ImageData() {
    if (isValid && rawData) {
        stbi_image_free(rawData);
    }
}

ImageData::ImageData(ImageData&& imageData) noexcept
    : width(imageData.width),
      height(imageData.height),
      numChannels(imageData.numChannels),
      rawData(imageData.rawData),
      isValid(std::exchange(imageData.isValid, false)) {}

ImageData& ImageData::operator=(ImageData&& imageData) {
    width = imageData.width;
    height = imageData.height;
    numChannels = imageData.numChannels;
    rawData = imageData.rawData;
    isValid = std::exchange(imageData.isValid, false);
    return *this;
}

std::vector<ImageData> generateImageDataVec(
    const std::vector<std::string>& filePaths) {
    std::vector<ImageData> imageDataVec;
    imageDataVec.reserve(filePaths.size());

    auto toImageData = [](const std::string& filePath) {
        return ImageData(filePath);
    };
    std::transform(filePaths.cbegin(), filePaths.cend(),
                   std::back_inserter(imageDataVec), toImageData);
    return imageDataVec;
}

bool validateImageDataVec(const std::vector<ImageData>& imageDataVec,
                          size_t width, size_t height) {
    auto imageDataValid = [width, height](const ImageData& imageData) {
        return (size_t)imageData.width == width &&
               (size_t)imageData.height == height && imageData.numChannels == 4;
    };
    return std::all_of(imageDataVec.cbegin(), imageDataVec.cend(),
                       imageDataValid);
}

}  // namespace engine
