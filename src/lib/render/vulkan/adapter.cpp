// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/adapter.cpp                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/adapter.hpp"

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

  struct queue_family_indices {

  public:
    
    signed graphics_family = -1;

    bool is_complete()
    {
      return (graphics_family >= 0);
    }
    
  };
  
  // variables, internal
  
  // functions, internal

  queue_family_indices
  find_queue_families(::VkPhysicalDevice device)
  {
    TRACE("hugh::render::vulkan::adapter::<unnamed>::find_queue_families");
    
    queue_family_indices indices;
    unsigned             count(0);
    
    ::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

    std::vector<::VkQueueFamilyProperties> queue_families(count);
    
    ::vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queue_families.data());

    unsigned i(0);
    
    for (auto const& qf : queue_families) {
      if ((0 < qf.queueCount) && (qf.queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
        indices.graphics_family = i;
      }

      if (indices.is_complete()) {
        break;
      }

      ++i;
    }

    return indices;
  }
  
} // namespace {

namespace hugh {

  namespace render {
    
    namespace vulkan {
    
      // variables, exported
  
      // functions, exported

      /* explicit */
      adapter::adapter(vulkan::instance* a)
        : handle<::VkPhysicalDevice>(),
          instance                  ((nullptr != a) ? a : new vulkan::instance)
      {
        TRACE("hugh::render::vulkan::adapter::adapter");
        
        unsigned count(0);
            
        ::vkEnumeratePhysicalDevices(*instance, &count, nullptr);

        if (0 == count) {
          throw std::runtime_error("'vkEnumeratePhysicalDevices'"
                                   "failed to find GPUs with Vulkan support!");
        }

        std::vector<::VkPhysicalDevice> adapter_list(count);
            
        ::vkEnumeratePhysicalDevices(*instance, &count, adapter_list.data());

        for (const auto& a : adapter_list) {
          if (find_queue_families(a).is_complete()) {
            object_ = a;
                
            break;
          }
        }
        
        if (nullptr == object_) {
          throw std::runtime_error("'vkEnumeratePhysicalDevices'"
                                   "did not find a suitable GPU!");
        }
      }
      
      /* virtual */
      adapter::~adapter()
      {
        TRACE("hugh::render::vulkan::adapter::~adapter");
      }      
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
