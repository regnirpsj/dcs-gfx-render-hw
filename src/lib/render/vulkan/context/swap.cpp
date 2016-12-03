// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/context/swap.cpp                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/context/swap.hpp"

// includes, system

#include <glm/gtx/io.hpp> // glm::io::*
#include <ostream>        // std::ostream
#include <stdexcept>      // std::runtime_error

// includes, project

#include <hugh/support/io_utils.hpp>

#define HUGH_USE_TRACE
//#undef HUGH_USE_TRACE
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

      namespace context {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        swap::swap(device & a, glm::uvec2 const& b)
          : render::context::base(b),
            render::context::swap(b),
            ctx_                 (a),
            surface_             (static_cast<handle<::VkInstance>&>(ctx_), ::vkDestroySurfaceKHR)
        {
          TRACE("hugh::render::vulkan::context::swap::swap");
        }
        
        /* virtual */
        swap::~swap()
        {
          TRACE("hugh::render::vulkan::context::swap::~swap");

          if (nullptr != surface_) {
            ::vkDeviceWaitIdle(static_cast<handle<::VkDevice>&>(ctx_));
          }
        }
        
        /* virtual */ void
        swap::print_on(std::ostream& os) const
        {
          TRACE_NEVER("hugh::render::vulkan::context::swap::print_on");

          os << glm::io::width(4);
          
          render::context::swap::print_on(os);

          using support::ostream::remove;
          
          os << remove(1) << ",\n"
             << ctx_      << ",\n"
             << surface_
             << ']';
        }
        
      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
