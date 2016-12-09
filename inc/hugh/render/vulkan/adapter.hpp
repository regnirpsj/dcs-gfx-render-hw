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

#include <hugh/field/adapter/single.hpp>
#include <hugh/field/container.hpp>
#include <hugh/render/vulkan/instance/base.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {
      
      // types, exported (class, enum, struct, union, typedef)
      
      class HUGH_RENDER_VULKAN_EXPORT adapter : public field::container,
                                                public handle<::VkPhysicalDevice> {

      public:

        struct queue_family_t {
          unsigned flags;

          struct {
            signed compute;
            signed graphics;
            signed sparse_binding;
            signed transfer;
          } index;
        };

        field::adapter::single<queue_family_t const> const queue_family; //< queue family
        
        explicit adapter(vulkan::instance::base const&, unsigned = 0);
        virtual ~adapter();

        virtual void print_on(std::ostream&) const;
        
      private:

        queue_family_t queue_family_;

        queue_family_t const& get_cb_queue_family() const;
        queue_family_t        set_cb_queue_family(queue_family_t const&);
        
      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

      HUGH_RENDER_VULKAN_EXPORT std::ostream& operator<<(std::ostream&,
                                                         adapter::queue_family_t const&);
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_VULKAN_ADAPTER_HPP)
