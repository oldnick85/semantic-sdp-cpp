include(ExternalProject)
ExternalProject_Add(
    gtest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         v1.14.0
    PREFIX          ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)
ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_executable(semantic-sdp-cpp-lib-unittest 
    main.cpp)

target_link_libraries(semantic-sdp-cpp-lib-unittest
    semantic-sdp-cpp-lib
    libgtest
)

target_include_directories(semantic-sdp-cpp-lib-unittest PRIVATE
    "${source_dir}/googletest/include"
)