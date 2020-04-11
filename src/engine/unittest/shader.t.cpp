#include "shader.hpp"
#include "window.hpp"
#include "environment.hpp"

#include <gtest/gtest.h>
#include <fstream>

namespace engine {
namespace {

TEST(Shader, ErrorThrownWithIncorrectFilePath)
{
    EXPECT_THROW(
        Shader::createShaderFromFile("bogus/file/path", GL_VERTEX_SHADER),
        std::ifstream::failure);
}

}
}
