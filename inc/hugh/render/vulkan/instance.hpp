// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/instance.hpp                                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_INSTANCE_HPP)

#define HUGH_RENDER_VULKAN_INSTANCE_HPP

// includes, system

#include <string>          // std::string
#include <vector>          // std::vector<>
#include <vulkan/vulkan.h> // [V|v]k_*

// includes, project

#include <hugh/render/vulkan/export.h>
#include <hugh/render/vulkan/handle.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_RENDER_VULKAN_EXPORT instance : public handle<::VkInstance> {

      public:

        using string_list_type = std::vector<std::string>;
        
        explicit instance(string_list_type const&    /* enabled layers     */ = string_list_type(),
                          string_list_type const&    /* enabled extensions */ = string_list_type(),
                          ::VkApplicationInfo const* /* app/engine info    */ = nullptr);
        virtual ~instance();

      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_INSTANCE_HPP)
