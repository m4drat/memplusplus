#pragma once

#include <string>

namespace mpp { namespace utils { namespace colours {
    constexpr std::string_view RESET = "\u001b[0m";
    constexpr std::string_view BLACK = "\u001b[30m";
    constexpr std::string_view RED = "\u001b[31m";
    constexpr std::string_view GREEN = "\u001b[32m";
    constexpr std::string_view YELLOW = "\u001b[33m";
    constexpr std::string_view BLUE = "\u001b[34m";
    constexpr std::string_view MAGENTA = "\u001b[35m";
    constexpr std::string_view CYAN = "\u001b[36m";
    constexpr std::string_view WHITE = "\u001b[37m";

    constexpr std::string_view BRIGHT_BLACK = "\u001b[30;1m";
    constexpr std::string_view BRIGHT_RED = "\u001b[31;1m";
    constexpr std::string_view BRIGHT_GREEN = "\u001b[32;1m";
    constexpr std::string_view BRIGHT_YELLOW = "\u001b[33;1m";
    constexpr std::string_view BRIGHT_BLUE = "\u001b[34;1m";
    constexpr std::string_view BRIGHT_MAGENTA = "\u001b[35;1m";
    constexpr std::string_view BRIGHT_CYAN = "\u001b[36;1m";
    constexpr std::string_view BRIGHT_WHITE = "\u001b[37;1m";
}}}