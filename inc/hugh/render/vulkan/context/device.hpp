// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/context/device.hpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_CONTEXT_DEVICE_HPP)

#define HUGH_RENDER_VULKAN_CONTEXT_DEVICE_HPP

// includes, system

#include <vulkan/vulkan.h> // [V|v]k*

// includes, project

#include <hugh/render/context/device.hpp>
#include <hugh/render/vulkan/export.h>
#include <hugh/render/vulkan/handle.hpp>

namespace hugh {
  
  namespace render {

    namespace vulkan {

      namespace context {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_VULKAN_EXPORT device : public render::context::device {

        public:

          explicit device();
          virtual ~device();
          
          operator handle<::VkInstance>& ();
          operator handle<::VkDevice>&   ();
          
          virtual void print_on(std::ostream&) const;
          
        private:

          handle<::VkInstance>       instance_;
          handle<::VkPhysicalDevice> adapter_;
          handle<::VkDevice>         device_;
          
          bool adapter_suitable(VkPhysicalDevice);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_CONTEXT_DEVICE_HPP)
