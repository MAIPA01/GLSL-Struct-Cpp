#pragma once
#include <pch.h>
#include <framework.h>
#include <STDVariable.h>
#include <STDStruct.h>

namespace glsl {
	template<class T, size_t num = 0>
	struct STDValue {
	private:
#pragma region CHECKS
		template<class _Type, size_t length> using array_var_check_t = extra::type_test_t<(length == 0), _Type, std::vector<_Type>>;

		template<class _Type, size_t length, class Ret = void> using scalar_array_enable_if_t = std::enable_if_t<(extra::scalar_check_v<_Type>&& length > 0), Ret>;
		template<class _Type, size_t L, size_t length, class Ret = void> using vec_array_enable_if_t = std::enable_if_t<(extra::vec_check_v<_Type, L>&& length > 0), Ret>;
		template<class _Type, size_t C, size_t R, size_t length, class Ret = void> using mat_array_enable_if_t = std::enable_if_t<(extra::mat_check_v<_Type, C, R> && length > 0), Ret>;

		template<class _Type, class _Offsets, class Ret = void> using struct_enable_if_t = std::enable_if_t<(std::is_same_v<_Type, STDStruct<_Offsets>>&& extra::offsets_check_v<_Offsets>), Ret>;
		template<class _Type, class Ret = void> using scalar_offsets_enable_if_t = std::enable_if_t<(extra::scalar_check_v<_Type> || extra::offsets_check_v<_Type>), Ret>;
#pragma endregion

	public:
		using value_type = T;
		const size_t array_size = num;

#pragma region VARIABLES
		const std::string var_name;
		const array_var_check_t<T, num> value;
		const bool is_offsets;
		const bool is_struct;
#pragma endregion

#pragma region NORMAL_AND_OFFSETS_CONSTRUCTORS
		template<typename = scalar_offsets_enable_if_t<T>>
		STDValue(const std::string& name) : var_name(name), value(array_var_check_t<T, num>()), is_struct(false) {
			if constexpr (num > 0) {
				value.resize(num);
			}

			if constexpr (extra::scalar_check_v<T>) {
				is_offsets = false;
			}
			else if constexpr (extra::offsets_check_v<T>) {
				is_offsets = true;
			}
		}

		template<typename = scalar_offsets_enable_if_t<T>>
		STDValue(const std::string& name, const array_var_check_t<T, num>& value) : var_name(name), value(value), is_struct(false) {
			if constexpr (extra::scalar_check_v<T>) {
				is_offsets = false;
			}
			else if constexpr (extra::offsets_check_v<T>) {
				is_offsets = true;
			}
		}
#pragma endregion

#pragma region NORMAL_CONSTRUCTORS
		template<class VT = T::value_type, size_t L = T::length(), typename = extra::vec_enable_if_t<T, VT, L>>
		STDValue(const std::string& name) : var_name(name), value(array_var_check_t<T, num>()), is_offsets(false), is_struct(false) {
			if constexpr (num > 0) {
				value.resize(num);
			}
		}

		template<class VT = T::value_type, size_t L = T::length(), typename = extra::vec_enable_if_t<T, VT, L>>
		STDValue(const std::string& name, const array_var_check_t<T, num>& value) : var_name(name), value(value), is_offsets(false), is_struct(false) {}

		template<class MT = T::value_type, size_t C = T::row_type::length(), size_t R = T::col_type::length(), typename = extra::mat_enable_if_t<T, MT, C, R>>
		STDValue(const std::string& name) : var_name(name), value(array_var_check_t<T, num>()), is_offsets(false), is_struct(false) {
			if constexpr (num > 0) {
				value.resize(num);
			}
		}

		template<class MT = T::value_type, size_t C = T::row_type::length(), size_t R = T::col_type::length(), typename = extra::mat_enable_if_t<T, MT, C, R>>
		STDValue(const std::string& name, const array_var_check_t<T, num>& value) : var_name(name), value(value), is_offsets(false), is_struct(false) {}
#pragma endregion

#pragma region NORMAL_AND_OFFSETS_ARRAY_CONSTRUCTORS
		template<typename = scalar_offsets_enable_if_t<T>>
		STDValue(const std::string& name, const T*& values, size_t size) : var_name(name), is_struct(false) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				if (i < size) {
					array_values.push_back(values[i]);
				}
				else {
					array_values.push_back(T());
				}
			}
			value = array_values;

			if constexpr (extra::scalar_check_v<T>) {
				is_offsets = false;
			}
			else if constexpr (extra::offsets_check_v<T>) {
				is_offsets = true;
			}
		}

		template<typename = scalar_offsets_enable_if_t<T>>
		STDValue(const std::string& name, const T(&values)[num]) : var_name(name), is_struct(false) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				array_values.push_back(values[i]);
			}
			value = array_values;

			if constexpr (extra::scalar_check_v<T>) {
				is_offsets = false;
			}
			else if constexpr (extra::offsets_check_v<T>) {
				is_offsets = true;
			}
		}
#pragma endregion

#pragma region NORMAL_ARRAY_CONSTRUCTORS
		template<class VT = T::value_type, size_t L = T::length(), typename = vec_array_enable_if_t<VT, L, num>>
		STDValue(const std::string& name, const T*& values, size_t size) : var_name(name), is_offsets(false), is_struct(false) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				if (i < size) {
					array_values.push_back(values[i]);
				}
				else {
					array_values.push_back(T());
				}
			}
			value = array_values;
		}

		template<class VT = T::value_type, size_t L = T::length(), typename = scalar_array_enable_if_t<T, num>>
		STDValue(const std::string& name, const T(&values)[num]) : var_name(name), is_offsets(false), is_struct(false) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				array_values.push_back(values[i]);
			}
			value = array_values;
		}

		template<class MT = T::value_type, size_t C = T::row_type::length(), size_t R = T::col_type::length(), typename = scalar_array_enable_if_t<T, num>>
		STDValue(const std::string& name, const T*& values, size_t size) : var_name(name), is_offsets(false), is_struct(false) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				if (i < size) {
					array_values.push_back(values[i]);
				}
				else {
					array_values.push_back(T());
				}
			}
			value = array_values;
		}

		template<class MT = T::value_type, size_t C = T::row_type::length(), size_t R = T::col_type::length(), typename = scalar_array_enable_if_t<T, num>>
		STDValue(const std::string& name, const T(&values)[num]) : var_name(name), is_offsets(false), is_struct(false) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				array_values.push_back(values[i]);
			}
			value = array_values;
		}
#pragma endregion

#pragma region STRUCT_CONSTRUCTORS
		template<class O = T::offset_type, typename = struct_enable_if_t<T, O>>
		STDValue(const std::string& name) : var_name(name), value(array_var_check_t<T, num>()), is_offsets(false), is_struct(true) {
			if constexpr (num > 0) {
				value.resize(num);
			}
		}

		template<class O = T::offset_type, typename = struct_enable_if_t<T, O>>
		STDValue(const std::string& name, const array_var_check_t<T, num>& value) : var_name(name), value(value), is_offsets(false), is_struct(true) {}
#pragma endregion

#pragma region STRUCT_ARRAY_CONSTRUCTORS
		template<class O = T::offset_type, typename = struct_enable_if_t<T, O>>
		STDValue(const std::string& name, const T*& values) : var_name(name), is_offsets(false), is_struct(true) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				if (i < size) {
					array_values.push_back(values[i]);
				}
				else {
					array_values.push_back(T());
				}
			}
			value = array_values;
		}

		template<class O = T::offset_type, typename = struct_enable_if_t<T, O>>
		STDValue(const std::string& name, const T(&values)[num]) : var_name(name), is_offsets(false), is_struct(true) {
			std::vector<T> array_values;
			array_values.reserve(num);
			for (size_t i = 0; i < num; ++i) {
				array_values.push_back(values[i]);
			}
			value = array_values;
		}
#pragma endregion
	};
}

