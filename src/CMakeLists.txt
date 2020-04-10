add_subdirectory(cppcraft)
add_subdirectory(engine)

target_include_directories(cppcraft PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
