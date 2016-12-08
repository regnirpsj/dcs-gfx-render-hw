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
  
  // variables, internal
  
  // functions, internal

  unsigned
  queue_index(::VkPhysicalDevice a, ::VkQueueFlags b)
  {
    TRACE("hugh::render::vulkan::adapter::<unnamed>::queue_index");
    
    unsigned count;
    
    ::vkGetPhysicalDeviceQueueFamilyProperties(a, &count, nullptr);
          
    std::vector<::VkQueueFamilyProperties> qfp(count);
    
    ::vkGetPhysicalDeviceQueueFamilyProperties(a, &count, qfp.data());
    
    signed result(-1);
    
    if ((0 > result) && (VK_QUEUE_COMPUTE_BIT & b)) {
      for (unsigned i(0); i < qfp.size(); ++i) {
        if ((qfp[i].queueFlags & b) && (0 == (qfp[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))) {
          result = i;
          
          break;
        }
      }
    }
    
    if ((0 > result) && (VK_QUEUE_TRANSFER_BIT & b)) {
      for (unsigned i(0); i < qfp.size(); ++i) {
        if ((qfp[i].queueFlags & b) && (0 == (qfp[i].queueFlags & VK_QUEUE_COMPUTE_BIT))) {
          result = i;
          
          break;
        }
      }
    }

    if (0 > result) {
      for (unsigned i(0); i < qfp.size(); ++i) {
        if (qfp[i].queueFlags & b) {
          result = i;
          
          break;
        }
      }
    }

    if (0 > result) {
      using hugh::render::vulkan::operator<<;
      
      std::ostringstream ostr;

      ostr << "No matching queue family index found on " << a;
      
      throw std::runtime_error(ostr.str());
    }
    
    return result;
  }
  
} // namespace {

namespace hugh {

  namespace render {
    
    namespace vulkan {
    
      // variables, exported
  
      // functions, exported

      /* explicit */
      adapter::adapter(vulkan::instance const& a, unsigned b)
        : field::container          (),
          handle<::VkPhysicalDevice>(),
          queue_family              (*this, "queue_family",
                                     std::bind(&adapter::get_cb_queue_family, this),
                                     std::bind(&adapter::set_cb_queue_family, this,
                                               std::placeholders::_1)),
          queue_family_             ({ 0, { -1, -1, -1, -1, }})
      {
        TRACE("hugh::render::vulkan::adapter::adapter");

        {
          unsigned count(0);
            
          ::vkEnumeratePhysicalDevices(*a, &count, nullptr);

          if (0 == count) {
            throw std::runtime_error("'vkEnumeratePhysicalDevices'"
                                     "failed to find GPUs with Vulkan support!");
          }

          std::vector<::VkPhysicalDevice> adapter_list(count);
            
          ::vkEnumeratePhysicalDevices(*a, &count, adapter_list.data());

        
          unsigned const index((b < adapter_list.size()) ? b : 0);
        
          object_ = adapter_list[index];
        }

        if (nullptr == object_) {
          throw std::runtime_error("'vkEnumeratePhysicalDevices'"
                                   "did not find a suitable GPU!");
        }
        
        for (::VkQueueFlagBits f : { VK_QUEUE_COMPUTE_BIT,        VK_QUEUE_GRAPHICS_BIT,
                                     VK_QUEUE_SPARSE_BINDING_BIT, VK_QUEUE_TRANSFER_BIT, }) {
          signed const index(queue_index(object_, f));
          
          if (0 <= index) {
            bool update_flags(true);
            
            switch (f) {
            case VK_QUEUE_COMPUTE_BIT:        queue_family_.index.compute        = index; break;
            case VK_QUEUE_GRAPHICS_BIT:       queue_family_.index.graphics       = index; break;
            case VK_QUEUE_SPARSE_BINDING_BIT: queue_family_.index.sparse_binding = index; break;
            case VK_QUEUE_TRANSFER_BIT:       queue_family_.index.transfer       = index; break;
            default:                          update_flags = false;                       break;
            }

            if (update_flags) {
              queue_family_.flags |= f;
            }
          }
        }
      }
      
      /* virtual */
      adapter::~adapter()
      {
        TRACE("hugh::render::vulkan::adapter::~adapter");
      }
      
      /* virtual */ void
      adapter::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::render::vulkan::adapter::print_on");
        
        field::container::print_on(os);
        
        os << support::ostream::remove(1) << ',';
        
        handle<::VkPhysicalDevice>::print_on(os);
      }
      
      adapter::queue_family_t const&
      adapter::get_cb_queue_family() const
      {
        TRACE("hugh::render::vulkan::adapter::get_cb_queue_family");
        
        return queue_family_;
      }
      
      adapter::queue_family_t
      adapter::set_cb_queue_family(queue_family_t const&)
      {
        TRACE("hugh::render::vulkan::adapter::set_cb_queue_family");
        
        throw std::logic_error("invalid operation "
                               "'hugh::render::vulkan::adapter::set_cb_queue_family'");
        
        return queue_family_t();
      }
      
      std::ostream&
      operator<<(std::ostream& os, adapter::queue_family_t const& a)
      {
        std::ostream::sentry const cerberus(os);
        
        if (cerberus) {
          os << '['
             << ::VkQueueFlagBits(a.flags)     << ",["
             << "c:" << a.index.compute        << ','
             << "g:" << a.index.graphics       << ','
             << "s:" << a.index.sparse_binding << ','
             << "t:" << a.index.transfer
             << "]]";
        }
        
        return os;
      }
      
    } // namespace vulkan {
    
  } // namespace render {
  
} // namespace hugh {
