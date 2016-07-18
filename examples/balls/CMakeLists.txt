CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(balls)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../../spn/spn.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../../spn-sdl/spn-sdl.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/balls.cmake)
INCLUDE_DIRECTORIES(${spn_include} ${balls_include} ${spn_sdl_include})

ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/../../spn/ spn_build)
LINK_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/spn_build ${spn_sdl_lib_dirs})

ADD_EXECUTABLE(balls ${balls_src})
TARGET_LINK_LIBRARIES(balls spn ${spn_sdl_lib})