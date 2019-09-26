cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

project(RT VERSION 1.0.0 LANGUAGES C)

add_executable(rt)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-modules)

set_target_properties(rt
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

if (APPLE)
    if (NOT SDL2_FOUND)
        execute_process(COMMAND ls
                COMMAND head -1
                WORKING_DIRECTORY /Users/$ENV{USER}/.brew/Cellar/sdl2/
                OUTPUT_VARIABLE SDL_VERSION)
        message("Found SDL version ${SDL_VERSION}")
        set(SDL2_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2/${SDL_VERSION})
    endif()
    if (NOT SDL2_IMAGE_FOUND)
        execute_process(COMMAND ls
                COMMAND head -1
                WORKING_DIRECTORY /Users/$ENV{USER}/.brew/Cellar/sdl2_image/
                OUTPUT_VARIABLE SDL_IMAGE_VERSION)
        message("Found SDL_image version ${SDL_IMAGE_VERSION}")
        set(SDL2_IMAGE_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_image/${SDL_IMAGE_VERSION})
    endif()
    if (NOT SDL2_TTF_FOUND)
        execute_process(COMMAND ls
                COMMAND head -1
                WORKING_DIRECTORY /Users/$ENV{USER}/.brew/Cellar/sdl2_ttf/
                OUTPUT_VARIABLE SDL_TTF_VERSION)
        message("Found SDL_image version ${SDL_TTF_VERSION}")
        set(SDL2_TTF_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_ttf/${SDL_TTF_VERSION})
    endif()
endif()

if (NOT APPLE)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
    if(NOT CMAKE_THREAD_LIBS_INIT)
        set(SDL2_THREADS_NOT_FOUND "Could NOT find Threads (Threads is required by SDL2).")
        if(SDL2_FIND_REQUIRED)
            message(FATAL_ERROR ${SDL2_THREADS_NOT_FOUND})
        endif()
    endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(OpenCL REQUIRED)

if (APPLE)
    set(GCC_COMPILE_FLAGS "-Wall -Werror -Wextra -D APPLE___")
else()
    set(GCC_COMPILE_FLAGS "-O3")
endif()
add_definitions(${GCC_COMPILE_FLAGS})

set(${PROJECT_NAME}_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${LIBFT_INCLUDE_DIRS}
        ${LIBJTOC_INCLUDE_DIRS}
        ${LIBCL_INCLUDE_DIRS}
        ${LIBUI_INCLUDE_DIRS})
message(${RT_INCLUDE_DIRS})
message(${OpenCL_INCLUDE_DIRS})

if (APPLE)
    set(CL_INCLUDE_DIRS ${OpenCL_INCLUDE_DIRS}/OpenCL)
else()
    set(CL_INCLUDE_DIRS ${OpenCL_INCLUDE_DIRS}/CL)
endif()
message(${CL_INCLUDE_DIRS})

include_directories(
        ${RT_INCLUDE_DIRS}
        ${CL_INCLUDE_DIRS}
        ${OpenCL_INCLUDE_DIRS}
)

message(${OpenCL_LIBRARY})

link_directories(${OpenCL_LIBRARY})

add_subdirectory(libft)
add_subdirectory(libjtoc)
add_subdirectory(libui)
add_subdirectory(libcl)

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