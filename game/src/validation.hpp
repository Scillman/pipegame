#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include "common.hpp"

class Validation
{
private:
    PFN_vkCreateDebugUtilsMessengerEXT pfnCreateMessenger;
    PFN_vkDestroyDebugUtilsMessengerEXT pfnDestroyMessenger;

    VkAllocationCallbacks *allocator;
    VkInstance instance;
    VkDebugUtilsMessengerEXT messenger;

    VkDebugUtilsMessengerCreateInfoEXT createInfo { };

    bool enabled;

public:
    Validation();
    ~Validation();

private:
    DELETE_COPY_MOVE(Validation);

public:
    void release() noexcept;

public:
    inline bool isEnabled() const noexcept
    {
        return this->enabled;
    }
    void enable();

    const char* getValidationLayer() const noexcept
    {
        return "VK_LAYER_KHRONOS_validation";
    }

    const char* getValidationExtension() const noexcept
    {
        return VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    }

    const VkDebugUtilsMessengerCreateInfoEXT& getCreateInfo() const noexcept
    {
        return this->createInfo;
    }

public:
    bool getFunctionAddresses();
    bool create(VkInstance instance, VkAllocationCallbacks *allocator);

};

#endif /* VALIDATION_HPP */
