#pragma once

#include <stdint.h>
#include <array>
#include <utility>


//! Static estimation of std::array container size
// Declare a generic template (which is called initially)
template <size_t dim, class Array>
struct static_size;

// specialization for std::array and first dimension
// creates a struct with a static member "value = N"
template <class T, size_t N>
struct static_size<0, std::array<T, N>> : std::integral_constant<size_t, N> {};

// specialization for std::array and dimension > 0 -> recurse down in dim
template <size_t dim, class InnerArray, size_t N>
struct static_size<dim, std::array<InnerArray, N>> : static_size<dim - 1, InnerArray> {};

