PROJECT(nbobservable)
set(CMAKE_CXX_STANDARD 11)

# Set the minimum version of cmake required to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

find_package(Boost REQUIRED)

set(EXT_LIBS
        pthread
    )

add_executable(nbobservable_app main.cpp)
target_include_directories(nbobservable_app PUBLIC include ${Boost_INCLUDE_DIRS})
target_link_libraries(nbobservable_app ${EXT_LIBS} ${Boost_LIBRARIES})
