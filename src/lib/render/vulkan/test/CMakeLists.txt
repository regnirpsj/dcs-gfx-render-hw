# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS unit_test_framework)

include_directories(SYSTEM ${Boost_INLCUDE_DIR})

set(SRC)
list(APPEND SRC adapter.cpp)
list(APPEND SRC compile.cpp)
list(APPEND SRC context_device.cpp)
list(APPEND SRC context_swap.cpp)
list(APPEND SRC handle.cpp)
list(APPEND SRC instance.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${LIB})
list(APPEND LIBS ${Boost_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vk_layer_settings.txt ${CMAKE_BINARY_DIR} COPYONLY)

cma_setup_test(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})
