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
    imagedata.cpp
    imagedata.hpp
    texturearray.cpp
    texturearray.hpp
    vertexdataview.cpp
    vertexdataview.hpp
    vertexbuffer.cpp
    vertexbuffer.hpp
)
add_library(engine ${ENGINE_SOURCE_FILES})

set(PRIVATE_ENGINE_DEPENDENCIES
    glfw
    OpenGL::GL
    stb_image
)

set(PUBLIC_ENGINE_DEPENDENCIES
    glad
)

target_link_libraries(engine
    PRIVATE ${PRIVATE_ENGINE_DEPENDENCIES}
    PUBLIC ${PUBLIC_ENGINE_DEPENDENCIES}
)

if(BUILD_TESTING)
    add_subdirectory(unittest)
    target_include_directories(engine_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endif()

