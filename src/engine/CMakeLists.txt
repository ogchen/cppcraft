find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

set(ENGINE_SOURCE_FILES
    environment.cpp
    window.cpp
    window.hpp
)

add_library(engine ${ENGINE_SOURCE_FILES})

target_link_libraries(engine PRIVATE glfw OpenGL::GL glad)
