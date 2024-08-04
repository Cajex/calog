/*
 * Created by Joges on 04.08.2024.
 */ 
#pragma once
#include "string"

namespace calog {
    namespace fmt {
        template<typename T>
        std::string format(const std::string &fmt, const T &value);

        template<typename T, typename... Args>
        std::string format(const std::string &fmt, const T &value, const Args&... arguments);

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
        ERROR,
        DEBUG,
    };

    struct CalogContext {
        std::string format = " | {TIME} | {PROFILE} | {MESSAGE}";
    };

    void init();
}
