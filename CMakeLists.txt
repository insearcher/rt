cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

project(RT VERSION 1.0.0 LANGUAGES C)

add_executable(rt)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-modules)

set_target_properties(rt
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

if (NOT SDL2_FOUND)
    set(SDL2_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.9_1)
endif()

if (NOT SDL2_IMAGE_FOUND)
    set(SDL2_IMAGE_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.4)
endif()

if (NOT SDL2_TTF_FOUND)
    set(SDL2_TTF_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_ttf/2.0.15)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenCL REQUIRED)
set(GCC_COMPILE_FLAGS "-Wall -Werror -Wextra")
add_definitions(${GCC_COMPILE_FLAGS})

add_subdirectory(libft)
add_subdirectory(libjtoc)
add_subdirectory(libui)
add_subdirectory(libcl)

set(${PROJECT_NAME}_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${LIBFT_INCLUDE_DIRS}
        ${LIBJTOC_INCLUDE_DIRS}
        ${LIBCL_INCLUDE_DIRS}
        ${LIBUI_INCLUDE_DIRS})
message(${RT_INCLUDE_DIRS})

include_directories(
        ${RT_INCLUDE_DIRS}
        ${OpenCL_INCLUDE_DIRS}
)
link_directories(${OpenCL_LIBRARY})

target_link_libraries(rt
        ft
        jtoc
        cl
        ui
        ${OpenCL_LIBRARY}
        SDL2::Core
        SDL2::Main
        SDL2::Image
        SDL2::TTF)

add_subdirectory(src)

install(TARGETS rt DESTINATION .)