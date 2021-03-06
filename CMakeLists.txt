cmake_minimum_required(VERSION 3.14)
project(ray_tracing)
set(CMAKE_CXX_STANDARD 17)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()
# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif ()

add_library(ray-tracing Vec3.cpp Ray.cpp RaycastHit.h Sphere.cpp Sphere.h HittableList.cpp Camera.cpp Material.cpp AABB.cpp BVHNode.cpp Metadata.h)

add_executable(render main.cpp)
target_link_libraries(render ray-tracing)

add_executable(test-vec3 test/test-vec3.cpp)
target_link_libraries(test-vec3 ray-tracing gtest_main)
add_test(NAME test-vec3 COMMAND test-vec3)

add_executable(test-sphere test/test-sphere.cpp)
target_link_libraries(test-sphere ray-tracing gtest_main)
add_test(NAME test-sphere COMMAND test-sphere)

add_executable(test-bvh test/test-bvh.cpp)
target_link_libraries(test-bvh ray-tracing gtest_main)
add_test(NAME test-bvh COMMAND test-bvh)
