set(CPPCRAFT_SOURCE_FILES
    main.cpp
)

add_executable(cppcraft ${CPPCRAFT_SOURCE_FILES})
target_link_libraries(cppcraft PRIVATE engine)
