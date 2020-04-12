#include <gtest/gtest.h>

#include <fstream>
#include <utility>

#include "shader.hpp"
#include "window.hpp"

namespace engine {
namespace {

class ShaderTest : public ::testing::Test {
   protected:
    ShaderTest()
        : d_window(
              std::move(Window::createWindow(1, 1, "dummy", true).value())) {}

   private:
    Window d_window;
};

TEST_F(ShaderTest, ErrorThrownWithIncorrectFilePath) {
    EXPECT_THROW(
        Shader::createShaderFromFile("bogus/file/path", GL_VERTEX_SHADER),
        std::ifstream::failure);
}

TEST_F(ShaderTest, ErrorThrownOnCompilationError) {
    const char invalidCode[] = "invalid";
    EXPECT_THROW(Shader invalidShader(invalidCode, GL_VERTEX_SHADER),
                 std::runtime_error);
}

TEST_F(ShaderTest, NoErrorThrownOnValidCompilation) {
    const char code[] = "void main() {}";
    EXPECT_NO_THROW(Shader shader(code, GL_VERTEX_SHADER));
}

TEST_F(ShaderTest, NotValidAfterMove) {
    const char code[] = "void main() {}";

    Shader shaderA(code, GL_VERTEX_SHADER);
    EXPECT_TRUE(shaderA.isValid());

    Shader shaderB = std::move(shaderA);
    EXPECT_FALSE(shaderA.isValid());
    EXPECT_TRUE(shaderB.isValid());
}

}  // namespace
}  // namespace engine
