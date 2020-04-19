#ifndef ENGINE_WINDOW_HPP
#define ENGINE_WINDOW_HPP

#include <atomic>
#include <optional>
#include <string>

class GLFWwindow;

namespace engine {
class Renderer;

class Window {
   public:
    /**
     * Attempt to create a Window object. Returns a falsey optional if an active
     * Window instance exists, i.e. if s_activeInstance is true.
     *
     * @param width Width of window in pixels
     * @param height Height of window in pixels
     * @param title Title of window
     * @param hideWindow Window is hidden on creation
     * @return An optional depending whether a window was created or not.
     */
    static std::optional<Window> createWindow(size_t width, size_t height,
                                              const std::string& title,
                                              bool hideWindow = false);
    ~Window();
    Window(Window&& window);
    Window& operator=(Window&& window);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool shouldClose();
    void setShouldClose(bool shouldClose);
    void renderLoop(Renderer& renderer);

   private:
    /**
     * Creates a window. Initializes GLFW and GLAD and makes the window the
     * current context.
     *
     * @param width Width of window in pixels
     * @param height Height of window in pixels
     * @param title Title of window
     * @param hideWindow Window is hidden on creation
     */
    Window(size_t width, size_t height, const std::string& title,
           bool hideWindow);

   private:
    GLFWwindow* d_window;

    /**
     * Static atomic boolean that indicates if a Window instance currently
     * exists.
     */
    static std::atomic<bool> s_activeInstance;
};

}  // namespace engine
#endif
