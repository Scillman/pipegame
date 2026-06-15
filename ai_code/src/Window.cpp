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

Window
Window::create(int width, int height, const char* title)
{
    Window window;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init failed: "
                  << SDL_GetError()
                  << '\n';
        exit(EXIT_FAILURE);
    }

    window.window = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    if (window.window == NULL) {
        std::cerr << "Window creation failed: "
                  << SDL_GetError()
                  << '\n';

        SDL_Quit();
        exit(EXIT_FAILURE);
    }

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
