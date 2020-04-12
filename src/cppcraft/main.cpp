#include <iostream>
#include <utility>

#include "engine/window.hpp"

int main() {
    auto optWindow = engine::Window::createWindow(640, 480, "CppCraft");

    if (!optWindow) {
        std::cerr
            << "Failed to create window, another active instance exists.\n";
        return -1;
    }
    engine::Window window = std::move(optWindow.value());

    while (!window.shouldClose()) {
        window.renderLoop();
    }
}
