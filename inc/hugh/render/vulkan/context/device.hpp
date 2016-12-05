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

#include <hugh/field/adapter/single.hpp>
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

          using adapter_handle_type  = handle<::VkPhysicalDevice>;
          using device_handle_type   = handle<::VkDevice>;
          using instance_handle_type = handle<::VkInstance>;          
          using queue_handle_type    = handle<::VkQueue>;
          
          field::adapter::single<instance_handle_type> const instance; //< vulkan instance
          field::adapter::single<adapter_handle_type> const  physical; //< adapter
          field::adapter::single<device_handle_type> const   logical;  //< device
          field::adapter::single<queue_handle_type> const    queue;    //< device queue
          
          explicit device();
          virtual ~device();
          
        private:

          instance_handle_type instance_;
          adapter_handle_type  physical_;
          device_handle_type   logical_;
          queue_handle_type    queue_;
          
          instance_handle_type const& cb_get_instance() const;
          instance_handle_type        cb_set_instance(instance_handle_type const&);
          device_handle_type const&   cb_get_logical () const;
          device_handle_type          cb_set_logical (device_handle_type const&);
          adapter_handle_type const&  cb_get_physical() const;
          adapter_handle_type         cb_set_physical(adapter_handle_type const&);
          queue_handle_type const&    cb_get_queue   () const;
          queue_handle_type           cb_set_queue   (queue_handle_type const&);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace context {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_CONTEXT_DEVICE_HPP)
