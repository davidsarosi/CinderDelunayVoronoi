cmake_minimum_required(VERSION 3.31)
project(CinderDelunayVoronoi)

# Path to Cinder submodule
set(CINDER_PATH ${CMAKE_SOURCE_DIR}/external/Cinder)
add_subdirectory(external/Cinder)

# Include Cinder CMake modules
include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

# Use Cinder's helper macro to configure linking
ci_make_app(
        APP_NAME CinderDelunayVoronoi
        CINDER_PATH ${CINDER_PATH}
        SOURCES src/main.cpp
)






