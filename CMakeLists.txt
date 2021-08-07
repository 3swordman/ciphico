cmake_minimum_required(VERSION 3.0.0)
project(ciphico VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
#
add_executable(ciphico src/index.cpp)
target_link_libraries(ciphico)
#
#
#
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
cmake_policy(SET CMP0054 NEW)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
# using Clang
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -fvisibility=hidden -march=native -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-argument -Wno-ignored-optimization-argument -Wno-c++98-compat -Wno-c++98-compat-extra-semi -Wno-reserved-id-macro -Wno-covered-switch-default")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat-pedantic -Wno-global-constructors -Wno-exit-time-destructors -Wno-newline-eof -Wno-header-hygiene -Wno-missing-prototypes")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -ftree-vectorize -fdevirtualize-speculatively -fassociative-math -fno-stack-protector -funroll-loops -ffunction-sections -fdata-sections")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ffunction-sections -fdata-sections -fassociative-math -fno-stack-protector") 
endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
# using GCC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -Wextra -fvisibility=hidden -march=native -fopenmp -Wno-unknown-pragmas")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -flto -ftree-vectorize -fdevirtualize-speculatively -fno-stack-protector -funroll-loops -ffunction-sections -fdata-sections")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -ffunction-sections -fdata-sections -fassociative-math -fno-stack-protector")
endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# using Visual Studio C++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi /std:c++latest /Wall /Zc:preprocessor /Zc:__cplusplus /volatile:iso /openmp /await:strict /nologo /permissive-")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Qpar")
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O1")
endif()
endif()
message("${CMAKE_CXX_FLAGS}")
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
