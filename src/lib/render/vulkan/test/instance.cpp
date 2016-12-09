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

  class dummy_instance : public hugh::render::vulkan::instance::base {

  public:

    using string_list_type = base::string_list_type;
    
    explicit dummy_instance(string_list_type const&    a = string_list_type(),
                            string_list_type const&    b = string_list_type(),
                            ::VkApplicationInfo const* c = nullptr)
      : base({ }, a, { }, b, c)
    {
      TRACE("<unnamed>::dummy_instance::dummy_instance");
    }
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_instance_ctor_dflt)
{
  std::unique_ptr<dummy_instance> i(new dummy_instance);
  
  BOOST_CHECK       (nullptr != i);
  BOOST_TEST_MESSAGE(*i);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_instance_ctor_user)
{
  std::unique_ptr<dummy_instance> i(new dummy_instance({ },
                                                       { VK_KHR_SURFACE_EXTENSION_NAME,
                                                         VK_KHR_DISPLAY_EXTENSION_NAME, }));
  
  BOOST_CHECK       (nullptr != i);
  BOOST_TEST_MESSAGE(*i);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_instance_visual_ctor_dflt)
{
  using namespace hugh::render::vulkan;
  
  std::unique_ptr<instance::visual> i(new instance::visual);
  
  BOOST_CHECK       (nullptr != i);
  BOOST_TEST_MESSAGE(*i);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_test_instance_visual_ctor_user)
{
  using namespace hugh::render::vulkan;
  
  std::unique_ptr<instance::visual> i(new instance::visual({ },
                                                           { VK_KHR_DISPLAY_EXTENSION_NAME, }));
  
  BOOST_CHECK       (nullptr != i);
  BOOST_TEST_MESSAGE(*i);
}
