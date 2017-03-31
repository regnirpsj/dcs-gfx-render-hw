// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/queue.hpp                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RNEDER_VULKAN_QUEUE_HPP)

#define HUGH_RNEDER_VULKAN_QUEUE_HPP

// includes, system

#include <vector>

// includes, project

#include <hugh/render/vulkan/context/device.hpp>
#include <hugh/render/vulkan/handle.hpp>

namespace hugh {

  namespace render {

    namespace vulkan {

      class command_buffer;
      class fence;
      class semaphore;
      
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_RENDER_VULKAN_EXPORT queue : public handle<::VkQueue> {

      public:

        enum class semaphore_type {
          waitfor, signal
        };
        
        explicit queue(context::device const&);
        explicit queue(handle<::VkDevice> const&);
        // virtual ~queue();
        
        void add(command_buffer*);
        void add(semaphore*, semaphore_type);
        void add(fence*);
        
        void submit();
        
      private:

        using command_buffer_list_type = std::vector<command_buffer>;
        using fence_list_type          = std::vector<fence>;
        using semaphore_list_type      = std::vector<semaphore>;
        
        command_buffer_list_type command_buffer_list_;
        fence_list_type          fence_list_;
        semaphore_list_type      semaphores_to_wait_for_;
        semaphore_list_type      semaphores_to_signal_;
        
      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RNEDER_VULKAN_QUEUE_HPP)
