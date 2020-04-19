#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "texturearray.hpp"
#include "window.hpp"

namespace engine {
namespace {

class TextureArrayTest : public ::testing::Test {
   protected:
    TextureArrayTest()
        : d_window(
              std::move(Window::createWindow(1, 1, "dummy", true).value())) {}

   private:
    Window d_window;
};

TEST_F(TextureArrayTest, ErrorOnIncorrectPaths) {
    std::vector<std::string> filePaths = {"bogus/path", "bogus/path2"};
    EXPECT_THROW(TextureArray texture(filePaths, 16, 16), std::runtime_error);
}

TEST_F(TextureArrayTest, ErrorOnIncorrectSize) {
    unsigned char texture[] = {0, 0, 0, 0};
    int width = 2;
    int height = 2;

    std::vector<ImageData> dataVec;
    dataVec.emplace_back(width, height, 4, texture);

    EXPECT_NO_THROW(TextureArray textureA(dataVec, width, height));
    EXPECT_THROW(TextureArray textureB(dataVec, 0, 0), std::runtime_error);
}

}  // namespace
}  // namespace engine
