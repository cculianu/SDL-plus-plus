cmake_minimum_required(VERSION 3.5)
project(sdlpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${sdlpp_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_gfx REQUIRED)

set(
    HEADERS
    ${sdlpp_SOURCE_DIR}/SDL++/include/SDL.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/SDL_ttf.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/audio.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/blendmode.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/error.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/events.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/image.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/mouse.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/observer.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/pixels.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/ray.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/rect.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/render.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/scancode.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/surface.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/timer.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/version.hpp
    ${sdlpp_SOURCE_DIR}/SDL++/include/video.hpp
)

set(
    SOURCES
    ${sdlpp_SOURCE_DIR}/SDL++/src/SDL_ttf.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/audio.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/blendmode.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/error.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/image.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/mouse.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/pixels.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/ray.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/rect.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/render.cpp
    ${sdlpp_SOURCE_DIR}/SDL++/src/version.cpp
)

add_library(sdlpp SHARED ${HEADERS} ${SOURCES})
target_include_directories(
    sdlpp
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_GFX_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${sdlpp_SOURCE_DIR}/SDL++/include>
)
target_link_libraries(
    sdlpp
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_GFX_LIBRARIES}
)
target_compile_definitions(sdlpp PUBLIC SDL_MAIN_HANDLED)

add_executable(Example ${sdlpp_SOURCE_DIR}/SDL++\ Example/Example.cpp)

# Enable extra warnings
target_compile_options(sdlpp PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wno-gnu-anonymous-struct -Wno-nested-anon-types>
)
target_compile_options(Example PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Wno-gnu-anonymous-struct -Wno-nested-anon-types>
)

target_include_directories(
    Example
    PUBLIC
        ${sdlpp_BINARY_DIR}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_GFX_INCLUDE_DIRS}
        $<BUILD_INTERFACE:${sdlpp_SOURCE_DIR}/SDL++/include>
)
target_link_libraries(
    Example
    sdlpp
)

install(
    TARGETS sdlpp
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY ${sdlpp_SOURCE_DIR}/SDL++/include
    DESTINATION include
)
