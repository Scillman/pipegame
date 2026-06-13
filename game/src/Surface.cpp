#include "Surface.hpp"

Surface::Surface(Instance& instance) :
    instance(instance),
    surface(VK_NULL_HANDLE)
{

}

Surface::~Surface()
{
    if (this->surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
    }
}

void
Surface::create(const Window& window)
{
    VkWaylandSurfaceCreateInfoKHR create_info { };

    create_info.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    create_info.display = window.get_display();
    create_info.surface = window.get_surface();

    VK_CHECK(vkCreateWaylandSurfaceKHR(this->instance, &create_info, nullptr, &(this->surface)));
}
