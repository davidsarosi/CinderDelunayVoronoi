cmake_minimum_required(VERSION 3.25.1)
project(CinderDelunayVoronoi)
set( CMAKE_VERBOSE_MAKEFILE ON )
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_subdirectory(external/Cinder)
# Path to Cinder submodule
set(CINDER_PATH ${CMAKE_SOURCE_DIR}/external/Cinder)




# Include Cinder CMake modules
include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )


# Use Cinder's helper macro to configure linking
ci_make_app(
        APP_NAME CinderDelunayVoronoi
        CINDER_PATH ${CINDER_PATH}
        SOURCES src/main.cpp src/Line.cpp src/Point.cpp src/Triangle.cpp src/DelaunayTriangulator.cpp
)






