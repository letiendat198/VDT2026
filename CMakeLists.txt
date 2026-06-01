cmake_minimum_required(VERSION 3.16)

# list(APPEND CMAKE_PREFIX_PATH "~/Applications/Qt/6.11.1/gcc_64")

project(VDT2026 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

add_subdirectory(src)
add_subdirectory(src/ui)

