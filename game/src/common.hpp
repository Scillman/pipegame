#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <assert.h>

#define VK_USE_PLATFORM_WAYLAND_KHR
#include <vulkan/vulkan.h>
#include <wayland-client.h>



#define APP_COLOR_RESET     "\033[0m"

#define APP_COLOR_BLACK     "\033[0;30m"
#define APP_COLOR_GRAY      "\033[1;30m"
#define APP_COLOR_RED       "\033[0;31m"
#define APP_COLOR_GREEN     "\033[0;32m"
#define APP_COLOR_ORANGE    "\033[0;33m"
#define APP_COLOR_YELLOW    "\033[1;33m"
#define APP_COLOR_BLUE      "\033[0;34m"
#define APP_COLOR_MAGENTA   "\033[0;35m"
#define APP_COLOR_CYAN      "\033[0;36m"
#define APP_COLOR_WHITE     "\033[0;37m"



#define LOG(msg, prefix, color, ...) \
    std::printf(color "[" prefix "] " msg "\n", ##__VA_ARGS__)

#define LOG_INFO(msg, ...) \
    LOG(msg, "I", APP_COLOR_WHITE, ##__VA_ARGS__)

#define LOG_VERBOSE(msg, ...) \
    LOG(msg, "V", APP_COLOR_GRAY, ##__VA_ARGS__)

#define LOG_WARNING(msg, ...) \
    LOG(msg, "W", APP_COLOR_YELLOW, ##__VA_ARGS__)

#define LOG_ERROR(msg, ...) \
    LOG(msg, "E", APP_COLOR_RED, ##__VA_ARGS__)

#define LOG_FATAL(msg, ...) \
    LOG(msg, "F", APP_COLOR_RED, ##__VA_ARGS__)



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



#define VK_CHECK(call) \
    if (VK_SUCCESS != call) { \
        LOG_FATAL("Vulkan error at %s: %i", __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    }



#endif /* COMMON_HPP */
