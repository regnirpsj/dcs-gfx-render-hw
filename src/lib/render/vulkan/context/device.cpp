// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/context/device.cpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/context/device.hpp"

// includes, system

#include <glm/gtx/io.hpp> // glm::io::*
#include <ostream>        // std::ostream
#include <stdexcept>      // std::runtime_error

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
        device::device()
          : render::context::base  (glm::uvec2()),
            render::context::device(glm::uvec2()),
            instance_              (           ::vkDestroyInstance),
            adapter_               (),
            device_                (           ::vkDestroyDevice)
        {
          TRACE("hugh::render::vulkan::context::device::device");

          { // instance
            ::VkApplicationInfo const ai = {
              .sType         = VK_STRUCTURE_TYPE_APPLICATION_INFO,
              .pEngineName   = "hugh-render-vulkan",
              .engineVersion = VK_MAKE_VERSION(1, 0, 0),
              .apiVersion    = VK_API_VERSION_1_0,
            };
            
            ::VkInstanceCreateInfo    ici = {
              .sType             = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
              .pApplicationInfo  = &ai,
              .enabledLayerCount = 0,
            };
            
            if (VK_SUCCESS != ::vkCreateInstance(&ici, nullptr, &instance_)) {
              std::runtime_error("'vkCreateInstance' failed!");
            }
          }

          { // adapter
            unsigned count(0);
            
            ::vkEnumeratePhysicalDevices(*instance_, &count, nullptr);

            if (0 == count) {
              throw std::runtime_error("'vkEnumeratePhysicalDevices'"
                                       "failed to find GPUs with Vulkan support!");
            }

            std::vector<::VkPhysicalDevice> adapter_list(count);
            
            ::vkEnumeratePhysicalDevices(*instance_, &count, adapter_list.data());

            for (const auto& a : adapter_list) {
              if (adapter_suitable(a)) {
                adapter_ = a;
                
                break;
              }
            }

            if (nullptr == adapter_) {
              throw std::runtime_error("'vkEnumeratePhysicalDevices'"
                                       "failed to find a suitable GPU!");
            }
          }

          { // device
          }
        }
        
        /* virtual */
        device::~device()
        {
          TRACE("hugh::render::vulkan::context::device::~device");
        }

        device::operator handle<::VkInstance>& ()
        {
          TRACE("hugh::render::vulkan::context::device::operator handle<::VkInstance>&");

          return instance_;
        }
        
        device::operator handle<::VkDevice>& ()
        {
          TRACE("hugh::render::vulkan::context::device::operator handle<::VkDevice>&");

          return device_;
        }

        /* virtual */ void
        device::print_on(std::ostream& os) const
        {
          TRACE_NEVER("hugh::render::vulkan::context::device::print_on");

          os << glm::io::width(4);
          
          render::context::device::print_on(os);

          using support::ostream::remove;
          
          os << remove(1) << ",\n"
             << instance_ << ",\n"
             << adapter_  << ",\n"
             << device_
             << ']';
        }
        
        bool
        device::adapter_suitable(::VkPhysicalDevice)
        {
          TRACE("hugh::render::vulkan::context::device::adapter_suitable");
          
          return true;
        }
        
      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
