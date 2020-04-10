#ifndef ENGINE_WINDOW_HPP
#define ENGINE_WINDOW_HPP

#include <cstdint>
#include <string>

class GLFWwindow;

namespace engine {

class Window {
   public:
    /**
     * Creates a window, making the window context current.
     *
     * @param width Width of window in pixels
     * @param height Height of window in pixels
     * @param title Title of window
     */
    Window(uint32_t width, uint32_t height, const std::string& title);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& window);
    Window& operator=(Window&& window);

    /**
     * Determine if the window should close.
     */
    bool shouldClose();

    /**
     *
     */
    void renderLoop();

   private:
    GLFWwindow* d_window;
};

}  // namespace engine
#endif
