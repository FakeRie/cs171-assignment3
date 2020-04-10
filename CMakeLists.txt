cmake_minimum_required(VERSION 3.0.0)
project(ray-tracing VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

#add opengl
find_package(OpenGL)

# Add Include Path
include_directories(
	src
	head
	include
)

# find source codes
# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	src/*.c
    src/*.cpp
	src/*.cc)
if(WIN32)
add_definitions(-D_AMD64_)
endif()
message("Following files are complied " ${SOURCE_FILES})
add_executable(ray-tracing ${SOURCE_FILES})
target_link_libraries(ray-tracing ${OPENGL_glu_LIBRARY} ${OPENGL_LIBRARIES})

