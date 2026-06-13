#include "Window.hpp"

Window::Window() :
    display(nullptr),
    surface(nullptr),
    compositor(nullptr),
    shell(nullptr),
    width(640),
    height(480)
{

}

Window::~Window()
{
    if (this->display != nullptr) {
        wl_display_disconnect(this->display);
    }
}

void Window::create(int width, int height)
{
    this->width = width;
    this->height = height;

    this->display = wl_display_connect(nullptr);
    if (this->display == nullptr) {
        std::cerr << "Failed to connect to Wayland display" << std::endl;
        exit(EXIT_FAILURE);
    }

    wl_registry* registry = wl_display_get_registry(this->display);
    // TODO: register globals
    UNUSED(registry);

    wl_display_roundtrip(this->display);
}
