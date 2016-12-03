// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/allocator.hpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_ALLOCATOR_HPP)

#define HUGH_RENDER_VULKAN_ALLOCATOR_HPP

// includes, system

#include <vulkan/vulkan.h> // vk::*

// includes, project

#include <hugh/render/vulkan/export.h>

namespace hugh {
  
  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)
      
      class HUGH_RENDER_VULKAN_EXPORT allocator {
        
      public:

        allocator();
        
        operator ::VkAllocationCallbacks const& () const;

      private:

        VkAllocationCallbacks cb_;
        
        static void* VKAPI_CALL alloc  (void*                     /* user data */,
                                        size_t                    /* size      */,
                                        size_t                    /* alignment */,
                                        ::VkSystemAllocationScope /* scope     */);
        
        static void* VKAPI_CALL realloc(void*                     /* user data */,
                                        void*                     /* original  */,
                                        size_t                    /* size      */,
                                        size_t                    /* alignment */,
                                        ::VkSystemAllocationScope /* scope     */);
        
        static void  VKAPI_CALL dealloc(void*                     /* user data */,
                                        void*                     /* memory    */);

        void* alloc  (size_t                    /* size      */,
                      size_t                    /* alignment */,
                      ::VkSystemAllocationScope /* scope     */);
        
        void* realloc(void*                     /* original  */,
                      size_t                    /* size      */,
                      size_t                    /* alignment */,
                      ::VkSystemAllocationScope /* scope     */);
        
        void  dealloc(void*                     /* memory    */);

      };

      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#include <hugh/render/vulkan/allocator.inl>

#endif // #if !defined(HUGH_RENDER_VULKAN_ALLOCATOR_HPP)
