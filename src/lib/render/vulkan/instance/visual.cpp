// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/instance/visual.cpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/instance/visual.hpp"

// includes, system

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error, std::runtime_error

// includes, project

#include <hugh/render/vulkan/io.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  using string_list_type = hugh::render::vulkan::instance::visual::string_list_type;
  
  // variables, internal

  string_list_type const dflt_extensions({ VK_KHR_SURFACE_EXTENSION_NAME });
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace render {
    
    namespace vulkan {

      namespace instance {
        
        // variables, exported
  
        // functions, exported        

        /* explicit */
        visual::visual(string_list_type const&    a,
                       string_list_type const&    b,
                       ::VkApplicationInfo const* c)
          : base(string_list_type(), a, dflt_extensions, b, c)
        {
          TRACE("hugh::render::vulkan::instance::visual::visual(dflt)");
        }

        /* virtual */
        visual::~visual()
        {
          TRACE("hugh::render::vulkan::instance::visual::~visual");
        }
        
      } // namespace instance {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
