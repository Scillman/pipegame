#include "Window.hpp"

int main()
{
    Window window = Window::create(1280, 720, "Pipegame");
    window.run();
    return 0;
}
