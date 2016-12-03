// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/handle.inl                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_HANDLE_INL)

#define HUGH_RENDER_VULKAN_HANDLE_INL

// includes, system

#include <typeinfo>

// includes, project

#include <hugh/render/vulkan/io.hpp>
#include <hugh/support/io_utils.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {

      // functions, inlined (inline)  

      template <typename T>
      inline
      handle<T>::handle()
        : handle([](T, ::VkAllocationCallbacks*) {})
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::handle(dflt)");
      }

      template <typename T>
      inline
      handle<T>::handle(generic_deleter a)
        : object_ (nullptr),
          deleter_([=](T o) { a(o, nullptr); })
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::handle(generic_deleter)");
      }

      template <typename T>
      inline
      handle<T>::handle(handle<::VkInstance> const& a, instance_deleter b)
        : object_ (nullptr),
          deleter_([&a, b](T o) { b(a, o, nullptr); })
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::handle(instance_deleter)");
      }

      template <typename T>
      inline
      handle<T>::handle(handle<::VkDevice> const& a, device_deleter b)
        : object_ (nullptr),
          deleter_([&a, b](T o) { b(a, o, nullptr); })
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::handle(device_deleter)");
      }

      template <typename T>
      inline
      handle<T>::~handle()
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::~handle");
        
        cleanup();
      }

      template <typename T>
      inline T const*
      handle<T>::operator &() const
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::operator & const");

        return &object_;
      }

      template <typename T>
      inline T*
      handle<T>::operator &()
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::operator &");

        return &object_;
      }

      template <typename T>
      inline
      handle<T>::operator T() const
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::operator " + support::demangle(typeid(T)));

        return object_;
      }

      template <typename T>
      inline void
      handle<T>::operator=(T const& rhs)
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::operator=");

        if (rhs != object_) {
          cleanup();
          
          object_ = rhs;
        }
      }

      template <typename T> template <typename U>
      inline bool
      handle<T>::operator==(U const& rhs)
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::operator==");

        return object_ == T(rhs);
      }

      template <typename T>
      /* virtual */ inline void
      handle<T>::print_on(std::ostream& os) const
      { 
        TRACE_NEVER("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::print_on");

        os << '['
           << object_
           << ',';

        // avoids catching 'object_' with an 'support::ostream::operator<<'
        using support::ostream::operator<<;
        
        os << deleter_
           << ']';
      }
        
      template <typename T>
      inline void
      handle<T>::cleanup()
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::cleanup");
        
        if (nullptr != object_) {
          deleter_(object_);

          object_ = nullptr;
        }        
      }
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_RENDER_VULKAN_HANDLE_INL)
