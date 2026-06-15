#include <iostream>
#include "Window.hpp"

Window::Window() :
    initialized(false),
    window(NULL),
    renderer(NULL)
{

}

Window::~Window()
{
    if (this->renderer != NULL) {
        SDL_DestroyRenderer(this->renderer);
        LOG_VERBOSE("Renderer destroyed");
    }

    if (this->window != NULL) {
        SDL_DestroyWindow(this->window);
        LOG_VERBOSE("Window destroyed");
    }

    if (this->initialized == true) {
        SDL_Quit();
        LOG_VERBOSE("SDL_Quit");
    }
}

void
Window::initialize()
{
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
        LOG_FATAL("SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    LOG_INFO("SDL_Init successful");
    this->initialized = true;
}

void
Window::createWindow(int width, int height, const char* title)
{
    this->window = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    if (this->window == NULL) {
        LOG_FATAL("Window creation failed: %s", SDL_GetError());

        SDL_Quit();
        LOG_VERBOSE("SDL_Quit");

        exit(EXIT_FAILURE);
    }

    LOG_INFO("Window creation successful");
}

void
Window::createRenderer()
{
    this->renderer = SDL_CreateRenderer(this->window, nullptr);

    if (this->renderer == NULL) {
        LOG_FATAL("Renderer creation failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Renderer creation successful");
}

Window
Window::create(int width, int height, const char* title)
{
    Window window;

    window.initialize();
    window.createWindow(width, height, title);
    window.createRenderer();

    return window;
}

void
Window::clearScreen()
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void
Window::processEvents(bool& running)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;

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
}

void
Window::update()
{

}

void
Window::render()
{
    this->clearScreen();
}

void
Window::run()
{
    bool running = true;

    do {
        this->processEvents(running);
        this->update();
        this->render();
    } while (running);
}
