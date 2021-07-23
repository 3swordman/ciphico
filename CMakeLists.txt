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