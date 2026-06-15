#ifndef COMMON_HPP
#define COMMON_HPP

#define APP_COLOR_RESET     "\033[0m"

#define APP_COLOR_BLACK     "\033[0;30m"
#define APP_COLOR_GRAY      "\033[1;30m"
#define APP_COLOR_RED       "\033[0;31m"
#define APP_COLOR_GREEN     "\033[0;32m"
#define APP_COLOR_ORANGE    "\033[0;33m"
#define APP_COLOR_YELLOW    "\033[1;33m"
#define APP_COLOR_BLUE      "\033[0;34m"
#define APP_COLOR_MAGENTA   "\033[0;35m"
#define APP_COLOR_CYAN      "\033[0;36m"
#define APP_COLOR_WHITE     "\033[0;37m"



#define LOG_INFO(msg, ...) \
    std::printf(APP_COLOR_WHITE msg APP_COLOR_RESET "\n", ##__VA_ARGS__)

#define LOG_VERBOSE(msg, ...) \
    std::printf(APP_COLOR_GRAY msg APP_COLOR_RESET "\n", ##__VA_ARGS__)

#define LOG_WARNING(msg, ...) \
    std::printf(APP_COLOR_YELLOW msg APP_COLOR_RESET "\n", ##__VA_ARGS__)

#define LOG_ERROR(msg, ...) \
    std::printf(APP_COLOR_RED msg APP_COLOR_RESET "\n", ##__VA_ARS__)

#define LOG_FATAL(msg, ...) \
    std::printf(APP_COLOR_RED msg APP_COLOR_RESET "\n", ##__VA_ARGS__)



#define DELETE_COPY(Class) \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete

#define DELETE_MOVE(Class) \
    Class(Class&&) noexcept = delete; \
    Class& operator=(Class&&) noexcept = delete

#define DELETE_COPY_MOVE(Class) \
    DELETE_COPY(Class); \
    DELETE_MOVE(Class)



#endif /* COMMON_HPP */
