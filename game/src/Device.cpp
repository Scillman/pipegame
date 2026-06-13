#include "Device.hpp"

Device::Device(VkInstance instance, VkSurfaceKHR surface) :
    instance(instance),
    surface(surface),
    physical_device(VK_NULL_HANDLE),
    logical_device(VK_NULL_HANDLE)
{

}

Device::~Device()
{
    if (this->logical_device != VK_NULL_HANDLE)
    {
        vkDestroyDevice(this->logical_device, nullptr);
    }
}

std::vector<VkPhysicalDevice>
Device::getPhysicalDevices() const
{
    uint32_t count = 0u;
    VK_CHECK(vkEnumeratePhysicalDevices(this->instance, &count, nullptr));

    if (count == 0u)
    {
        std::cerr << "No Vulkan-compatible devices found" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<VkPhysicalDevice> devices(count);
    VK_CHECK(vkEnumeratePhysicalDevices(this->instance, &count, devices.data()));
    return devices;
}

void
Device::pickPhysicalDevice()
{
    std::vector<VkPhysicalDevice> devices = this->getPhysicalDevices();

    for (const VkPhysicalDevice& device: devices)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);

        std::cout << "Found device: " << properties.deviceName << std::endl;

        // TODO: pick dedicated GPU
        this->physical_device = device;
        break;
    }

    if (this->physical_device == VK_NULL_HANDLE)
    {
        std::cerr << "No suitable Vulkan device found" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void
Device::createLogicalDevice()
{
    VkDeviceCreateInfo device_create_info { };
    device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    VK_CHECK(vkCreateDevice(this->physical_device, &device_create_info, nullptr, &(this->logical_device)));
}

void
Device::create()
{
    this->pickPhysicalDevice();
    this->createLogicalDevice();
}
