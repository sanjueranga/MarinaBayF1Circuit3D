cmake_minimum_required(VERSION 3.5.0)
project(MarinaBaySim VERSION 0.1.0 LANGUAGES C CXX)

# Find and include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Find and include GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

# Add the executable
add_executable(MarinaBaySim main.cpp)

# Link the OpenGL and GLUT libraries
target_link_libraries(MarinaBaySim ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})