// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/adapter.hpp                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_ADAPTER_HPP)

#define HUGH_RENDER_VULKAN_ADAPTER_HPP

// includes, system

#include <boost/intrusive_ptr.hpp> // boost::intrusive_ptr<>
#include <vulkan/vulkan.h>         // [V|v]k_*

// includes, project

#include <hugh/render/vulkan/instance.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)
      
      class HUGH_RENDER_VULKAN_EXPORT adapter : public handle<::VkPhysicalDevice> {

      public:

        boost::intrusive_ptr<vulkan::instance const> const instance;

        explicit adapter(vulkan::instance* = nullptr);
        virtual ~adapter();        

        
      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_ADAPTER_HPP)
