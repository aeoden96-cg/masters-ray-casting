cmake_minimum_required(VERSION 3.16)
project(PROJECT)
set(CMAKE_CXX_STANDARD 17)

ADD_EXECUTABLE(PROJECT
        source/main.cpp
        source/ray.cpp
        source/ray.h
        source/hittable.cpp
        source/hittable.h
        source/sphere.cpp
        source/sphere.h
        source/hittable_list.cpp
        source/hittable_list.h
        source/utils.h
        source/color.h
        source/camera.cpp
        source/camera.h
        source/utils.cpp
        source/box.cpp
        source/box.h
        source/aarect.h
        source/aarect.cpp
        )


target_link_libraries(
        PROJECT LINK_PUBLIC -lyaml-cpp
#        -lGLEW -lGL -lGLU -lglut -lpthread -lm
        )

# FIND ALL YAML FILES
file(GLOB_RECURSE YAML_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.yaml")

# copy config.yaml and input.yaml to build directory
foreach(YAML_FILE ${YAML_FILES})
        configure_file(${YAML_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()


