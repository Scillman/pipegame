#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "common.hpp"

class Instance
{
private:
    VkInstance instance;

public:
    Instance();
    ~Instance();

private:
    DELETE_COPY_MOVE(Instance);

private:
    VkApplicationInfo get_app_info() const;
    bool has_wayland_support() const;

public:
    inline operator VkInstance() const noexcept
    {
        return this->instance;
    }

    void create();
};

#endif /* INSTANCE_HPP */
