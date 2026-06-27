#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "common.hpp"
#include "engine.hpp"

#define APP_LOG_LEVEL_NONE      0
#define APP_LOG_LEVEL_INFO      (1 << 0)
#define APP_LOG_LEVEL_VERBOSE   (1 << 1)
#define APP_LOG_LEVEL_WARNING   (1 << 2)
#define APP_LOG_LEVEL_ERROR     (1 << 3)
#define APP_LOG_LEVEL_FATAL     (1 << 4)

class Application
{
private:
    struct {
        int log_level = 0;
    } settings;
    Engine engine;

public:
    Application();
    ~Application();

private:
    DELETE_COPY_MOVE(Application);

public:
    void release() noexcept;

private:
    void printUsageMessage(const char* binName) const;

    bool applyLogLevel(const char* value, size_t len);
    bool setLogLevel(const char* value);

public:
    bool processArguments(int argc, char** argv);

    int start();
};

#endif /* APPLICATION_HPP */
