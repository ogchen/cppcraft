#include "window.hpp"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <stdexcept>
#include <utility>

namespace engine {

std::atomic<bool> Window::s_activeInstance = false;

std::optional<Window> Window::createWindow(size_t width, size_t height,
                                           const std::string& title,
                                           bool hideWindow) {
    if (!s_activeInstance.exchange(true)) {
        return Window(width, height, title, hideWindow);
    }
    return std::nullopt;
}

Window::Window(size_t width, size_t height, const std::string& title,
               bool hideWindow) {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW failed to initialize.");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (hideWindow) {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    }

    d_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (d_window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(d_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("GLAD failed to initialize.");
    }

    auto resizeCallback = [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(d_window, resizeCallback);
}

Window::~Window() {
    if (d_window) {
        glfwDestroyWindow(d_window);
        glfwTerminate();
        s_activeInstance = false;
    }
}

Window::Window(Window&& window)
    : d_window(std::exchange(window.d_window, nullptr)) {}

Window& Window::operator=(Window&& window) {
    d_window = std::exchange(window.d_window, nullptr);
    return *this;
}

bool Window::shouldClose() { return glfwWindowShouldClose(d_window); }

void Window::setShouldClose(bool shouldClose) {
    glfwSetWindowShouldClose(d_window, shouldClose);
}

void Window::renderLoop() {
    if (glfwGetKey(d_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        setShouldClose(true);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(d_window);
    glfwPollEvents();
}

}  // namespace engine
