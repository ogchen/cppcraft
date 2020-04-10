#ifndef ENGINE_ENVIRONMENT_HPP
#define ENGINE_ENVIRONMENT_HPP

namespace engine {
namespace environment {

// Initialize environment. Returns true on success.
bool initialize();
bool isInitialized();
void terminate();

}  // namespace environment
}  // namespace engine
#endif
