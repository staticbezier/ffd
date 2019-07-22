#pragma once

#include <iostream>
#include <tuple>
#include <utility>
#include "enumerations.h"


namespace detail {
	template <std::size_t ... Is>
	struct accum_mul;
	
	template <>
	struct accum_mul<> : std::integral_constant<std::size_t, 1u>{};
	
	template <std::size_t I, std::size_t ... Is>
	struct accum_mul<I, Is...> : std::integral_constant<std::size_t, I * accum_mul<Is...>::value>{};
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <typename Seq, typename Res = std::tuple<>>
	struct coeff;
	
	template <typename Res>
	struct coeff<std::index_sequence<>, Res> { using type = Res; };

	template <std::size_t I, std::size_t ... Is, typename ... TRes>
	struct coeff<std::index_sequence<I, Is...>, std::tuple<TRes...>> : coeff<std::index_sequence<Is...>, std::tuple<TRes..., accum_mul<Is...>>> {};
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <std::size_t I, typename coeffs, typename dims, typename Seq>
	struct to_multi_index;
	
	template <std::size_t I, typename coeffs, typename dims, std::size_t... Is>
	struct to_multi_index<I, coeffs, dims, std::index_sequence<Is...>> {
		using type = std::index_sequence<(I / (std::tuple_element<Is, coeffs>::type::value)
		% (std::tuple_element<Is, dims>::type::value))...>;
	};
	
	template <typename Indexes, typename coeffs, typename dims, typename dim_indexes>
	struct to_multi_indexes;
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template <std::size_t... Is, typename coeffs, typename dims, typename dim_indexes>
	struct to_multi_indexes<std::index_sequence<Is...>, coeffs, dims, dim_indexes> {
		using type = std::tuple<typename to_multi_index<Is, coeffs, dims, dim_indexes>::type...>;
	};
};

template <std::size_t...Is>
struct all_indexes {
private:
    using as_seq = std::index_sequence<Is...>;
    using as_tuple = std::tuple<std::integral_constant<std::size_t, Is>...>;
    using dim_index = std::make_index_sequence<sizeof...(Is)>;
    using coeffs = typename detail::coeff<as_seq>::type;
    using elem_count = detail::accum_mul<Is...>;
    using index_seq = std::make_index_sequence<elem_count::value>;
public:
    using type = typename detail::to_multi_indexes<index_seq, coeffs, as_tuple, dim_index>::type;
};

template <std::size_t ... Is>
void print(std::index_sequence<Is...>) {
	std::cout << "Point=";
	const int dummy[] = {0, (std::cout << Is << " ", 0)...};
	(void) dummy;
	std::cout << std::endl;
}
 
template <typename ...Ts>
void print(const std::tuple<Ts...>&) {
	const int dummy[] = {0, (print(Ts{}), 0)...};
	(void) dummy;
}
