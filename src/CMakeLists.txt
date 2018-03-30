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

target_link_libraries(nvd ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBMONGOCXX_LIBRARIES} ${LIBBSONCXX_LIBRARIES})

install (TARGETS nvd LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)