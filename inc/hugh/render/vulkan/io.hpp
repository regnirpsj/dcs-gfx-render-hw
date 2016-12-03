// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/io.hpp                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_IO_HPP)

#define HUGH_RENDER_VULKAN_IO_HPP

// includes, system

#include <iosfwd>          // std::ostream (fwd decl)
#include <vulkan/vulkan.h> // vk::*

// includes, project

#include <hugh/render/vulkan/export.h>

namespace hugh {

  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)

      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

      HUGH_RENDER_VULKAN_EXPORT std::ostream& operator<<(std::ostream&, ::VkDevice const&);
      HUGH_RENDER_VULKAN_EXPORT std::ostream& operator<<(std::ostream&, ::VkInstance const&);
      HUGH_RENDER_VULKAN_EXPORT std::ostream& operator<<(std::ostream&, ::VkPhysicalDevice const&);
      HUGH_RENDER_VULKAN_EXPORT std::ostream& operator<<(std::ostream&, ::VkSurfaceKHR const&);
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_IO_HPP)
