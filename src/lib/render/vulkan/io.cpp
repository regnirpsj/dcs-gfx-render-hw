// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016-2017 University of Hull                                                     */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/io.cpp                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/io.hpp"

// includes, system

#include <array>    // std::array<>
#include <ostream>  // std::ostream
#include <typeinfo> // typeid
#include <utility>  // std::make_pair<>, std::pair<>

// includes, project

#include <hugh/support/io.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal  
  
  template <typename T>
  inline std::ostream&
  get_handle(std::ostream& os, T const& a,
             std::string const& b = hugh::support::demangle(typeid(T)))
  {
    std::ostream::sentry const cerberus(os);

    if (cerberus) {
      if (nullptr != a) {
        os << b << '@' << static_cast<void const*>(a);
      } else {
        os << "uninitialized " << b;
      }
    }
    
    return os;
  }
  
} // namespace {

namespace hugh {
  
  namespace render {

    namespace vulkan {
      
      // variables, exported
  
      // functions, exported      

      std::ostream&
      operator<<(std::ostream& os, ::VkDevice const& a)
      {
        return get_handle(os, a, "VkDevice");
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkExtent3D const& a)
      {
        std::ostream::sentry const cerberus(os);
        
        if (cerberus) {
          os << '['
             << a.width  << ','
             << a.height << ','
             << a.depth
             << "]";
        }
        
        return os;
      }
      
      std::ostream&
      operator<<(std::ostream& os, ::VkInstance const& a)
      {
        return get_handle(os, a, "VkInstance");
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkInternalAllocationType const& a)
      {
        static std::array<std::pair<::VkInternalAllocationType, std::string const>, 1> const
          types = {
          std::make_pair(VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE,
                         "INTERNAL_ALLOCATION_TYPE_EXECUTABLE"),
        };

        return os << support::ostream::enumerate(a, types);
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkPhysicalDevice const& a)
      {
        return get_handle(os, a, "VkPhysicalDevice");
      }

      std::ostream& operator<<(std::ostream& os, ::VkPhysicalDeviceProperties const& a)
      {
        std::ostream::sentry const cerberus(os);
        
        if (cerberus) {
          os << '['
             << "api:"
             << VK_VERSION_MAJOR(a.apiVersion) << '.'
             << VK_VERSION_MINOR(a.apiVersion) << '.'
             << VK_VERSION_PATCH(a.apiVersion) << ','
             << "drv:" << a.driverVersion     << ','
             << "vendor:" << std::hex << a.vendorID          << ','
             << "devid:" << std::hex << a.deviceID          << ','
             << a.deviceType        << ','
             << a.deviceName        << ','
             << "ppl$uuid:" << a.pipelineCacheUUID
            // << a.limits
            // << a.sparseProperties
             << "]";
        }
        
        return os;
      }
      
      std::ostream&
      operator<<(std::ostream& os, ::VkPhysicalDeviceType const& a)
      {
        static std::array<std::pair<::VkPhysicalDeviceType, std::string const>, 5> const types = {
          std::make_pair(VK_PHYSICAL_DEVICE_TYPE_OTHER,          "OTHER"),
          std::make_pair(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU, "IGPU"),
          std::make_pair(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU,   "DGPU"),
          std::make_pair(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU,    "VGPU"),
          std::make_pair(VK_PHYSICAL_DEVICE_TYPE_CPU,            "CPU"),
        };
        
        return os << support::ostream::enumerate(a, types);
      }
      
      std::ostream&
      operator<<(std::ostream& os, ::VkQueue const& a)
      {
        return get_handle(os, a, "VkQueue");
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkQueueFamilyProperties const& a)
      {
        std::ostream::sentry const cerberus(os);
        
        if (cerberus) {
          os << '['
             << ::VkQueueFlagBits(a.queueFlags) << ','
             << a.queueCount                    << ','
             << a.timestampValidBits            << ','
             << a.minImageTransferGranularity
             << "]";
        }
        
        return os;
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkQueueFlagBits const& a)
      {
        static std::array<std::pair<::VkQueueFlagBits, std::string const>, 4> const flags = {
          std::make_pair(VK_QUEUE_COMPUTE_BIT,        "COMPUTE"),
          std::make_pair(VK_QUEUE_GRAPHICS_BIT,       "GRAPHICS"),
          std::make_pair(VK_QUEUE_SPARSE_BINDING_BIT, "SPARSE_BINDING"),
          std::make_pair(VK_QUEUE_TRANSFER_BIT,       "TRANSFER"),
        };
        
        return os << support::ostream::flags(a, flags);
      }
      
      std::ostream&
      operator<<(std::ostream& os, ::VkResult const& a)
      {
        static std::array<std::pair<::VkResult, std::string const>, 25> const results = {
          std::make_pair(VK_SUCCESS,                        "SUCCESS"),
          std::make_pair(VK_NOT_READY,                      "NOT_READY"),
          std::make_pair(VK_TIMEOUT,                        "TIMEOUT"),
          std::make_pair(VK_EVENT_SET,                      "EVENT_SET"),
          std::make_pair(VK_EVENT_RESET,                    "EVENT_RESET"),
          std::make_pair(VK_INCOMPLETE,                     "INCOMPLETE"),
          std::make_pair(VK_ERROR_OUT_OF_HOST_MEMORY,       "ERROR_OUT_OF_HOST_MEMORY"),
          std::make_pair(VK_ERROR_OUT_OF_DEVICE_MEMORY,     "ERROR_OUT_OF_DEVICE_MEMORY"),
          std::make_pair(VK_ERROR_INITIALIZATION_FAILED,    "ERROR_INITIALIZATION_FAILED"),
          std::make_pair(VK_ERROR_DEVICE_LOST,              "ERROR_DEVICE_LOST"),
          std::make_pair(VK_ERROR_MEMORY_MAP_FAILED,        "ERROR_MEMORY_MAP_FAILED"),
          std::make_pair(VK_ERROR_LAYER_NOT_PRESENT,        "ERROR_LAYER_NOT_PRESENT"),
          std::make_pair(VK_ERROR_EXTENSION_NOT_PRESENT,    "ERROR_EXTENSION_NOT_PRESENT"),
          std::make_pair(VK_ERROR_FEATURE_NOT_PRESENT,      "ERROR_FEATURE_NOT_PRESENT"),
          std::make_pair(VK_ERROR_INCOMPATIBLE_DRIVER,      "ERROR_INCOMPATIBLE_DRIVER"),
          std::make_pair(VK_ERROR_TOO_MANY_OBJECTS,         "ERROR_TOO_MANY_OBJECTS"),
          std::make_pair(VK_ERROR_FORMAT_NOT_SUPPORTED,     "ERROR_FORMAT_NOT_SUPPORTED"),
          std::make_pair(VK_ERROR_FRAGMENTED_POOL,          "ERROR_FRAGMENTED_POOL"),
          std::make_pair(VK_ERROR_SURFACE_LOST_KHR,         "ERROR_SURFACE_LOST_KHR"),
          std::make_pair(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR, "ERROR_NATIVE_WINDOW_IN_USE_KHR"),
          std::make_pair(VK_SUBOPTIMAL_KHR,                 "SUBOPTIMAL_KHR"),
          std::make_pair(VK_ERROR_OUT_OF_DATE_KHR,          "ERROR_OUT_OF_DATE_KHR"),
          std::make_pair(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR, "ERROR_INCOMPATIBLE_DISPLAY_KHR" ),
          std::make_pair(VK_ERROR_VALIDATION_FAILED_EXT,    "ERROR_VALIDATION_FAILED_EXT"),
          std::make_pair(VK_ERROR_INVALID_SHADER_NV,        "ERROR_INVALID_SHADER_NV"),
        };

        return os << support::ostream::enumerate(a, results);
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkSurfaceKHR const& a)
      {
        return get_handle(os, a, "VkSurfaceKHR");
      }
      
      std::ostream&
      operator<<(std::ostream& os, ::VkSystemAllocationScope const& a)
      {
        static std::array<std::pair<::VkSystemAllocationScope, std::string const>, 5> const
          scopes = {
          std::make_pair(VK_SYSTEM_ALLOCATION_SCOPE_COMMAND,  "SYSTEM_ALLOCATION_SCOPE_COMMAND"),
          std::make_pair(VK_SYSTEM_ALLOCATION_SCOPE_OBJECT,   "SYSTEM_ALLOCATION_SCOPE_OBJECT"),
          std::make_pair(VK_SYSTEM_ALLOCATION_SCOPE_CACHE,    "SYSTEM_ALLOCATION_SCOPE_CACHE"),
          std::make_pair(VK_SYSTEM_ALLOCATION_SCOPE_DEVICE,   "SYSTEM_ALLOCATION_SCOPE_DEVICE"),
          std::make_pair(VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE, "SYSTEM_ALLOCATION_SCOPE_INSTANCE"),
        };

        return os << support::ostream::enumerate(a, scopes);
      }
      
    } // namespace vulkan {

  } // namespace render {

} // namespace hugh {
