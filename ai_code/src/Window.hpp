#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL3/SDL.h>
#include "common.hpp"

class Window
{
private:
    bool initialized;
    SDL_Window* window;
    SDL_Renderer* renderer;

private:
    Window();

public:
    ~Window();

// private:
//     DELETE_COPY_MOVE(Window);

private:
    void initialize();
    void createWindow(int width, int height, const char* title);
    void createRenderer();

    void processEvents(bool& running);
    void update();
    void render();

    void clearScreen();

public:
    static Window create(int width, int height, const char* title);
    void run();
};

#endif /* WINDOW_HPP */
