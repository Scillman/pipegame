#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>

class Window
{
private:
    bool initialized;
    SDL_Window* window;

private:
    Window();

public:
    ~Window();

// private:
//     Window(const Window&) = default;
//     Window& operator=(const Window&) = default;

//     Window(Window&&) noexcept = default;
//     Window& operator=(Window&&) noexcept = default;

private:
    void initializeSDL();
    void createSDLWindow(int width, int height, const char* title);

public:
    static Window create(int width, int height, const char* title);
    void run();
};

#endif /* WINDOW_HPP */
