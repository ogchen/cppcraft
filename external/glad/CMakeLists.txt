add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include/)
target_link_libraries(glad PRIVATE ${CMAKE_DL_LIBS})
