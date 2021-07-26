cmake_minimum_required(VERSION 3.0.0)
project(ciphico VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
#
add_executable(ciphico src/index.cpp)
target_link_libraries(ciphico)
#
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
# using Clang
add_compile_options(-std=c++17 -fno-strict-alias -Wall -Wextra -fvisibility=hidden -march=native)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
add_compile_options(-O3 -fipa-pta -ftree-vectorize -fdevirtualize-speculatively -fassociative-math)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
add_compile_options(-Os)
endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
# using GCC
add_compile_options(-std=c++17 -fno-strict-alias -Wall -Wextra -fvisibility=hidden -march=native)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
add_compile_options(-O3 -fipa-pta -ftree-vectorize -fdevirtualize-speculatively -fassociative-math)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
add_compile_options(-Os)
endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# using Visual Studio C++
add_compile_options(/std:c++latest /Wall)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
add_compile_options(/O2)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
add_compile_options(/O1)
endif()
endif()
include(CPack)
include(CMakePackageConfigHelpers)
install(
    TARGETS ciphico
    EXPORT ciphicoTargets
)
write_basic_package_version_file(
    ciphico.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)