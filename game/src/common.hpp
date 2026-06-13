#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <assert.h>

#define VK_USE_PLATFORM_WAYLAND_KHR
#include <vulkan/vulkan.h>
#include <wayland-client.h>

#define UNUSED(var)  ((void)(var))

#define DELETE_COPY(Class) \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete;

#define DELETE_MOVE(Class) \
    Class(Class&&) noexcept = delete; \
    Class& operator=(Class&&) noexcept = delete;

#define DELETE_COPY_MOVE(Class) \
    DELETE_COPY(Class); \
    DELETE_MOVE(Class)

// Error handling macros
#define VK_CHECK(call) \
    if (VK_SUCCESS != call) { \
        std::cerr << "Vulkan error at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(EXIT_FAILURE); \
    }

#endif /* COMMON_HPP */
