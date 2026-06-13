#include "common.hpp"
#include "Window.hpp"
#include "Instance.hpp"
#include "Surface.hpp"
#include "Device.hpp"

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    std::cout << "Starting PipeGame Vulkan application..." << std::endl;

    Window window;
    window.create(1280, 720);

    Instance instance;
    instance.create();

    Surface surface(instance);
    surface.create(window);

    Device device(instance, surface);
    device.create();

    return 0;
}
