#include "validation.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
)
{
    UNUSED(messageSeverity);
    UNUSED(messageType);
    //UNUSED(pCallbackData);
    UNUSED(pUserData);

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

Validation::Validation() :
    allocator(nullptr),
    instance(VK_NULL_HANDLE),
    messenger(VK_NULL_HANDLE),
    enabled(false)
{

}

Validation::~Validation()
{
    this->release();
}

void
Validation::release() noexcept
{
    if (this->enabled && VK_NULL_HANDLE != this->messenger) {
        this->pfnDestroyMessenger(
            this->instance,
            messenger,
            this->allocator
        );
        this->messenger = VK_NULL_HANDLE;
    }
}

void
Validation::enable()
{
    this->enabled = true;
}

bool
Validation::getFunctionAddresses()
{
    this->pfnCreateMessenger = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(this->instance, "vkCreateDebugUtilsMessengerEXT");
    if (nullptr == this->pfnCreateMessenger) {
        LOG_FATAL("vkCreateDebugUtilsMessengerEXT not found");
        //throw new std::runtime_error("vkCreateDebugUtilsMessengerEXT not found");
        return false;
    }

    this->pfnDestroyMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(this->instance, "vkDestroyDebugUtilsMessengerEXT");
    if (nullptr == this->pfnDestroyMessenger) {
        LOG_FATAL("vkDestroyDebugUtilsMessengerEXT not found");
        //throw new std::runtime_error("vkDestroyDebugUtilsMessengerEXT not found");
        return false;
    }

    return true;
}

bool
Validation::create(VkInstance instance, VkAllocationCallbacks *allocator)
{
    if (!this->enabled) {
        return true;
    }

    this->allocator = allocator;
    this->instance = instance;

    if (!this->getFunctionAddresses()) {
        return false;
    }

    this->createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    this->createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    this->createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    this->createInfo.pfnUserCallback = debugCallback;
    this->createInfo.pUserData = this;

    VkResult result = this->pfnCreateMessenger(this->instance, &this->createInfo, this->allocator, &this->messenger);
    VK_CHECK(result);

    return VK_SUCCESS == result;
}
