#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "common.hpp"

class Window
{
private:
    wl_display* display;
    wl_surface* surface;
    wl_compositor* compositor;
    wl_shell* shell;
    int width, height;

public:
    Window();
    ~Window();

private:
    DELETE_COPY_MOVE(Window);

public:
    void create(int width, int height);

public:
    inline wl_display* get_display() const noexcept
    {
        return this->display;
    }

    inline wl_surface* get_surface() const noexcept
    {
        return this->surface;
    }
};

#endif /* WINDOW_HPP */
