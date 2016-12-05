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

#include <stdexcept> // std::logic_error, std::runtime_error

// includes, project

#include <hugh/support/io_utils.hpp>

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

      namespace context {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        swap::swap(context::device& a, glm::uvec2 const& b)
          : render::context::swap(b),
            device               (*this, "device",
                                  std::bind(&swap::cb_get_device,  this),
                                  std::bind(&swap::cb_set_device,  this, std::placeholders::_1)),
            surface              (*this, "surface",
                                  std::bind(&swap::cb_get_surface, this),
                                  std::bind(&swap::cb_set_surface, this, std::placeholders::_1)),
            device_              (a),
            surface_             (*device_.instance, ::vkDestroySurfaceKHR)
        {
          TRACE("hugh::render::vulkan::context::swap::swap");
        }
        
        /* virtual */
        swap::~swap()
        {
          TRACE("hugh::render::vulkan::context::swap::~swap");

          if (nullptr != surface_) {
            ::vkDeviceWaitIdle(**device_.logical);
          }
        }        

        swap::device_context_type const&
        swap::cb_get_device() const
        {
          TRACE("hugh::render::vulkan::context::swap::cb_get_logical");
          
          return device_;
        }
        
        swap::device_context_type
        swap::cb_set_device(device_context_type const&)
        {
          TRACE("hugh::render::vulkan::context::swap::cb_set_logical");

          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::swap::cb_set_logical'");

          return device_context_type();
        }
        
        swap::surface_handle_type const&
        swap::cb_get_surface() const
        {
          TRACE("hugh::render::vulkan::context::swap::cb_get_logical");
          
          return surface_;
        }
        
        swap::surface_handle_type
        swap::cb_set_surface(surface_handle_type const&)
        {
          TRACE("hugh::render::vulkan::context::swap::cb_set_logical");

          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::swap::cb_set_logical'");
          
          return surface_handle_type();
        }

      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
