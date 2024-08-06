/*
 * Created by Joges on 04.08.2024.
 */ 
#include "calog.h"

inline calog::CalogContext formatContext;

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
        case INFO: return color::get({67, 188, 122}, "INFO");
        case WARN: return color::get({253, 171, 131}, "WARN");
        case DEBUG: return color::get({255, 111, 0}, "DEBUG");
        default: return color::get({244, 67, 96}, "ERROR");
    }

}

calog::FormatComponent calog::fromStringToComponent(const std::string &string) {
    static const std::unordered_map<std::string, FormatComponent> map = {
        {"TIME", TIME},
        {"PROFILE", PROFILE},
        {"MESSAGE", MESSAGE},
    };
    const auto item = map.find(string);
    return item->second;
}

calog::FormatProfile calog::fromStringToProfile(const std::string &string) {
    static const std::unordered_map<std::string, FormatProfile> map = {
        {"INFO", INFO},
        {"WARN", WARN},
        {"ERRO", ERRO},
        {"DEBUG", DEBUG},
    };
    const auto item = map.find(string);
    return item->second;
}

std::string calog::getComponent(const FormatComponent component) {
    switch (component) {
        case TIME: {
            time_t rawtime;
            time(&rawtime);
            const tm *timeinfo = localtime(&rawtime);
            char buffer[9];
            strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
            return std::string{buffer};
        }
        default: return "";
    }
}

calog::CalogContext& calog::getFormatContext() { return formatContext; }

void calog::setProfile(const FormatProfile profile) {
    formatContext.profile = profile;
}

void calog::clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void calog::log(const std::string& fmt) {
    auto format = formatContext.format;
    format = fmt::replace(format, "{TIME}", getComponent(TIME));
    format = fmt::replace(format, "{PROFILE}", toString(formatContext.profile));
    format = fmt::replace(format, "{MESSAGE}", fmt);
    std::cout << format << "\n";
}

template<typename T>
void calog::log(const std::string& fmt, const T& value) {
    log(fmt::format(fmt, value));
}

template<typename T, typename... Args>
void calog::log(const std::string& fmt, const T& value, const Args&... arguments) {
    const auto output = fmt::format(fmt, value);
    log(output, arguments...);
}