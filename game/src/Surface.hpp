#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "common.hpp"
#include "Window.hpp"
#include "Instance.hpp"

class Surface
{
private:
    VkInstance instance;
    VkSurfaceKHR surface;

public:
    Surface(Instance& instance);
    ~Surface();

private:
    DELETE_COPY_MOVE(Surface);

public:
    inline operator VkSurfaceKHR() const noexcept
    {
        return this->surface;
    }

    void create(const Window& window);
};

#endif /* SURFACE_HPP */
