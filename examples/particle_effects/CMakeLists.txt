CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(particle_effects)

INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../../spn/spn.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../../spn-sdl/spn-sdl.cmake)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/particle_effects.cmake)
INCLUDE_DIRECTORIES(${spn_include} ${particle_effects_include} ${spn_sdl_include})

ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/../../spn/ spn_build)
LINK_DIRECTORIES(spn_build ${spn_sdl_lib_dirs})

ADD_EXECUTABLE(particle_effects ${particle_effects_src})
TARGET_LINK_LIBRARIES(particle_effects spn ${spn_sdl_lib})