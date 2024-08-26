#[[
 Copyright (C) 2022 The Android Open Source Project

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
#]]

cmake_minimum_required(VERSION 3.18.1)
project(hellovkjni)

# Include the GameActivity static lib to the project.
find_package(game-activity REQUIRED CONFIG)
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u \
    Java_com_google_androidgamesdk_GameActivity_initializeNativeCode")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(THIRD_PARTY_DIR ../../../../third_party)

set(TINYOBJ_PATH tinyobjloader)

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_definitions(-DVK_USE_PLATFORM_ANDROID_KHR=1)

add_library(${PROJECT_NAME} SHARED
    vk_main.cpp ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Import the CMakeLists.txt for the glm library
add_subdirectory(${THIRD_PARTY_DIR}/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${THIRD_PARTY_DIR}/glm/glm
    ${THIRD_PARTY_DIR}/stb_image
    ${PROJECT_SOURCE_DIR}/src
    ${TINYOBJ_PATH}
        )

# add lib dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
    vulkan
    game-activity::game-activity_static
    android
    glm
    log)

############## Build SHADERS #######################

# Find all vertex and fragment sources within shaders directory
# taken from VBlancos vulkan tutorial
# https://github.com/vblanco20-1/vulkan-guide/blob/all-chapters/CMakeLists.txt
find_program(GLSL_VALIDATOR glslangValidator HINTS
        ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE}
        /usr/bin
        /usr/local/bin
        ${VULKAN_SDK_PATH}/Bin
        ${VULKAN_SDK_PATH}/Bin32
        $ENV{VULKAN_SDK}/Bin/
        $ENV{VULKAN_SDK}/Bin32/
        )

# get all .vert and .frag files in shaders directory
file(GLOB_RECURSE GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/../assets/shaders/*.frag"
        "${PROJECT_SOURCE_DIR}/../assets/shaders/*.vert"
        )

foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_SOURCE_DIR}/../assets/shaders/${FILE_NAME}.spv")
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
        Shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)

add_dependencies(${PROJECT_NAME} Shaders)

#message(FATAL_ERROR "MINGW_PATH ${GLSL_SOURCE_FILES}")
