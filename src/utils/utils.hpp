#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>

namespace ft {
	template< bool B, class T = void >
	struct enable_if { };

	template< class T >
	struct enable_if<true, T> { typedef T type; };

	template< class T >
	struct is_integral {
		typedef bool value_type;
		static const bool value = false;
	};

	template <>
	struct is_integral<bool> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char16_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char32_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<int> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int> {
		static const bool value = true;
	};
}

#endif