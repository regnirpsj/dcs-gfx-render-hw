// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/context/swap.hpp                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_CONTEXT_SWAP_HPP)

#define HUGH_RENDER_VULKAN_CONTEXT_SWAP_HPP

// includes, system

#include <vulkan/vulkan.h> // [V|v]k*

// includes, project

#include <hugh/render/context/swap.hpp>
#include <hugh/render/vulkan/context/device.hpp>

namespace hugh {
  
  namespace render {

    namespace vulkan {

      namespace context {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_VULKAN_EXPORT swap : public render::context::swap {

        public:

          using device_context_type = context::device;
          using surface_handle_type = vulkan::handle<::VkSurfaceKHR>;

          field::adapter::single<device_context_type> const device;  //< device context
          field::adapter::single<surface_handle_type> const surface; //< surface

          explicit swap(device_context_type& /* device context */,
                        glm::uvec2 const&    /* size           */ = glm::uvec2(1,1));
          virtual ~swap();
          
        protected:

          device_context_type& device_;
          surface_handle_type  surface_;

          device_context_type const& cb_get_device () const;
          device_context_type        cb_set_device (device_context_type const&);
          surface_handle_type const& cb_get_surface() const;
          surface_handle_type        cb_set_surface(surface_handle_type const&);

        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_CONTEXT_SWAP_HPP)
