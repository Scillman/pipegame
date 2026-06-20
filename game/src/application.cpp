#include <cstring>
#include <assert.h>
#include "application.hpp"

Application::Application()
{

}

Application::~Application()
{

}

void
Application::printUsageMessage(const char* binName) const
{
    const char* programName = strrchr(binName, '/');
    if (programName == nullptr) {
        programName = binName;
    } else {
        programName += 1;
    }

    putc('\n', stdout);
    fprintf(stdout, "USAGE: %s <OPTIONS>\n", programName);
    putc('\n', stdout);
    fprintf(stdout, "OPTIONS\n");
    fprintf(stdout, "  -L   --log-level   Set the logging level. (none, info, verbose, warning, error, fatal)\n");
    putc('\n', stdout);
}

bool
Application::applyLogLevel(const char* value, size_t len)
{
#define SET_LOG_VALUE(name, level) \
    if (0 == strncmp(name, value, len)) { \
        this->settings.log_level |= level; \
        printf("Applying log level %i (%.*s)\n", level, static_cast<int>(len), value); \
        return true; \
    }

    if (0 == strncmp("none", value, len)) {
        this->settings.log_level = 0;
        printf("Applying log level %i (none)\n", APP_LOG_LEVEL_NONE);
        return true;
    }

//  SET_LOG_VALUE("none",    APP_LOG_LEVEL_NONE);
    SET_LOG_VALUE("info",    APP_LOG_LEVEL_INFO);
    SET_LOG_VALUE("verbose", APP_LOG_LEVEL_VERBOSE);
    SET_LOG_VALUE("warning", APP_LOG_LEVEL_WARNING);
    SET_LOG_VALUE("error",   APP_LOG_LEVEL_ERROR);
    SET_LOG_VALUE("fatal",   APP_LOG_LEVEL_FATAL);

#undef SET_LOG_LEVEL

    printf("Invalid log level of '%.*s'\n", static_cast<int>(len), value);
    return false;
}

bool
Application::setLogLevel(const char* value)
{
    const char* next = value;
    const char* end = value + strlen(value);
    const char* sep;
    size_t len;

    do
    {
        sep = strchr(next, ',');

        if (sep == nullptr) {
            len = strlen(next);
            return this->applyLogLevel(next, len);
        }

        len = static_cast<size_t>(sep - next);
        if (!this->applyLogLevel(next, len)) {
            return false;
        }
        next = (next + len + 1);
    }
    while (next < end);

    assert(next[0] == '\0');
    return false;
}

bool
Application::processArguments(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i) {
        const char* param = argv[i];

        if (0 == strcmp(param, "--help")) {
            this->printUsageMessage(argv[0]);
            return false;
        }

        if (0 == strcmp(param, "-L") || 0 == strcmp(param, "--log-level")) {
            if (i+1 >= argc) {
                std::cout << "Missing argument for " << param << std::endl;
                return false;
            }

            if (!this->setLogLevel(argv[++i])) {
                std::cout << "Invalid value for parameter " << param << std::endl;
                return false;
            }

            continue;
        }

        printf("Unknown parameter: %s\n", param);
        return false;
    }

    return true;
}

int
Application::start()
{
    if (engine.create()) {
        engine.run();
    }

    return EXIT_SUCCESS;
}
