// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/vulkan/instance/base.cpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/vulkan/instance/base.hpp"

// includes, system

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error, std::runtime_error

// includes, project

#include <hugh/render/vulkan/io.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace render {
    
    namespace vulkan {

      namespace instance {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        base::base(string_list_type const&    a1,
                   string_list_type const&    a2, 
                   string_list_type const&    b1,
                   string_list_type const&    b2,
                   ::VkApplicationInfo const* c)
          : handle<::VkInstance>(::vkDestroyInstance)
        {
          TRACE("hugh::render::vulkan::instance::base::base");

          ::VkApplicationInfo ai = { };

          if (nullptr != c) {
            ai = *c;
          }

          ai.sType         = VK_STRUCTURE_TYPE_APPLICATION_INFO;
          ai.pEngineName   = "hugh-render-vulkan";
          ai.engineVersion = VK_MAKE_VERSION(1, 0, 0);
          ai.apiVersion    = VK_API_VERSION_1_0;

          ::VkInstanceCreateInfo ici = { };
        
          ici.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
          ici.pApplicationInfo = &ai;

          std::vector<char const*> layer;

          for (auto const& l : a1) {
            layer.push_back(l.c_str());
          }
          
          for (auto const& l : a2) {
            layer.push_back(l.c_str());
          }
        
          ici.ppEnabledLayerNames = layer.data();
          ici.enabledLayerCount   = layer.size();

          std::vector<char const*> extensions;

          for (auto const& e : b1) {
            extensions.push_back(e.c_str());
          }
        
          for (auto const& e : b2) {
            extensions.push_back(e.c_str());
          }

          ici.ppEnabledExtensionNames = extensions.data();
          ici.enabledExtensionCount   = extensions.size();
        
          VkResult const result(::vkCreateInstance(&ici, nullptr, &object_));
            
          if (VK_SUCCESS != result) {
            std::ostringstream ostr;

            ostr << "'vkCreateInstance' failed (" << result << ")!";
              
            std::runtime_error(ostr.str());
          }
        }
      
        /* virtual */
        base::~base()
        {
          TRACE("hugh::render::vulkan::instance::base::~base");
        }      

      } // namespace instance {
      
    } // namespace vulkan {

  } // namespace render {
  
} // namespace hugh {
