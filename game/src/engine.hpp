#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include "common.hpp"
#include "validation.hpp"

class Engine
{
private:
    VkAllocationCallbacks* allocator;
    bool isSDLInitialized;
    SDL_Window* window;
    SDL_Renderer* windowRenderer;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
    Validation validation;

public:
    Engine();
    ~Engine();

private:
    DELETE_COPY_MOVE(Engine);

public:
    void release() noexcept;

private:
    bool initializeSDL();
    bool createWindow();
    bool createWindowRenderer();

    VkApplicationInfo getApplicationInfo() const;
    bool instanceHasLayers(const std::vector<const char*>& requiredLayers) const;
    bool hasWaylandSupport() const;
    bool createInstance();

    bool setupValidation();

    bool createSurface();

    std::vector<VkPhysicalDevice> getPhysicalDevices() const;
    bool isPhysicalDeviceSuitable(VkPhysicalDevice device) const;
    bool pickPhysicalDevice();
    bool createLogicalDevice();

    void clearScreen();

    bool processEvents();
    void update();
    void render();

public:
    bool create();
    void run();
};

#endif /* ENGINE_HPP */
