#include "window.hpp"

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <utility>

#include "environment.hpp"

namespace engine {

Window::Window(uint32_t width, uint32_t height, const std::string& title) {
    if (!environment::isInitialized()) {
        throw std::runtime_error(
            "GLFW environment has not been initialized. Cannot create GLFW "
            "window\n");
    }
    d_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (d_window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(d_window);

    auto resizeCallback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };

    glfwSetFramebufferSizeCallback(d_window, resizeCallback);
}

Window::~Window() { glfwDestroyWindow(d_window); }

Window::Window(Window&& window)
    : d_window(std::exchange(window.d_window, nullptr)) {}

Window& Window::operator=(Window&& window) {
    d_window = std::exchange(window.d_window, nullptr);
    return *this;
}

bool Window::shouldClose() { return glfwWindowShouldClose(d_window); }

//void Window::setShouldClose(bool shouldClose) {
//    glfwSetWindowShouldClose(d_window, shouldClose);
//}

void Window::renderLoop() {
     if (glfwGetKey(d_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(d_window, true);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(d_window);
    glfwPollEvents();
}

}  // namespace engine
