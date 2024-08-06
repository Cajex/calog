/*
 * Created by Joges on 04.08.2024.
 */ 
#pragma once
#include "string"

namespace calog {
    namespace fmt {
        template<typename T, typename... Args>
        std::string format(const std::string &fmt, const T &value, const Args&... arguments);

        template<typename T>
        std::string format(const std::string &fmt, const T &value);

        std::string format(const std::string &fmt);

        std::string replace(std::string fmt, const std::string& source, const std::string& target);
    }

    namespace color {
        struct Color {
            int r;
            int g;
            int b;
        };

        std::string get(const Color& color, const std::string& text);

    }

    enum FormatComponent {
        TIME,
        PROFILE,
        MESSAGE,
    };

    enum FormatProfile {
        INFO,
        WARN,
        ERRO,
        DEBUG,
    };

    struct CalogContext {
        std::string format = " | {TIME} | {PROFILE} | {MESSAGE}";
        FormatProfile profile;
    };

    void init();

    std::string toString(FormatComponent);

    std::string toString(FormatProfile);

    FormatComponent fromStringToComponent(const std::string& string);

    FormatProfile fromStringToProfile(const std::string& string);

    std::string getComponent(FormatComponent component);

    CalogContext& getFormatContext();

    void setProfile(FormatProfile profile);

    void clear();

    void log(const std::string& fmt);

    template<typename T>
    void log(const std::string& fmt, const T& value);

    template<typename T, typename... Args>
    void log(const std::string& fmt, const T& value, const Args&... arguments);
}
