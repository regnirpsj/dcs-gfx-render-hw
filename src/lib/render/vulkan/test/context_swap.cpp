// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/test/context_swap.cpp                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <memory> // std::unique_ptr<>

// includes, project

#include <hugh/render/vulkan/context/swap.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_context_swap_ctor)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<context::device> dctx(new context::device);

  BOOST_CHECK(nullptr != dctx);
  
  std::unique_ptr<context::swap> const sctx(new context::swap(*dctx, glm::uvec2(0, 0)));
  
  BOOST_CHECK(nullptr != sctx);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_context_swap_print_on)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<context::device> dctx(new context::device);

  BOOST_CHECK(nullptr != dctx);
  
  std::unique_ptr<context::swap> const sctx(new context::swap(*dctx, glm::uvec2(0, 0)));
  
  BOOST_CHECK(nullptr != sctx);

  std::ostringstream ostr;

  ostr << *sctx;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_context_swap_size)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<context::device> dctx(new context::device);

  BOOST_CHECK(nullptr != dctx);

  glm::uvec2 const                     s1  (1, 2);
  std::unique_ptr<context::swap> const sctx(new context::swap(*dctx, s1));
  
  BOOST_CHECK(nullptr != sctx);
  BOOST_CHECK(s1 == *sctx->size);

  glm::uvec2 const s2 (3, 4);

  sctx->size = s2;

  BOOST_CHECK(s2 == *sctx->size);
}
