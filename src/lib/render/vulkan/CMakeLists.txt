# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Vulkan)

if(NOT Vulkan_FOUND)
  return()
endif()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED)
find_package(GLM   ${GLM_MINIMUM_VERSION}   REQUIRED)
find_package(HUGH                           REQUIRED COMPONENTS render support)

include_directories(SYSTEM ${Vulkan_INCLUDE_DIR})
include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})

set(SRC)

list(APPEND SRC adapter.cpp)
list(APPEND SRC allocator.cpp)
list(APPEND SRC handle.cpp)
list(APPEND SRC instance.cpp)
list(APPEND SRC io.cpp)
list(APPEND SRC utilities.cpp)

list(APPEND SRC context/device.cpp)
list(APPEND SRC context/swap.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${HUGH_LIBRARIES})
list(APPEND LIBS ${Boost_LIBRARIES})
list(APPEND LIBS ${Vulkan_LIBRARY})

set(LIB hugh_render_vulkan)

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} INCDIR hugh/render/vulkan)
cma_setup_export(${LIB})

add_subdirectory(test EXCLUDE_FROM_ALL)
