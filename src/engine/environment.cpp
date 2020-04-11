#include <GLFW/glfw3.h>

#include <iostream>

namespace engine {
namespace environment {

bool g_isInitialized = false;

bool initialize() {
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialize\n";
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    g_isInitialized = true;
    return true;
}

bool isInitialized() { return g_isInitialized; }

void terminate() { glfwTerminate(); }

}  // namespace environment
}  // namespace engine
