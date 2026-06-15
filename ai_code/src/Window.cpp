#include <iostream>
#include "Window.hpp"

Window::Window() :
    initialized(false),
    window(NULL)
{

}

Window::~Window()
{
    if (this->window != NULL) {
        SDL_DestroyWindow(this->window);
    }

    if (this->initialized == true) {
        SDL_Quit();
    }
}

void
Window::initializeSDL()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: "
                  << SDL_GetError()
                  << '\n';
        exit(EXIT_FAILURE);
    }

    this->initialized = true;
}

void
Window::createSDLWindow(int width, int height, const char* title)
{
    this->window = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    if (this->window == NULL) {
        std::cerr << "Window creation failed: "
                  << SDL_GetError()
                  << '\n';

        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

Window
Window::create(int width, int height, const char* title)
{
    Window window;

    window.initializeSDL();
    window.createSDLWindow(width, height, title);

    return window;
}

void
Window::run()
{
    bool running = true;
    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        SDL_Delay(16);
    }
}
