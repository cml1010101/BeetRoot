#ifndef X86_64_SERIAL_LOGGER_HPP
#define X86_64_SERIAL_LOGGER_HPP
#include <core/Logger.hpp>
#include <arch/x86_64/io/SerialPort.hpp>
namespace serial
{
    class SerialLogger : public core::Logger
    {
    private:
        arch::x86_64::io::SerialPort port;
        bool hasInitializedPort;
        void write(const String& message);
    public:
        SerialLogger(klib::uint16_t port);
        void log(Level level, const String &message) override;
        void debug(const String &message) override;
        void info(const String &message) override;
        void warning(const String &message) override;
        void error(const String &message) override;
        void fatal(const String &message) override;
    };
}
#endif