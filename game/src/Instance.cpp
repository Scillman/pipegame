#include "Instance.hpp"

Instance::Instance() :
    instance(VK_NULL_HANDLE)
{

}

Instance::~Instance()
{
    if (this->instance != VK_NULL_HANDLE) {
        vkDestroyInstance(this->instance, nullptr);
    }
}

VkApplicationInfo
Instance::getAppInfo() const
{
    VkApplicationInfo info { };

    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "PipeGame";
    info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pEngineName = "No Engine";
    info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    info.apiVersion = VK_API_VERSION_1_0;

    return info;
}

bool
Instance::hasWaylandSupport() const
{
    uint32_t count = 0u;
    VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr));

    std::vector<VkExtensionProperties> extensions(count);
    VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data()));

    bool has_wayland_extension = false;
    for (const VkExtensionProperties& extension: extensions) {
        if (strcmp(extension.extensionName, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME) == 0) {
            has_wayland_extension = true;
            break;
        }
    }

    if (!has_wayland_extension) {
        std::cerr << "Wayland surface extension not available" << std::endl;
        exit(EXIT_FAILURE);
    }

    return has_wayland_extension;
}

void
Instance::create()
{
    VkApplicationInfo app_info = this->getAppInfo();

    this->hasWaylandSupport();

    VkInstanceCreateInfo create_info { };
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    const char* required_extensions[] = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
    };

    create_info.enabledExtensionCount = 2;
    create_info.ppEnabledExtensionNames = required_extensions;

    VK_CHECK(vkCreateInstance(&create_info, nullptr, &(this->instance)));
}
