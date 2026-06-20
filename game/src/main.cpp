#include "common.hpp"
#include "application.hpp"

static Application app;

int main(int argc, char** argv)
{
    std::cout << "Starting PipeGame Vulkan application..." << std::endl;

    app.processArguments(argc, argv);
    app.start();

    return 0;
}
