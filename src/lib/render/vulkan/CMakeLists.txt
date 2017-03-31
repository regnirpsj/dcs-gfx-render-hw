# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016-2017 University of Hull                                                       #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Vulkan)

if(NOT Vulkan_FOUND)
  return()
endif()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED)
find_package(GLM   ${GLM_MINIMUM_VERSION}   REQUIRED)
find_package(HUGH                           REQUIRED COMPONENTS field platform platform_sdl platform_xcb render support)
find_package(PkgConfig)
pkg_check_modules(SDL sdl2)
find_package(XCB                                     COMPONENTS xcb-util)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})
if(SDL_FOUND)
  include_directories(SYSTEM ${SDL_INCLUDE_DIRS})
endif()
include_directories(SYSTEM ${Vulkan_INCLUDE_DIR})
if(XCB_FOUND)
  include_directories(SYSTEM ${XCB_INCLUDE_DIRS})
endif()
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})

set(SRC)

list(APPEND SRC adapter.cpp)
list(APPEND SRC allocator.cpp)
list(APPEND SRC handle.cpp)
list(APPEND SRC io.cpp)
list(APPEND SRC queue.cpp)
list(APPEND SRC utilities.cpp)

list(APPEND SRC context/device.cpp)
list(APPEND SRC context/swap.cpp)

list(APPEND SRC instance/base.cpp)
list(APPEND SRC instance/visual.cpp)

list(APPEND SRC window/base.cpp)
if(SDL_FOUND)
  list(APPEND SRC window/sdl.cpp)
endif()
if(WIN32)
  list(APPEND SRC window/win32.cpp)
endif()
if(XCB_FOUND)
  add_definitions(${XCB_DEFINITIONS})
  list(APPEND SRC window/xcb.cpp)
endif()

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${HUGH_LIBRARIES})
list(APPEND LIBS ${Boost_LIBRARIES})
if(SDL_FOUND)
  list(APPEND LIBS ${SDL_LIBRARIES})
endif()
list(APPEND LIBS ${Vulkan_LIBRARY})
if(XCB_FOUND)
  list(APPEND LIBS ${XCB_LIBRARIES})
endif()

set(LIB hugh_render_vulkan)

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} INCDIR hugh/render/vulkan)
cma_setup_export(${LIB})

add_subdirectory(test EXCLUDE_FROM_ALL)
