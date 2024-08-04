/*
 * Created by Joges on 04.08.2024.
 */ 
#include "calog.h"
#include <sstream>
#if __WIN32__
#include <windows.h>
#endif

template<typename T>
std::string calog::fmt::format(const std::string &fmt, const T &value) {
    std::ostringstream ostringstream;
    ostringstream << value;
    const auto pos = fmt.find("{}");
    if (pos == std::string::npos) return fmt;
    std::string result = fmt;
    result.replace(pos, 2, ostringstream.str());
    return result;
}

template<typename T, typename... Args>
std::string calog::fmt::format(const std::string &fmt, const T &value, const Args&... arguments) {
    std::string result = format(fmt, value);
    return format(result, arguments...);
}

std::string calog::fmt::format(const std::string &fmt) {
    return fmt;
}

std::string calog::fmt::replace(std::string fmt, const std::string& source, const std::string& target) {
    bool breakOut = true;
    while (breakOut)
        if (const auto pos = fmt.find(source); pos == std::string::npos) breakOut = false;
        else fmt = fmt.replace(pos, source.size(), target);
    return fmt;
}

std::string calog::color::get(const Color& color, const std::string& text) {
    return fmt::format("\033[38;2;{};{};{}m{}\033[0m", color.r, color.g, color.b, text);
}

void calog::init() {
#if __WIN32__
    const auto hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

std::string calog::toString(const FormatComponent e) {
    switch (e) {
        case TIME: return "TIME";
        case PROFILE: return "PROFILE";
        case MESSAGE: return "MESSAGE";
        default: return "";
    }
}

std::string calog::toString(const FormatProfile e) {
    switch (e) {
        case INFO: return "INFO";
        case WARN: return "WARN";
        case DEBUG: return "DEBUG";
        default: return "ERROR";
    }

}

calog::FormatComponent calog::fromStringToComponent(const std::string &string) {
    return PROFILE;
}

calog::FormatProfile calog::fromStringToProfile(const std::string &string) {
    return FormatProfile::WARN;
}
