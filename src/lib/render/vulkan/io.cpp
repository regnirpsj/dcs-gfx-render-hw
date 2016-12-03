// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
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

#include <ostream>  // std::ostream
#include <typeinfo> // typeid

// includes, project

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
      operator<<(std::ostream& os, ::VkInstance const& a)
      {
        return get_handle(os, a, "VkInstance");
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkPhysicalDevice const& a)
      {
        return get_handle(os, a, "VkPhysicalDevice");
      }

      std::ostream&
      operator<<(std::ostream& os, ::VkSurfaceKHR const& a)
      {
        return get_handle(os, a, "VkSurfaceKHR");
      }
      
    } // namespace vulkan {

  } // namespace render {

} // namespace hugh {
