// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/window/xcb.hpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_VULKAN_WINDOW_XCB_HPP)

#define HUGH_VULKAN_WINDOW_XCB_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/vulkan/window/base.hpp>
#include <hugh/platform/xcb/window.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {

      namespace window {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_VULKAN_EXPORT xcb : public window::base,
                                              public platform::xcb::window::simple {

        public:

          using rect = platform::window::rect;
          
          explicit xcb(std::string const& /* title   */,
                       rect const&        /* rect    */ = rect::dflt_rect,
                       std::string const& /* display */ = std::string());
          virtual ~xcb();

          virtual void print_on(std::ostream&) const;
          
        };

        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace window {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_VULKAN_WINDOW_XCB_HPP)
