// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/handle.hpp                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_HANDLE_HPP)

#define HUGH_RENDER_VULKAN_HANDLE_HPP

// includes, system

#include <functional>      // std::function<>
#include <vulkan/vulkan.h> // vk::*

// includes, project

#include <hugh/render/vulkan/export.h>
#include <hugh/support/printable.hpp>

namespace hugh {
  
  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)
      
      // adapted from [https://vulkan-tutorial.com/]
      
      template <typename T>
      class handle : public support::printable {
        
      public:

        using generic_deleter  = std::function<void(              T, ::VkAllocationCallbacks*)>;
        using instance_deleter = std::function<void(::VkInstance, T, ::VkAllocationCallbacks*)>;
        using device_deleter   = std::function<void(::VkDevice,   T, ::VkAllocationCallbacks*)>;
        
        handle();
        handle(generic_deleter);
        handle(handle<::VkInstance> const&, instance_deleter);
        handle(handle<::VkDevice> const&,   device_deleter);
        ~handle();

        T const* operator &() const;
        T*       operator &();

        operator T() const;

        void operator=(T const&);

        template <typename U> bool operator==(U const&);

        virtual void print_on(std::ostream&) const;
        
      private:
        
        T                      object_;
        std::function<void(T)> deleter_;

        void cleanup();
        
      };

      // variables, exported (extern)

      // functions, inlined (inline)
      
      // functions, exported (extern)
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#include <hugh/render/vulkan/handle.inl>

#endif // #if !defined(HUGH_RENDER_VULKAN_HANDLE_HPP)
