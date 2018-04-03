set(NVD_SOURCE
        client.cpp
        file.cpp
        operation.cpp
        )

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_library(nvd ${NVD_SOURCE})

target_include_directories(nvd
        PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS}
)

target_compile_definitions(nvd
        PRIVATE ${LIBMONGOCXX_DEFINITIONS}
)

install (TARGETS nvd LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)