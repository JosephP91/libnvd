set(NVD_SOURCE
        database.cpp
        file_loader.cpp
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

target_link_libraries(nvd
        PRIVATE ${LIBMONGOCXX_LIBRARIES}
        PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS}
        PRIVATE ${LIBBSONCXX_LIBRARIES}
)

target_compile_definitions(nvd
        PRIVATE ${LIBMONGOCXX_DEFINITIONS}
)

install (TARGETS nvd LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)