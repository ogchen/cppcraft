find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

set(ENGINE_SOURCE_FILES
    environment.cpp
    window.cpp
    window.hpp
    shader.cpp
    shader.hpp
    shaderprogram.cpp
    shaderprogram.hpp
)
add_library(engine ${ENGINE_SOURCE_FILES})
target_link_libraries(engine PRIVATE glfw OpenGL::GL glad)

if(BUILD_TESTING)
    add_subdirectory(unittest)
    target_include_directories(engine_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

