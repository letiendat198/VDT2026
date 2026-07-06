cmake_minimum_required(VERSION 3.16)

# list(APPEND CMAKE_PREFIX_PATH "~/Applications/Qt/6.11.1/gcc_64")

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/package/")

project(VDT2026 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

add_subdirectory(src)

if(CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif (CMAKE_BUILD_TYPE MATCHES "Debug")
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -fsanitize=undefined -fsanitize=address -fsanitize=memory -fsanitize=thread -fno-omit-frame-pointer -fast_unwind_on_malloc=0")
#     target_link_options(appVDT2026 BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address)
endif()