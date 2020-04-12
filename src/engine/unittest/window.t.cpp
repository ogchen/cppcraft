#include <gtest/gtest.h>

#include <utility>

#include "window.hpp"

namespace engine {
namespace {

TEST(Window, CreateWindowSucceeds) {
    std::optional<Window> window = Window::createWindow(1, 1, "dummy", true);
    EXPECT_TRUE(window);
}

TEST(Window, OneActiveWindowLimit) {
    std::optional<Window> windowA = Window::createWindow(1, 1, "dummy", true);
    EXPECT_TRUE(windowA);
    std::optional<Window> windowB = Window::createWindow(1, 1, "dummy", true);
    EXPECT_FALSE(windowB);
}

TEST(Window, WindowDeactivatedOnDestructor) {
    {
        std::optional<Window> windowA =
            Window::createWindow(1, 1, "dummy", true);
        EXPECT_TRUE(windowA);
    }
    std::optional<Window> windowB = Window::createWindow(1, 1, "dummy", true);
    EXPECT_TRUE(windowB);
}

TEST(Window, SetShouldClose) {
    Window window =
        std::move(Window::createWindow(1, 1, "dummy", true).value());
    EXPECT_FALSE(window.shouldClose());
    window.setShouldClose(true);
    EXPECT_TRUE(window.shouldClose());
    window.setShouldClose(false);
    EXPECT_FALSE(window.shouldClose());
}

}  // namespace
}  // namespace engine
