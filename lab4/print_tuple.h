#pragma once
#include <iostream>
#include <tuple>

template <std::size_t Index, typename... Args>
struct TuplePrinter {
    static void print(std::ostream& os, const std::tuple<Args...>& t) {
        TuplePrinter<Index - 1, Args...>::print(os, t);
        os << ", " << std::get<Index>(t);
    }
};

template <typename... Args>
struct TuplePrinter<0, Args...> {
    static void print(std::ostream& os, const std::tuple<Args...>& t) {
        os << std::get<0>(t);
    }
};

template <typename... Args>
auto operator<<(std::ostream& os, const std::tuple<Args...>& t) -> std::ostream& {
    os << "(";
    if constexpr (sizeof...(Args) > 0) {
        TuplePrinter<sizeof...(Args) - 1, Args...>::print(os, t);
    }
    os << ")";
    return os;
}