CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(parallax)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../../spn/spn.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../../spn-sdl/spn-sdl.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/parallax.cmake)
INCLUDE_DIRECTORIES(${spn_include} ${parallax_include} ${spn_sdl_include})

ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/../../spn/ spn_build)
LINK_DIRECTORIES(spn_build ${spn_sdl_lib_dirs})

ADD_EXECUTABLE(parallax ${parallax_src})
TARGET_LINK_LIBRARIES(parallax spn ${spn_sdl_lib})