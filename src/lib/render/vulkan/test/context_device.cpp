// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/test/context_device.cpp                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <memory> // std::unique_ptr<>

// includes, project

#include <hugh/render/vulkan/context/device.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_context_device_ctor)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<context::device> const ctx(new context::device);
  
  BOOST_CHECK(nullptr != ctx);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_context_device_print_on)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<context::device> const ctx(new context::device);
  
  BOOST_CHECK(nullptr != ctx);

  std::ostringstream ostr;

  ostr << *ctx;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
