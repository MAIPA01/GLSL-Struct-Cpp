#pragma once
#include <pch.h>
#include <framework.h>
#include <types.h>
#include <templates.h>

namespace glsl {

	template<class T, size_t num = 0>
	struct STDVariable {
	private:
#pragma region CHECKS
		template<class T> using struct_enable_if_t = extra::type_test_t<extra::struct_check_v<T>,
			extra::type_test_t<extra::struct140_check_v<T>, const STD140Offsets, const STD430Offsets>,
			void(*)>;
#pragma endregion

	public:
		using var_type = T;
		const size_t array_size = num;

#pragma region VARIABLES
		const std::string var_name;
		typename struct_enable_if_t<T> struct_offsets;
#pragma endregion

#pragma region NORMAL_CONSTRUCTOR
		template<typename = extra::scalar_enable_if_t<T>>
		STDVariable(const std::string& name) : var_name(name) {}

		template<class VT = T::value_type, size_t L = T::length(), typename = extra::vec_enable_if_t<T, VT, L>>
		STDVariable(const std::string& name) : var_name(name) {}

		template<class MT = T::value_type, size_t C = T::row_type::length(), size_t R = T::col_type::length(), typename = extra::mat_enable_if_t<T, MT, C, R>>
		STDVariable(const std::string& name) : var_name(name) {}
#pragma endregion

#pragma region STRUCT_CONSTRUCTOR
		template<typename = extra::struct140_enable_if_t<T>>
		STDVariable(const std::string& name, const STD140Offsets offsets) : var_name(name), struct_offsets(offsets) {}

		template<typename = extra::struct430_enable_if_t<T>>
		STDVariable(const std::string& name, const STD430Offsets offsets) : var_name(name), struct_offsets(offsets) {}
#pragma endregion
	};
}