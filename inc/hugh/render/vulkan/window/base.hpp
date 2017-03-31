// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/window/base.hpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_VULKAN_WINDOW_BASE_HPP)

#define HUGH_VULKAN_WINDOW_BASE_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/vulkan/export.h>
#include <hugh/render/window/base.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {

      namespace window {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_VULKAN_EXPORT base : public render::window::base {

        public:

          explicit base();
          virtual ~base();

          virtual void render(unsigned /* #frames */);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace window {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_VULKAN_WINDOW_BASE_HPP)
