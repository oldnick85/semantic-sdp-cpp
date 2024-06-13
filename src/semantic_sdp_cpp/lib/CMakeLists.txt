add_library(semantic-sdp-cpp-lib INTERFACE)
target_include_directories(semantic-sdp-cpp-lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(semantic-sdp-cpp-lib INTERFACE cxx_std_20)