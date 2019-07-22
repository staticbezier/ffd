#pragma once

#include <type_traits>
#include <stdint.h>

#include <QDebug>


//! moved into namespace to hide it
namespace detail {
    template <typename T>
    void ignore(T &&)
    { }

	//! consexpr version of abs()
	template <class T>
	constexpr auto abs_value(T val) {
		return val < 0 ? -val : val;
	}

	//! Compile time calculation of the power of a number
	template <int exp>
	struct pow_helper {
		template <class T>
		static auto run(const T &val) {
			return val * pow_helper<abs_value(exp) - 1>::run(val);
		}
	};
	template <>
	struct pow_helper<1> {
		template <class T>
		static auto run(const T &val) {
			return val;
		}
	};
	template <>
	struct pow_helper<0> {
		template <class T>
		static auto run(const T &val) {
            ignore(val);
			return 1;
		}
	};
}

//! pow() function for integer exponents:
//! Performance benefit of ~50% for bernstein::polynomial()
template <int exp, class T>
inline auto powf(const T &val) {
	const auto result = detail::pow_helper<exp>::run(val);
	return exp < 0 ? (static_cast<T>(1) / result) : result;
}

// Compiler generated polynomials
// Moved the functions in class to keep the interface small
class bernstein {
private:
	// Functions to estimate the binominal coefficient
	static constexpr size_t factorial(const size_t n) {
		return (n < 2) ? 1 : n * factorial(n - 1);
	}
	static constexpr size_t bin_coeff(const size_t n, const size_t k) {
		return factorial(n) / factorial(n - k) / factorial(k);
	}

public:
	// Bernstein polynomial
	template <size_t n, size_t k, class T>
	static auto polynomial(const T val) {
		static_assert(n >= k, "Error in bernstein::polynomial: n < k");
		constexpr T binom_coeff = static_cast<T>(bin_coeff(n, k));
		const T a = powf<k>(val);
		const T b = powf<n - k>(1 - val);
        
		// human readable equation
		//qDebug() << "\t" << n << "/"<< k << ":" << binom_coeff << "*" << "t" << "^" << k << "*" << "(1-t)" << "^" << (n-k);
        
		return binom_coeff * a * b;
	}
};
