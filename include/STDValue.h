#pragma once
#include <pch.h>
#include <framework.h>

namespace glsl {
	template<class T, size_t num = 0>
	struct STDValue {
	public:
		using var_type = T;

		const std::string var_name;
		const T value;
		const size_t array_size;

		template<typename = std::enable_if_t<!std::is_same_v<T, STD140Offsets>>>
		STD140Value(const std::string& name) : var_name(name), value(), hasValue(false), array_size(0) {}

		STD140Value(const std::string& name, T value) : var_name(name), value(value), hasValue(true), array_size(0) {}

		template<typename = std::enable_if_t<!std::is_same_v<T, STD140Offsets>>>
		STD140Value(const std::string& name, const size_t& size) : var_name(name), value(), hasValue(false), array_size(size) {}

		template<typename = std::enable_if_t<std::is_same_v<T, STD140Offsets>>>
		STD140Value(const std::string& name, const T& offsets, const size_t& size) : var_name(name), value(offsets), hasValue(true), array_size(size) {}
	};
}

