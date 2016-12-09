// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/instance/base.hpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_INSTANCE_BASE_HPP)

#define HUGH_RENDER_VULKAN_INSTANCE_BASE_HPP

// includes, system

#include <string> // std::string
#include <vector> // std::vector<>

// includes, project

#include <hugh/render/vulkan/export.h>
#include <hugh/render/vulkan/handle.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {

      namespace instance {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_VULKAN_EXPORT base : public handle<::VkInstance> {

        public:

          virtual ~base();

        protected:

          using string_list_type = std::vector<std::string>;
          
          explicit base(string_list_type const&    /* default layers     */ = string_list_type(),
                        string_list_type const&    /* enabled layers     */ = string_list_type(),
                        string_list_type const&    /* default extensions */ = string_list_type(),
                        string_list_type const&    /* enabled extensions */ = string_list_type(),
                        ::VkApplicationInfo const* /* app/engine info    */ = nullptr);

        };
      
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace instance {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_INSTANCE_BASE_HPP)
