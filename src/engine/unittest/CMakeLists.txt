set(ENGINE_TEST_FILES
    window.t.cpp
    shader.t.cpp
    imagedata.t.cpp
    texturearray.t.cpp
    vertexdataview.t.cpp
)
add_executable(engine_test ${ENGINE_TEST_FILES})
add_test(NAME engine_test COMMAND engine_test WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(engine_test PRIVATE engine gtest_main ${ENGINE_DEPENDENCIES})
