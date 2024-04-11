#ifndef CORE_LOGGER_HPP
#define CORE_LOGGER_HPP
#include <klib/base/String.hpp>
namespace core
{
    class Logger
    {
    public:
        using String = klib::String;
        enum class Level
        {
            Debug,
            Info,
            Warning,
            Error,
            Fatal
        };
        virtual void log(Level level, const String &message) = 0;
        virtual void debug(const String &message) = 0;
        virtual void info(const String &message) = 0;
        virtual void warning(const String &message) = 0;
        virtual void error(const String &message) = 0;
        virtual void fatal(const String &message) = 0;
    };
}
#endif