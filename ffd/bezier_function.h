#pragma once

#include <cstddef>
#include <iostream>

#include "array_access.h"
#include "static_size.h"
#include "enumerations.h"
#include "bernstein.h"

#include <array>


namespace detail {	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1) Calculate the current Bernstein polynomial product
	template <size_t Iter>
	struct Iterate {
		template <size_t... Ds>
		struct Dim {
		template<size_t... Is>
		struct ID {
			template <class Inp>
			static auto run(const Inp inp) {
				constexpr std::size_t Ndim = sizeof...(Ds);
				constexpr std::size_t Nind = sizeof...(Is);
				
				constexpr std::array<size_t, Ndim> dims = {{Ds...}};
				constexpr std::array<size_t, Nind> inds = {{Is...}};

				constexpr size_t n = dims[Iter] - 1;
				constexpr size_t k = inds[Iter];
				static_assert(n >= k, "Error in Iterate::Dim::ID::run(): n < k");

				//qDebug() << n << "/" << k << inp[Iter];
				return (
					  bernstein::polynomial<n, k>(inp[Iter])
					* Iterate<Iter-1>::template Dim<Ds...>::template ID<Is...>::template run(inp) // recursion
				);
			}
		};
		};
	};

	template <>
	struct Iterate<0> {
		template <size_t... Ds>
		struct Dim {
		template<size_t... Is>
		struct ID {
			template <class Inp>
			static auto run(const Inp inp) {
				constexpr std::size_t Ndim = sizeof...(Ds);
				constexpr std::size_t Nind = sizeof...(Is);
				
				constexpr std::array<size_t, Ndim> dims = {{Ds...}};
				constexpr std::array<size_t, Nind> inds = {{Is...}};

				constexpr size_t n = dims[0] - 1;
				constexpr size_t k = inds[0];
				static_assert(n >= k, "Error in Iterate::Dim::ID::run(): n < k");

				//qDebug() << "\t" << n << "/" << k << inp[0];
				return bernstein::polynomial<n, k>(inp[0]);
			}
		};
		};
	};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1) Calculate the current Bernstein polynomial product 
// 2) Multiply it with the appropriate control point
	template <size_t... Ds>
	struct Dim {
		template <size_t... Is, class Inp, class Pnts>
		static auto run(Inp inp, Pnts ctrl_points, const std::index_sequence<Is...> &) {
			constexpr std::size_t Ndim = sizeof...(Ds) - 1;
			
			const auto res 
			= Iterate<Ndim>::template Dim<Ds...>::template ID<Is...>::template run<Inp>(inp)
			* get(ctrl_points, Is...); // current control point at the index: "[Is][Is+1][Is...][Is+n]"
			
			//qDebug() << res;
			return res;
		}
	};
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1)
// 2)
// 3)
namespace helper {
	template <std::size_t... Ds> 
	struct Dim {
		template <class Inp, class Points, class ...Ts>
		static auto run(const Inp &inp, const Points &ctrl_points, const std::tuple<Ts...>&) {
			return (detail::Dim<Ds...>::template run(inp, ctrl_points, Ts{}) + ...);
		};
	};
};

template <size_t... Ds, class Inp, class CTRL_PTS>
auto bezier(const Inp &inp, const CTRL_PTS &ctrl_pts) {
	return helper::Dim<Ds...>::run(inp, ctrl_pts, typename all_indexes<Ds...>::type{});
}
