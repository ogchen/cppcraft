#include "engine/environment.hpp"
#include "engine/window.hpp"

int main() {
    if (!engine::environment::initialize()) {
        return -1;
    }
    engine::Window window(640, 480, "CppCraft");

    while (!window.shouldClose()) {
        window.renderLoop();
    }
    engine::environment::terminate();
}
