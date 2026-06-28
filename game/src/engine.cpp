#include "engine.hpp"

#define WINDOW_TITLE    "Pipe Game by SimpyGames"
#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720

bool
Engine::QueueFamilyIndices::isComplete() const
{
    return this->graphicsFamily.has_value();
}

Engine::Engine() :
    allocator(VK_NULL_HANDLE),
    isSDLInitialized(false),
    window(NULL),
    windowRenderer(NULL),
    instance(VK_NULL_HANDLE),
    surface(VK_NULL_HANDLE),
    physicalDevice(VK_NULL_HANDLE),
    logicalDevice(VK_NULL_HANDLE)
{
    this->validation.enable();
}

Engine::~Engine()
{
    this->release();
}

void
Engine::release() noexcept
{
    if (VK_NULL_HANDLE != this->logicalDevice) {
        vkDestroyDevice(this->logicalDevice, this->allocator);
        LOG_VERBOSE("Logical device destroyed");
        this->logicalDevice = VK_NULL_HANDLE;
    }

    if (VK_NULL_HANDLE != this->surface) {
        vkDestroySurfaceKHR(this->instance, this->surface, this->allocator);
        LOG_VERBOSE("Render surface destroyed");
        this->surface = VK_NULL_HANDLE;
    }

    this->validation.release();

    if (VK_NULL_HANDLE != this->instance) {
        vkDestroyInstance(this->instance, this->allocator);
        LOG_VERBOSE("Vulkan instance destroyed");
        this->instance = VK_NULL_HANDLE;
    }

    if (NULL != this->windowRenderer) {
        SDL_DestroyRenderer(this->windowRenderer);
        LOG_VERBOSE("Window renderer destroyed");
        this->windowRenderer = NULL;
    }

    if (NULL != this->window) {
        SDL_DestroyWindow(this->window);
        LOG_VERBOSE("Window destroyed");
        this->window = NULL;
    }

    if (this->isSDLInitialized) {
        SDL_Quit();
        LOG_VERBOSE("SDL_Quit called");
        this->isSDLInitialized = false;
    }
}

bool
Engine::initializeSDL()
{
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        LOG_FATAL("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    this->isSDLInitialized = true;

    LOG_INFO("SDL_Init successful");
    return true;
}

bool
Engine::createWindow()
{
    this->window = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN
    );

    if (this->window == NULL) {
        LOG_FATAL("Window creation failed: %s", SDL_GetError());
        return false;
    }

    LOG_INFO("Window creation successful");
    return true;
}

/**
 * NOTE: Can be used to, visually, test if SDL window creation using Wayland is successful.
 */
bool
Engine::createWindowRenderer()
{
    this->windowRenderer = SDL_CreateRenderer(this->window, NULL);

    if (NULL == this->windowRenderer) {
        LOG_FATAL("Window renderer creation failed: %s", SDL_GetError());
        return false;
    }

    LOG_INFO("Window renderer created");
    return true;
}

VkApplicationInfo
Engine::getApplicationInfo() const
{
    VkApplicationInfo info { };

    info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName = "pipegame";
    info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    info.pEngineName = "SimplyGames2D";
    info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    info.apiVersion = VK_API_VERSION_1_0;

    return info;
}

bool
Engine::instanceHasLayers(const std::vector<const char*>& requiredLayers) const
{
    uint32_t count;
    vkEnumerateInstanceLayerProperties(&count, nullptr);

    // NOTE: Allows for quick return, but poor logging
    // if (count < requiredLayers.size()) {
    //     LOG_WARNING("Missing one or more instance layers");
    //     return false;
    // }

    std::vector<VkLayerProperties> layers(count);
    vkEnumerateInstanceLayerProperties(&count, layers.data());

    for (const char* requiredLayer: requiredLayers) {
        bool found = false;

        for (const VkLayerProperties& layer: layers) {
            if (0 == strcmp(requiredLayer, layer.layerName)) {
                found = true;
            }
        }

        if (!found) {
            LOG_WARNING("Missing instance layer %s", requiredLayer);
            return false;
        }
    }

    return true;
}

/**
 * TODO: double-check if SDL already does this for us... it probably does.
 */
bool
Engine::hasWaylandSupport() const
{
    VkResult result;

    uint32_t count = 0u;
    result = vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
    VK_CHECK(result);

    std::vector<VkExtensionProperties> extensions(count);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data());
    VK_CHECK(result);

    bool has_wayland_extension = false;
    for (const VkExtensionProperties& extension: extensions) {
        if (0 == strcmp(extension.extensionName, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME)) {
            has_wayland_extension = true;
            break;
        }
    }

    if (!has_wayland_extension) {
        LOG_ERROR("Wayland surface extension not available");
        return false;
    }

    LOG_INFO("Wayland surface extension detected");
    return has_wayland_extension;
}

bool
Engine::createInstance()
{
    std::vector<const char*> required_layers = { };

    std::vector<const char*> required_extensions = {
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
    };

    if (this->validation.isEnabled()) {
        required_layers.push_back(this->validation.getValidationLayer());
    }

    if (!this->instanceHasLayers(required_layers)) {
        return false;
    }

    if (!this->hasWaylandSupport()) {
        return false;
    }

    VkApplicationInfo app_info = this->getApplicationInfo();

    VkInstanceCreateInfo create_info { };
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    if (this->validation.isEnabled()) {
        required_extensions.push_back(this->validation.getValidationExtension());
    }

    create_info.enabledExtensionCount = static_cast<uint32_t>(required_extensions.size());
    create_info.ppEnabledExtensionNames = required_extensions.data();

    if (required_layers.size() > 0u) {
        create_info.enabledLayerCount = static_cast<uint32_t>(required_layers.size());
        create_info.ppEnabledLayerNames = required_layers.data();
    }

    VkResult result = vkCreateInstance(
        &create_info,
        this->allocator,
        &this->instance
    );
    VK_CHECK(result);

    LOG_INFO("Vulkan instance created");
    return true;
}

bool
Engine::setupValidation()
{
    if (this->validation.isEnabled()) {
        return this->validation.create(this->instance, this->allocator);
    }
    return true;
}

bool
Engine::createSurface()
{
    bool result = SDL_Vulkan_CreateSurface(
        this->window,
        this->instance,
        this->allocator,
        &this->surface
    );

    if (!result) {
        LOG_FATAL("Failed to create render surface");
        return false;
    }

    LOG_INFO("Created render surface");
    return true;
}

std::vector<VkPhysicalDevice>
Engine::getPhysicalDevices() const
{
    VkResult result;
    uint32_t count;

    result = vkEnumeratePhysicalDevices(
        this->instance,
        &count,
        nullptr
    );
    VK_CHECK(result);

    if (count == 0u) {
        return std::vector<VkPhysicalDevice>(0u);
    }

    std::vector<VkPhysicalDevice> devices(count);
    result = vkEnumeratePhysicalDevices(
        this->instance,
        &count,
        devices.data()
    );
    VK_CHECK(result);

    return devices;
}

bool
Engine::isPhysicalDeviceSuitable(VkPhysicalDevice device) const
{
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(device, &properties);

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(device, &features);

    return properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
        && features.geometryShader;
}

bool
Engine::pickPhysicalDevice()
{
    std::vector<VkPhysicalDevice> devices = this->getPhysicalDevices();
    if (0u == devices.size()) {
        LOG_FATAL("No Vulkan compatible devices found");
        return false;
    }

    for (const VkPhysicalDevice& device: devices) {
        if (this->isPhysicalDeviceSuitable(device)) {
            this->physicalDevice = device;
            break;
        }
    }

    if (VK_NULL_HANDLE == this->physicalDevice) {
        LOG_FATAL("No suitable physical device found");
        return false;
    }

    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(this->physicalDevice, &properties);
    LOG_INFO("Using compatible device: %s", properties.deviceName);
    return true;
}

Engine::QueueFamilyIndices
Engine::findQueueFamilies(VkPhysicalDevice device) const
{
    QueueFamilyIndices indices;

    uint32_t count = 0u;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queueFamilies.data());

    uint32_t i =0u;

    for (const VkQueueFamilyProperties& queueFamily: queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.isComplete()) {
            break;
        }

        ++i;
    }

    return indices;
}

bool
Engine::createLogicalDevice()
{
    VkResult result;

    QueueFamilyIndices indices = this->findQueueFamilies(this->physicalDevice);
    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueInfo { };
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueInfo.queueCount = 1u;
    queueInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures features { };

    VkDeviceCreateInfo info { };
    info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    info.pQueueCreateInfos = &queueInfo;
    info.queueCreateInfoCount = 1u;
    info.pEnabledFeatures = &features;

    result = vkCreateDevice(
        this->physicalDevice,
        &info,
        this->allocator,
        &this->logicalDevice
    );
    VK_CHECK(result);

    LOG_INFO("Created logical device");
    return true;
}

bool
Engine::create()
{
    if (!this->initializeSDL()) {
        return false;
    }

    if (!this->createWindow()) {
        return false;
    }

#if 0
    if (!this->createWindowRenderer()) {
        return false;
    }

    return true;
#endif

    if (!this->createInstance()) {
        return false;
    }

    if (!this->setupValidation()) {
        return false;
    }

    if (!this->createSurface()) {
        return false;
    }

    if (!this->pickPhysicalDevice()) {
        return false;
    }

    if (!this->createLogicalDevice()) {
        return false;
    }

    return true;
}

bool
Engine::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                return false;

            case SDL_EVENT_WINDOW_MAXIMIZED:
            case SDL_EVENT_WINDOW_MINIMIZED:
            case SDL_EVENT_WINDOW_RESTORED:
            case SDL_EVENT_WINDOW_RESIZED:
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                break;

            default:
                break;
        }
    }

    return true;
}

void
Engine::clearScreen()
{
    SDL_SetRenderDrawColor(this->windowRenderer, 30, 30, 30, 255);
    SDL_RenderClear(this->windowRenderer);
    SDL_RenderPresent(this->windowRenderer);
}

void
Engine::update()
{

}

void
Engine::render()
{
    this->clearScreen();
}

void
Engine::run()
{
    while (this->processEvents()) {
        this->update();
        this->render();
    }
}
