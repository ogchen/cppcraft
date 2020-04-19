#include <gtest/gtest.h>

#include "imagedata.hpp"

#include <vector>

namespace engine {
namespace {

TEST(ImageData, ValidatePassesOnValidImageDataVec) {
    unsigned char textureA[] = {0, 0, 0, 0};
    unsigned char textureB[] = {1, 1, 1, 1};

    std::vector<ImageData> dataVec;
    dataVec.emplace_back(2, 2, 4, textureA);
    dataVec.emplace_back(2, 2, 4, textureB);

    EXPECT_TRUE(validateImageDataVec(dataVec, 2, 2));
}

TEST(ImageData, ValidateFailsOnNonUniformResolution) {
    unsigned char textureA[] = {0, 0, 0, 0};
    unsigned char textureB[] = {1, 1};

    std::vector<ImageData> dataVec;
    dataVec.emplace_back(2, 2, 4, textureA);
    dataVec.emplace_back(1, 1, 4, textureB);

    EXPECT_FALSE(validateImageDataVec(dataVec, 2, 2));
}

TEST(ImageData, ValidateFailsOnIncorrectNumChannels) {
    unsigned char textureA[] = {0, 0, 0, 0};
    unsigned char textureB[] = {1, 1, 1, 1};

    std::vector<ImageData> dataVec;
    dataVec.emplace_back(2, 2, 4, textureA);
    dataVec.emplace_back(2, 2, 3, textureB);

    EXPECT_FALSE(validateImageDataVec(dataVec, 2, 2));
}

}  // namespace
}  // namespace engine
