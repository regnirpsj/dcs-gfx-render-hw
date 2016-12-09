// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/instance/visual.hpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_VULKAN_INSTANCE_VISUAL_HPP)

#define HUGH_RENDER_VULKAN_INSTANCE_VISUAL_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/vulkan/instance/base.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {

      namespace instance {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_VULKAN_EXPORT visual : public base {

        public:

          using string_list_type = base::string_list_type;
          
          explicit visual(string_list_type const&    /* enabled layers     */ = string_list_type(),
                          string_list_type const&    /* enabled extensions */ = string_list_type(),
                          ::VkApplicationInfo const* /* app/engine info    */ = nullptr);

          virtual ~visual();
          
        };
      
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace instance {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_INSTANCE_VISUAL_HPP)
