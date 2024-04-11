#include <serial/SerialLogger.hpp>
using namespace serial;
using namespace klib;
void SerialLogger::write(const String& string)
{
    if (!hasInitializedPort)
    {
        port.init();
        hasInitializedPort = true;
    }
    for (size_t i = 0; i < string.length(); i++)
    {
        port.write(string[i]);
    }
}
SerialLogger::SerialLogger(uint16_t port) : port(port)
{
    hasInitializedPort = false;
}
void SerialLogger::log(SerialLogger::Level level, const String& message)
{
    switch (level)
    {
    case Level::Info:
        info(message);
        break;
    case Level::Warning:
        warning(message);
        break;
    case Level::Debug:
        debug(message);
        break;
    case Level::Error:
        error(message);
        break;
    case Level::Fatal:
        fatal(message);
        break;
    }
}
void SerialLogger::info(const String& message)
{
    write("[Info]: ");
    write(message);
    write("\n");
}
void SerialLogger::debug(const String& message)
{
    write("[Debug]: ");
    write(message);
    write("\n");
}
void SerialLogger::warning(const String& message)
{
    write("[Warning]: ");
    write(message);
    write("\n");
}
void SerialLogger::error(const String& message)
{
    write("[Error]: ");
    write(message);
    write("\n");
}
void SerialLogger::fatal(const String& message)
{
    write("[Fatal]: ");
    write(message);
    write("\n");
}