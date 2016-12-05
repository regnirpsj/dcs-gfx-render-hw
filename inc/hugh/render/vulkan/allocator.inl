// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/allocator.inl                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_ALLOCATOR_INL)

#define HUGH_RENDER_VULKAN_ALLOCATOR_INL

// includes, system

#include <iostream> // std::cout
#include <cstdlib>  // std::aligned_alloc

// includes, project

#include <hugh/render/vulkan/io.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
//#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
//#  include <typeinfo>
//#  include <hugh/support/type_info.hpp>
//#endif

namespace hugh {

  namespace render {

    namespace vulkan {
      
      // functions, inlined (inline)

      inline
      allocator::allocator()
        : cb_ {
          .pUserData             = static_cast<void*>(const_cast<allocator*>(this)),
          .pfnAllocation         = &allocator::alloc,
          .pfnReallocation       = &allocator::realloc,
          .pfnFree               = &allocator::dealloc,
          .pfnInternalAllocation = &allocator::notify_alloc,
          .pfnInternalFree       = &allocator::notify_free,
          }
      {}
      
      inline
      allocator::operator ::VkAllocationCallbacks const* () const
      {
        return &cb_;
      }

      /* static */ inline void* VKAPI_CALL
      allocator::alloc(void* a, size_t b, size_t c, ::VkSystemAllocationScope d)
      {
        return static_cast<allocator*>(a)->alloc(c, b, d);
      }
        
      /* static */ inline void* VKAPI_CALL
      allocator::realloc(void* a, void* b, size_t c, size_t d, ::VkSystemAllocationScope e)
      {
        return static_cast<allocator*>(a)->alloc(b, d, c, e);
      }
        
      /* static */ inline void  VKAPI_CALL
      allocator::dealloc(void* a, void* b)
      {
        static_cast<allocator*>(a)->dealloc(b);
      }

      /* static */ inline void VKAPI_CALL
      allocator::notify_alloc(void* a, size_t b, ::VkInternalAllocationType c,
                              ::VkSystemAllocationScope d)
      {
        std::cout << support::trace::prefix() << "hugh::render::vulkan::allocator::notify_alloc: "
                  << '@' << a << '+' << b << '(' << c << ',' << d << ')'
                  << std::endl;
      }

      /* static */ inline void VKAPI_CALL
      allocator::notify_free(void* a, size_t b, ::VkInternalAllocationType c,
                             ::VkSystemAllocationScope d)
      {
        std::cout << support::trace::prefix() << "hugh::render::vulkan::allocator::notify_free: "
                  << '@' << a << '+' << b << '(' << c << ',' << d << ')'
                  << std::endl;
      }
      
      inline void*
      allocator::alloc(size_t a, size_t b, ::VkSystemAllocationScope)
      {
        return ::aligned_alloc(b, a);
      }
        
      inline void*
      allocator::realloc(void* a, size_t b, size_t c, ::VkSystemAllocationScope)
      {
        dealloc(a);
        
        return ::aligned_alloc(b, c);
      }
        
      inline void
      allocator::dealloc(void* a)
      {
        std::free(a);
      }

    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_RENDER_VULKAN_ALLOCATOR_INL)
