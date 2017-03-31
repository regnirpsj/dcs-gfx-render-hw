// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/test/window_xcb.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <memory> // std::unique_ptr<>

// includes, project

#include <hugh/render/vulkan/window/xcb.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  class window : public hugh::render::vulkan::window::xcb {

  public:

    using inherited  = hugh::render::vulkan::window::xcb;
    using rect       = inherited::rect;
    using duration   = hugh::support::clock::duration;
    using time_point = hugh::support::clock::time_point;
    
    explicit window(std::string const& a,
                    duration const&    b = std::chrono::seconds(1),
                    rect const&        c = rect::dflt_rect,
                    std::string const& d = std::string())
      : inherited(a, c, d),
        duration_(b),
        start_   (hugh::support::clock::now())
    {
      TRACE("<unnamed>::window::window");
    }

    virtual void display()
    {
      TRACE("<unnamed>::window::display");
      
      while (duration_ > (hugh::support::clock::now() - start_)) {
        inherited::display();

        render(1);
        
        hugh::support::sleep(std::chrono::milliseconds(250));
      }
    }

  private:

    duration const   duration_;
    time_point const start_;
    
  };

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_window_xcb_ctor)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<window::xcb> w(new window::xcb("test_hugh_render_vulkan_window_xcb_ctor"));
  
  BOOST_CHECK       (nullptr != w);
  // BOOST_TEST_MESSAGE(*w);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_window_xcb_size)
{
  using namespace hugh::render::vulkan;

  std::unique_ptr<window::xcb> w(new window::xcb("test_hugh_render_vulkan_window_xcb_size",
                                                 { 0, 0, 800, 600 }));
  
  BOOST_CHECK       (nullptr != w);
  // BOOST_TEST_MESSAGE(*w);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_vulkan_window_xcb_render)
{
  std::unique_ptr<window> w(new window("test_hugh_render_vulkan_window_xcb_render",
                                       std::chrono::milliseconds(800),
                                       { 0, 0, 800, 600 }));
  
  BOOST_CHECK(nullptr != w);

  w->display();
  
  // BOOST_TEST_MESSAGE(*w);
}
