#include "common.hpp"
#include "application.hpp"

int main(int argc, char** argv)
{
    std::cout << "Starting PipeGame Vulkan application..." << std::endl;

    Application app;
    app.processArguments(argc, argv);
    app.start();
//    app.release();

    return 0;
}
