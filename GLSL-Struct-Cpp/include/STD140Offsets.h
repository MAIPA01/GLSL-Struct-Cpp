#pragma once

#include <pch.h>
#include <framework.h>
#include <macros.h>
#include <templates.h>
#include <stringExtension.h>
#include <ValueTypes.h>
#include <STDVariable.h>

namespace glsl {
	class STD140Offsets {
	private:
		size_t _currentOffset = 0;
		size_t _maxAligement = 0;

		std::unordered_map<size_t, size_t> _offsets;
		std::unordered_map<size_t, std::string> _names;
		std::unordered_map<size_t, const ValueType*> _types;

		static std::hash<std::string> _hasher;

		static const char* const _arrayElemFormat;
		static const char* const _subElemFormat;

		bool _CheckVariable(const std::string& name) const;

		template<class T, class... Ts, size_t num, size_t... nums>
		requires(sizeof...(Ts) == sizeof...(nums))
		std::enable_if_t<!std::is_same_v<T, STD430Offsets>>
		_AddMultiple(const STDVariable<T, num>& var, const STDVariable<Ts, nums>&... vars) {
			if constexpr (std::is_same_v<T, STD140Offsets>) {
				if (num == 0) {
					Add(var.var_name, var.struct_offsets);
				}
				else {
					Add(var.var_name, var.struct_offsets, num);
				}
			}
			else {
				if (num == 0) {
					Add<T>(var.var_name);
				}
				else {
					Add<T>(var.var_name, num);
				}
			}
			if constexpr (sizeof...(Ts) > 0 && sizeof...(nums) > 0) {
				_AddMultiple(vars...);
			}
		}

		size_t _Add(const std::string& name, size_t baseAligement, size_t baseOffset, const ValueType* type);
		std::vector<size_t> _AddArray(const std::string& name, size_t arraySize, size_t baseAligement, size_t baseOffset, const ValueType* typeTemplate);

	public:
		STD140Offsets() = default;
		STD140Offsets(STD140Offsets& std140off);
		STD140Offsets(const STD140Offsets& std140off);
		STD140Offsets(STD140Offsets&& std140off);
		template<class... Args, size_t... nums>
		requires(sizeof...(Args) == sizeof...(nums))
		STD140Offsets(const STDVariable<Args, nums>&... vars) {
			_AddMultiple(vars...);
		}
		virtual ~STD140Offsets();

		STD140Offsets& operator=(STD140Offsets& std140off);
		STD140Offsets& operator=(const STD140Offsets& std140off);
		STD140Offsets& operator=(STD140Offsets&& std140off);

		DeclareCloneFunc(STD140Offsets)

		bool Contains(const std::string& name) const;

#pragma region ADD_SCALAR
		template<class T>
		typename extra::scalar_enable_if_t<T, size_t>
		Add(const std::string& name) {
			if (_CheckVariable(name)) {
				return 0;
			}

			if constexpr (std::is_same_v<T, bool>) {
				// sizeof(unsigned int) = 4
				return _Add(name, 4, 4, new ScalarType(GetValueType<T>()));
			}
			else {
				return _Add(name, sizeof(T), sizeof(T), new ScalarType(GetValueType<T>()));
			}
		}

		template<class T>
		typename extra::scalar_enable_if_t<T, std::vector<size_t>>
		Add(const std::string& name, size_t size) {
			if (size == 0) {
				return std::vector<size_t>();
			}

			if (_CheckVariable(name)) {
				return std::vector<size_t>();
			}

			if constexpr (std::is_same_v<T, bool>) {
				// sizeof(unsigned int) = 4
				return _AddArray(name, size, 4, 4, new ScalarType(GetValueType<T>()));
			}
			else {
				return _AddArray(name, size, sizeof(T), sizeof(T), new ScalarType(GetValueType<T>()));
			}
		}
#pragma endregion

#pragma region ADD_VEC
		template<class V, class T = V::value_type, size_t L = V::length()>
		typename extra::vec_enable_if_t<V, T, L, size_t>
		Add(const std::string& name) {
			if (_CheckVariable(name)) {
				return 0;
			}

			if constexpr (std::is_same_v<T, bool>) {
				// sizeof(unsigned int) = 4
				if constexpr (extra::is_num_in_v<L, 2, 4>) {
					return _Add(name, 4 * L, 4 * L, new VecType(GetValueType<T>(), L));
				}
				else {
					return _Add(name, 4 * (L + 1), 4 * L, new VecType(GetValueType<T>(), L));
				}
			}
			else {
				if constexpr (extra::is_num_in_v<L, 2, 4>) {
					return _Add(name, sizeof(T) * L, sizeof(T) * L, new VecType(GetValueType<T>(), L));
				}
				else {
					return _Add(name, sizeof(T) * (L + 1), sizeof(T) * L, new VecType(GetValueType<T>(), L));
				}
			}
		}

		template<class V, class T = V::value_type, size_t L = V::length()>
		typename extra::vec_enable_if_t<V, T, L, std::vector<size_t>>
		Add(const std::string& name, size_t size) {
			if (size == 0) {
				return std::vector<size_t>();
			}

			if (_CheckVariable(name)) {
				return std::vector<size_t>();
			}

			if constexpr (std::is_same_v<T, bool>) {
				// sizeof(unsigned int) = 4
				if constexpr (extra::is_num_in_v<L, 2, 4>) {
					return _AddArray(name, size, 4 * L, 4 * L, new VecType(GetValueType<T>(), L));
				}
				else {
					return _AddArray(name, size, 4 * (L + 1), 4 * L, new VecType(GetValueType<T>(), L));
				}
			}
			else {
				if constexpr (extra::is_num_in_v<L, 2, 4>) {
					return _AddArray(name, size, sizeof(T) * L, sizeof(T) * L, new VecType(GetValueType<T>(), L));
				}
				else {
					return _AddArray(name, size, sizeof(T) * (L + 1), sizeof(T) * L, new VecType(GetValueType<T>(), L));
				}
			}
		}
#pragma endregion

#pragma region ADD_MAT
		template<class M, bool column_major = true, class T = M::value_type, size_t C = M::row_type::length(), size_t R = M::col_type::length()>
		typename extra::mat_enable_if_t<M, T, C, R, size_t>
		Add(const std::string& name) {
			if (_CheckVariable(name)) {
				return 0;
			}

			constexpr size_t arraySize = column_major ? C : R;
			constexpr size_t vecSize = column_major ? R : C;

			if constexpr (std::is_same_v<T, bool>) {
				// sizeof(unsigned int) = 4
				if constexpr (extra::is_num_in_v<vecSize, 2, 4>) {
					size_t offset = _AddArray(name, arraySize, 4 * vecSize, 4 * vecSize, new VecType(GetValueType<T>(), vecSize))[0];
					size_t nameHash = _hasher(name);
					delete _types[nameHash];
					_types[nameHash] = new MatType(GetValueType<T>(), C, R);
					return offset;
				}
				else {
					size_t offset = _AddArray(name, arraySize, 4 * (vecSize + 1), 4 * vecSize, new VecType(GetValueType<T>(), vecSize))[0];
					size_t nameHash = _hasher(name);
					delete _types[nameHash];
					_types[nameHash] = new MatType(GetValueType<T>(), C, R);
					return offset;
				}
			}
			else {
				if constexpr (extra::is_num_in_v<vecSize, 2, 4>) {
					size_t offset = _AddArray(name, arraySize, sizeof(T) * vecSize, sizeof(T) * vecSize, new VecType(GetValueType<T>(), vecSize))[0];
					size_t nameHash = _hasher(name);
					delete _types[nameHash];
					_types[nameHash] = new MatType(GetValueType<T>(), C, R);
					return offset;
				}
				else {
					size_t offset = _AddArray(name, arraySize, sizeof(T) * (vecSize + 1), sizeof(T) * vecSize, new VecType(GetValueType<T>(), vecSize))[0];
					size_t nameHash = _hasher(name);
					delete _types[nameHash];
					_types[nameHash] = new MatType(GetValueType<T>(), C, R);
					return offset;
				}
			}
		}

		template<class M, bool column_major = true, class T = M::value_type, size_t C = M::row_type::length(), size_t R = M::col_type::length()>
		typename extra::mat_enable_if_t<M, T, C, R, std::vector<size_t>>
		Add(const std::string& name, size_t size) {
			if (size == 0) {
				return std::vector<size_t>();
			}

			if (_CheckVariable(name)) {
				return std::vector<size_t>();
			}

			constexpr size_t arraySize = column_major ? C : R;
			constexpr size_t vecSize = column_major ? R : C;

			std::vector<size_t> values;

			const ValueType* matType = new MatType(GetValueType<T>(), C, R);
			const ValueType* rowType = new VecType(GetValueType<T>(), vecSize);

			for (size_t i = 0; i < size; ++i) {
				if constexpr (std::is_same_v<T, bool>) {
					// sizeof(unsigned int) = 4
					if constexpr (extra::is_num_in_v<vecSize, 2, 4>) {
						std::string valueName = std::vformat(_arrayElemFormat, std::make_format_args(name, i));
						values.push_back(std::move(_AddArray(valueName, arraySize, 4 * vecSize, 4 * vecSize, rowType)[0]));
						size_t nameHash = _hasher(valueName);
						delete _types[nameHash];
						_types[nameHash] = matType->Clone();
					}
					else {
						std::string valueName = std::vformat(_arrayElemFormat, std::make_format_args(name, i));
						values.push_back(std::move(_AddArray(valueName, arraySize, 4 * (vecSize + 1), 4 * vecSize, rowType)[0]));
						size_t nameHash = _hasher(valueName);
						delete _types[nameHash];
						_types[nameHash] = matType->Clone();
					}
				}
				else {
					if constexpr (extra::is_num_in_v<vecSize, 2, 4>) {
						std::string valueName = std::vformat(_arrayElemFormat, std::make_format_args(name, i));
						values.push_back(std::move(_AddArray(valueName, arraySize, sizeof(T) * vecSize, sizeof(T) * vecSize, rowType)[0]));
						size_t nameHash = _hasher(valueName);
						delete _types[nameHash];
						_types[nameHash] = matType->Clone();
					}
					else {
						std::string valueName = std::vformat(_arrayElemFormat, std::make_format_args(name, i));
						values.push_back(std::move(_AddArray(valueName, arraySize, sizeof(T) * (vecSize + 1), sizeof(T) * vecSize, rowType)[0]));
						size_t nameHash = _hasher(valueName);
						delete _types[nameHash];
						_types[nameHash] = matType->Clone();
					}
				}
			}

			// SET ARRAY BEGIN POINTER
			size_t nameHash = std::move(_hasher(name));
			_offsets[nameHash] = values[0];
			_names[nameHash] = name;
			_types[nameHash] = new ArrayType(matType, size);

			// CLEAR
			delete matType;
			delete rowType;

			return values;
		}
#pragma endregion

#pragma region ADD_STRUCT
		size_t Add(const std::string& name, const STD140Offsets& structTemplate) {
			if (_CheckVariable(name)) {
				return 0;
			}

			size_t aligementOffset = std::move(_Add(name, structTemplate.GetBaseAligement(), structTemplate._currentOffset, new StructType(structTemplate)));
			std::string valueName;
			size_t nameHash;
			for (const auto& off : structTemplate._offsets) {
				valueName = std::move(std::vformat(_subElemFormat, std::make_format_args(name, (*structTemplate._names.find(off.first)).second)));

				nameHash = std::move(_hasher(valueName));
				_offsets[nameHash] = aligementOffset + off.second;
				_names[nameHash] = valueName;
				_types[nameHash] = (*structTemplate._types.find(off.first)).second->Clone();
			}

			// ADD PADDING
			if (_currentOffset % 16 != 0) {
				_currentOffset += 16 - (_currentOffset % 16);
			}
			return aligementOffset;
		}

		std::vector<size_t> Add(const std::string& name, const STD140Offsets& structTemplate, size_t size) {
			if (size == 0) {
				return std::vector<size_t>();
			}
			
			if (_CheckVariable(name)) {
				return std::vector<size_t>();
			}

			std::vector<size_t> values;
			std::string arrayElemName;
			size_t aligementOffset;
			std::string valueName;
			size_t nameHash;

			const ValueType* structType = new StructType(structTemplate);

			for (size_t i = 0; i < size; ++i) {
				arrayElemName = std::move(std::vformat(_arrayElemFormat, std::make_format_args(name, i)));
				values.push_back((aligementOffset = std::move(_Add(arrayElemName, structTemplate.GetBaseAligement(), structTemplate._currentOffset, structType->Clone()))));

				for (const auto& off : structTemplate._offsets) {
					valueName = std::move(std::vformat(_subElemFormat, std::make_format_args(arrayElemName, (*structTemplate._names.find(off.first)).second)));

					nameHash = std::move(_hasher(valueName));
					_offsets[nameHash] = aligementOffset + off.second;
					_names[nameHash] = valueName;
					_types[nameHash] = (*structTemplate._types.find(off.first)).second->Clone();
				}

				// ADD PADDING
				if (_currentOffset % 16 != 0) {
					_currentOffset += 16 - (_currentOffset % 16);
				}
			}

			// SET ARRAY BEGIN POINTER
			nameHash = std::move(_hasher(name));
			_offsets[nameHash] = values[0];
			_names[nameHash] = name;
			_types[nameHash] = new ArrayType(structType, size);
			return values;
		}
#pragma endregion

		size_t Get(const std::string& name) const;
		std::vector<size_t> GetArray(const std::string& name) const;

		const ValueType* GetType(const std::string& name) const;
		std::vector<std::string> GetNames() const;

		size_t GetBaseAligement() const;
		size_t GetSize() const;

		void Clear();
	};
}