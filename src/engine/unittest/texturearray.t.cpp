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
    std::vector<std::string> relPaths = {"bogus/path", "bogus/path2"};
    EXPECT_THROW(TextureArray texture(relPaths, 16, 16), std::runtime_error);
}

TEST_F(TextureArrayTest, ErrorOnIncorrectSize) {
    std::vector<std::string> relPaths = {"block/grass_block_side.png",
                                         "block/glass.png"};
    EXPECT_NO_THROW(TextureArray textureA(relPaths, 16, 16));
    EXPECT_THROW(TextureArray textureB(relPaths, 0, 0), std::runtime_error);
}

}  // namespace
}  // namespace engine
