// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/test/instance.cpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/render/vulkan/instance.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_instance_ctor_dflt)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<instance> i(new instance);
  
  BOOST_CHECK       (nullptr != i);
  BOOST_TEST_MESSAGE(*i);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_instance_ctor_user)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<instance> i(new instance({ },
                                           { VK_KHR_SURFACE_EXTENSION_NAME,
                                             VK_KHR_DISPLAY_EXTENSION_NAME, }));
  
  BOOST_CHECK       (nullptr != i);
  BOOST_TEST_MESSAGE(*i);
}
