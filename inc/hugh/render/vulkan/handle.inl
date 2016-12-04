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
      handle<T>::handle(delete_generic a)
        : object_ (nullptr),
          deleter_([=](T o) { a(o, nullptr); })
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::handle(delete_generic)");
      }

      template <typename T>
      inline
      handle<T>::handle(handle<::VkInstance> const& a, delete_instance b)
        : object_ (nullptr),
          deleter_([&a, b](T o) { b(a, o, nullptr); })
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::handle(delete_instance)");
      }

      template <typename T>
      inline
      handle<T>::handle(handle<::VkDevice> const& a, delete_device b)
        : object_ (nullptr),
          deleter_([&a, b](T o) { b(a, o, nullptr); })
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::handle(delete_device)");
      }

      template <typename T>
      inline
      handle<T>::~handle()
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::~handle");
        
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
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::operator &");

        return &object_;
      }

      template <typename T>
      inline T const&
      handle<T>::operator *() const
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::operator * const");

        return object_;
      }

      template <typename T>
      inline T&
      handle<T>::operator *()
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::operator *");

        return object_;
      }

      template <typename T>
      inline
      handle<T>::operator T const () const
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) +
              ">::operator T const");

        return object_;
      }

      template <typename T>
      inline
      handle<T>::operator T ()
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::operator T");

        return object_;
      }

      template <typename T>
      inline
      handle<T>::operator bool () const
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::operator bool");

        return (nullptr != object_);
      }

      template <typename T>
      inline T
      handle<T>::reset(T const& a)
      {
        TRACE("hugh::render::vulkan::handle<" + support::demangle(typeid(T)) + ">::reset");

        T const result(object_);
        
        if (a != object_) {
          cleanup();
          
          object_ = a;
        }

        return result;
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

        // avoid catching 'object_' with 'support::ostream::operator<<'
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
