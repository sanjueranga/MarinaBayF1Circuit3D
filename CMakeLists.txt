cmake_minimum_required(VERSION 3.10)
project(MarinaBaySim)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Add executable
add_executable(MarinaBaySim main.cpp)

# Link OpenGL and GLUT
target_link_libraries(MarinaBaySim 
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARIES}
    SOIL  # Add SOIL library
)

# Include directories
target_include_directories(MarinaBaySim PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)