cmake_minimum_required(VERSION 3.5)
project(NVD)

#set(CMAKE_CXX_STANDARD 11)

# Checking for dependencies
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)

# Set up include pathes
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories(${NVD_SOURCE_DIR}/include)
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

file(GLOB HEADER_LIST "${CMAKE_SOURCE_DIR}/include/*.hpp")
install (FILES ${HEADER_LIST} DESTINATION include)

# Set up source directories
add_subdirectory(src)

set(NVD_LIB_LOCATION "$<TARGET_FILE:${NVD}>")

configure_file(CMake/nvdConfig.cmake.in ${NVD_BINARY_DIR}/nvdConfig.cmake @ONLY)
