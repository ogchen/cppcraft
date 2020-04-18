find_package(glfw3 REQUIRED)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

set(ENGINE_SOURCE_FILES
    window.cpp
    window.hpp
    shader.cpp
    shader.hpp
    shaderprogram.cpp
    shaderprogram.hpp
    texturearray.cpp
    texturearray.hpp
    vertexdataview.hpp
    vertexdataview.cpp
)
add_library(engine ${ENGINE_SOURCE_FILES})

set(ENGINE_DEPENDENCIES
    glfw
    OpenGL::GL
    glad
    stb_image
)
target_link_libraries(engine PRIVATE ${ENGINE_DEPENDENCIES})

if(BUILD_TESTING)
    add_subdirectory(unittest)
    target_include_directories(engine_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

