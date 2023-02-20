cmake_minimum_required(VERSION 3.0.0)
project(binaryen_sourcemap_fix VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(binaryen_sourcemap_fix main.cpp)
add_subdirectory(./thirdparty/binaryen)
target_link_libraries(binaryen_sourcemap_fix PUBLIC binaryen)
target_include_directories(binaryen_sourcemap_fix PRIVATE thirdparty/binaryen/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
