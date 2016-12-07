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
#include <hugh/support/refcounted.hpp>

namespace hugh {
  
  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)
      
      /*
       * adapted from [https://vulkan-tutorial.com/]
       */
      template <typename T>
      class handle : public support::refcounted<handle<T>>,
                     public support::printable {
        
      public:

        using delete_with_nothing  = std::function<void(              T, ::VkAllocationCallbacks*)>;
        using delete_with_instance = std::function<void(::VkInstance, T, ::VkAllocationCallbacks*)>;
        using delete_with_device   = std::function<void(::VkDevice,   T, ::VkAllocationCallbacks*)>;
        
        handle();
        handle(                             delete_with_nothing);
        handle(handle<::VkInstance> const&, delete_with_instance);
        handle(handle<::VkDevice> const&,   delete_with_device);
        ~handle();

        /*
         * returns a pointer to 'object'
         */
        T const* operator &() const;
        T*       operator &();

        /*
         * returns the 'object'
         */
        T const& operator *() const;
        T&       operator *();

        /*
         * returns the 'object' (viable auto-conversion)
         */
        operator T const () const;
        operator T       ();

        operator bool () const;

        T reset(T const&);
        
        void operator=(T const&);

        template <typename U> bool operator==(U const&);

        virtual void print_on(std::ostream&) const;
        
      protected:
        
        T                       object_;
        std::function<void (T)> deleter_;

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
