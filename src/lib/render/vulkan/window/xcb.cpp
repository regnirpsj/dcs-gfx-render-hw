// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/window/xcb.cpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/window/xcb.hpp"

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace render {

    namespace vulkan {

      namespace window {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        xcb::xcb(std::string const& a, rect const& b, std::string const& c)
          : window::base                 (),
            platform::xcb::window::simple(a, b, c)
        {
          TRACE("hugh::render::vulkan::window::xcb::xcb");
        }
        
        /* virtual */
        xcb::~xcb()
        {
          TRACE("hugh::render::vulkan::window::xcb::xcb");
        }

        /* virtual */ void
        xcb::print_on(std::ostream& os) const
        {
          TRACE_NEVER("hugh::render::vulkan::window::xcb::print_on");

          os << '[';
          
          window::base::print_on(os);

          os << ',';
          
          platform::xcb::window::simple::print_on(os);

          os << ']';
        }
        
      } // namespace window {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
