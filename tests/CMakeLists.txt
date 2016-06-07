CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(tests)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../spn/spn.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../spn-sdl/spn-sdl.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/tests.cmake)
INCLUDE_DIRECTORIES(${spn_include} ${tests_include} ${spn_sdl_include})

ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/../spn/ spn_build)
LINK_DIRECTORIES(spn_build ${spn_sdl_lib_dirs})

ADD_EXECUTABLE(tests ${tests_src})
TARGET_LINK_LIBRARIES(tests spn ${spn_sdl_lib})