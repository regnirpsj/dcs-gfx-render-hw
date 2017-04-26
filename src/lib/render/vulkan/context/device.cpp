// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016-2017 University of Hull                                                     */
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

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error, std::runtime_error

// includes, project

#include <hugh/render/vulkan/instance/visual.hpp>
#include <hugh/support/io.hpp>

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
    TRACE("hugh::render::vulkan::context::device::<unnamed>::find_queue_families");

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

      namespace context {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        device::device(vulkan::instance::base* a)
          : render::context::device(),
            instance               (*this, "instance",
                                    std::bind(&device::cb_get_instance, this),
                                    std::bind(&device::cb_set_instance, this,
                                              std::placeholders::_1)),
            physical               (*this, "physical",
                                    std::bind(&device::cb_get_physical, this),
                                    std::bind(&device::cb_set_physical, this,
                                              std::placeholders::_1)),
            logical                (*this, "logical",
                                    std::bind(&device::cb_get_logical,  this),
                                    std::bind(&device::cb_set_logical,  this,
                                              std::placeholders::_1)),
            queue                  (*this, "queue",
                                    std::bind(&device::cb_get_queue,  this),
                                    std::bind(&device::cb_set_queue,  this,
                                              std::placeholders::_1)),
            instance_              ((nullptr != a) ? a : new vulkan::instance::visual),
            physical_              (new adapter(*instance_)),
            logical_               (::vkDestroyDevice),
            queue_                 ()
        {
          TRACE("hugh::render::vulkan::context::device::device");
          
          float const                dflt_queue_priority(0.0f);
          queue_family_indices const indices(find_queue_families(*physical_));

          VkDeviceQueueCreateInfo dqci = { };
          
          dqci.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
          dqci.queueFamilyIndex = unsigned(indices.graphics_family);
          dqci.queueCount       = 1;
          dqci.pQueuePriorities = &dflt_queue_priority;
            
          ::VkPhysicalDeviceFeatures pdf = { };
            
          ::VkDeviceCreateInfo dci = { };

          dci.sType                 = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
          dci.pQueueCreateInfos     = &dqci;
          dci.queueCreateInfoCount  = 1;
          dci.pEnabledFeatures      = &pdf;
          dci.enabledExtensionCount = 0;
          dci.enabledLayerCount     = 0;

          VkResult const result(::vkCreateDevice(*physical_, &dci, nullptr, &logical_));

          if (VK_SUCCESS != result) {
            std::ostringstream ostr;

            ostr << "'vkCreateDevice' failed (" << result << ")!";
            
            std::runtime_error(ostr.str());
          }

          ::vkGetDeviceQueue(*logical_, physical_->queue_family->index.graphics, 0, &queue_);
        }
        
        /* virtual */
        device::~device()
        {
          TRACE("hugh::render::vulkan::context::device::~device");
        }
        
        device::instance_type const&
        device::cb_get_instance() const
        {
          TRACE("hugh::render::vulkan::context::device::cb_get_instance");

          return instance_;
        }
        
        device::instance_type
        device::cb_set_instance(instance_type const&)
        {
          TRACE("hugh::render::vulkan::context::device::cb_set_instance");
          
          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::device::cb_set_instance'");

          return instance_type();
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

        device::adapter_type const&
        device::cb_get_physical() const
        {
          TRACE("hugh::render::vulkan::context::device::cb_get_physical");

          return physical_;
        }
        
        device::adapter_type
        device::cb_set_physical(adapter_type const&)
        {
          TRACE("hugh::render::vulkan::context::device::cb_set_physical");
          
          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::device::cb_set_physical'");

          return adapter_type();
        }
        
        device::queue_handle_type const&
        device::cb_get_queue() const
        {
          TRACE("hugh::render::vulkan::context::device::cb_get_queue");

          return queue_;
        }

        device::queue_handle_type
        device::cb_set_queue(queue_handle_type const&)
        {
          TRACE("hugh::render::vulkan::context::device::cb_set_queue");

          throw std::logic_error("invalid operation "
                                 "'hugh::render::vulkan::context::device::cb_set_queue'");

          return queue_handle_type();
        }
        
      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
