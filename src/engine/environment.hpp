#ifndef ENGINE_ENVIRONMENT_HPP
#define ENGINE_ENVIRONMENT_HPP

namespace engine {
namespace environment {

/**
 * Initializes GLFW and sets window hints.
 */
bool initialize();

bool isInitialized();

/**
 * Cleans up GLFW environment, closing any remaining windows.
 */
void terminate();

}  // namespace environment
}  // namespace engine

#endif
