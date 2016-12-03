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

          explicit swap(device&, glm::uvec2 const&);
          virtual ~swap();

          virtual void print_on(std::ostream&) const;
          
        private:

          device&                ctx_;
          handle<::VkSurfaceKHR> surface_;
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_CONTEXT_SWAP_HPP)
