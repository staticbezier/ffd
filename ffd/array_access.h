#pragma once

#include <cstddef>
#include <iostream>


template <typename T>
constexpr auto get(const T& x, std::size_t i) {
    return x[i]; 
}

template <typename T, typename... Is>
constexpr auto get(const T& x, std::size_t i, Is... is) {
    return get(x[i], is...);
}
