// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/test/handle.cpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/render/vulkan/handle.hpp>

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
#include <boost/test/test_case_template.hpp>
#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_LIST_SIZE 30
#include <boost/mpl/list.hpp>

using handle_types = boost::mpl::list<::VkInstance
                                       ,::VkPhysicalDevice
                                       ,::VkDevice
                                       ,::VkQueue
                                       ,::VkSemaphore
                                       ,::VkCommandBuffer
                                       ,::VkFence
                                       ,::VkDeviceMemory
                                       ,::VkBuffer
                                       ,::VkImage
                                       ,::VkEvent
                                       ,::VkQueryPool
                                       ,::VkBufferView
                                       ,::VkImageView
                                       ,::VkShaderModule
                                       ,::VkPipelineCache
                                       ,::VkPipelineLayout
                                       ,::VkRenderPass
                                       ,::VkPipeline
                                       ,::VkDescriptorSetLayout
                                       ,::VkSampler
                                       ,::VkDescriptorPool
                                       ,::VkDescriptorSet
                                       ,::VkFramebuffer
                                       ,::VkCommandPool
                                       >;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_render_vulkan_handle_ctor, T, handle_types)
{
  using namespace hugh::render::vulkan;

  handle<T> const h;
  
  BOOST_CHECK       (!h && (nullptr == *h));
  BOOST_TEST_MESSAGE(h);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_render_vulkan_handle_reset, T, handle_types)
{
  using namespace hugh::render::vulkan;

  handle<T> h1;

  BOOST_CHECK( h1 == *h1);
  BOOST_CHECK(*h1 ==  h1);
  
  handle<T> const h2;

  BOOST_CHECK( h2 == *h2);
  BOOST_CHECK(*h2 ==  h2);
  
  h1.reset(*h2);
  
  BOOST_CHECK( h1 == *h2);
  BOOST_CHECK(*h1 ==  h2);
}
