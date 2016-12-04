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

// #include <glm/gtx/io.hpp> // glm::io::*
// #include <ostream>        // std::ostream
#include <stdexcept>      // std::logic_error, std::runtime_error

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
          : render::context::device(),
            instance               (*this, "instance",
                                    std::bind(&device::cb_get_instance, this),
                                    std::bind(&device::cb_set_instance, this,
                                              std::placeholders::_1)),
            physical               (*this, "phyiscal",
                                    std::bind(&device::cb_get_physical, this),
                                    std::bind(&device::cb_set_physical, this,
                                              std::placeholders::_1)),
            logical                (*this, "logical",
                                    std::bind(&device::cb_get_logical,  this),
                                    std::bind(&device::cb_set_logical,  this,
                                              std::placeholders::_1)),
            instance_              (::vkDestroyInstance),
            physical_              (),
            logical_               (::vkDestroyDevice)
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
                physical_ = a;
                
                break;
              }
            }

            if (nullptr == physical_) {
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

        device::instance_handle_type const&
        device::cb_get_instance() const
        {
          TRACE("hugh::render::vulkan::context::device::cb_get_instance");

          return instance_;
        }

        device::instance_handle_type
        device::cb_set_instance(instance_handle_type const&)
        {
          TRACE("hugh::render::vulkan::context::device::cb_set_instance");

          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::device::cb_set_instance'");

          return instance_handle_type();
        }

        device::device_handle_type const&
        device::cb_get_logical() const
        {
          TRACE("hugh::render::vulkan::context::device::cb_get_logical");

          return logical_;
        }

        device::device_handle_type
        device::cb_set_logical(device_handle_type const&)
        {
          TRACE("hugh::render::vulkan::context::device::cb_set_logical");

          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::device::cb_set_logical'");

          return device_handle_type();
        }

        device::adapter_handle_type const&
        device::cb_get_physical() const
        {
          TRACE("hugh::render::vulkan::context::device::cb_get_physical");

          return physical_;
        }
        
        device::adapter_handle_type
        device::cb_set_physical(adapter_handle_type const&)
        {
          TRACE("hugh::render::vulkan::context::device::cb_set_physical");
          
          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::device::cb_set_physical'");

          return adapter_handle_type();
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
