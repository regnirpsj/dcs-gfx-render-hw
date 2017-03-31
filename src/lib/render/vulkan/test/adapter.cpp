// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/test/adapter.cpp                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/render/vulkan/adapter.hpp>
#include <hugh/render/vulkan/instance/visual.hpp>

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
#include <boost/test/output_test_stream.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_adapter_ctor_dflt)
{
  using namespace hugh::render::vulkan;

  instance::visual         i;
  std::unique_ptr<adapter> a(new adapter(i, 1));
  
  BOOST_CHECK(nullptr != a);

  boost::test_tools::output_test_stream output;

  a->print_on(output);
  
  BOOST_TEST_MESSAGE(output.str());
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_adapter_ctor_user)
{
  using namespace hugh::render::vulkan;
  using string_list_type = instance::visual::string_list_type;

  string_list_type const l;
  string_list_type const e({ VK_KHR_SURFACE_EXTENSION_NAME });
  instance::visual       i(l, e);
  
  std::unique_ptr<adapter> a(new adapter(i, 1));
  
  BOOST_CHECK(nullptr != a);

  boost::test_tools::output_test_stream output;

  a->print_on(output);
  
  BOOST_TEST_MESSAGE(output.str());
}
