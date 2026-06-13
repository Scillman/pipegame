#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "common.hpp"

class Device
{
private:
    VkInstance instance;
    VkSurfaceKHR surface;

    VkPhysicalDevice physical_device;
    VkDevice logical_device;

public:
    Device(VkInstance instance, VkSurfaceKHR surface);
    ~Device();

private:
    DELETE_COPY_MOVE(Device);

public:
    inline operator VkDevice() const noexcept
    {
        return this->logical_device;
    }

    inline explicit operator VkPhysicalDevice() const noexcept
    {
        return this->physical_device;
    }

private:
    std::vector<VkPhysicalDevice> getPhysicalDevices() const;
    bool isSuitableDevice(VkPhysicalDevice device) const;
    void pickPhysicalDevice();
    void createLogicalDevice();

public:
    void create();
};

#endif /* DEVICE_HPP */
