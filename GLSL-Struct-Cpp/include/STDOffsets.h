#pragma once
#include <pch.h>
#include <framework.h>
#include <STDVariable.h>
#include <ValueTypes.h>
#include <macros.h>
#include <templates.h>

namespace glsl {
	class STDOffsets {
	protected:
		using offsets_map = std::unordered_map<size_t, size_t>;
		using names_map = std::unordered_map<size_t, std::string>;
		using types_map = std::unordered_map<size_t, const ValueType*>;

		size_t _currentOffset = 0;
		size_t _maxAligement = 0;

		offsets_map _offsets;
		names_map _names;
		types_map _types;

		static std::hash<std::string> _hasher;

		static const char* const _arrayElemFormat;
		static const char* const _subElemFormat;

		bool _CheckVariable(const std::string& name) const;

		void _SetVariable(const std::string& name, size_t offset, const ValueType* type);

		/*template<class T, class... Ts, size_t num, size_t... nums>
		requires(sizeof...(Ts) == sizeof...(nums))
		void _AddMultiple(const STDVariable<T, num>& var, const STDVariable<Ts, nums>&... vars) {
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
		}*/

		virtual size_t _Add(const std::string& name, size_t baseAligement, size_t baseOffset, const ValueType* type);
		virtual std::vector<size_t> _AddArray(const std::string& name, size_t arraySize, size_t baseAligement, size_t baseOffset, const ValueType* type);

		virtual size_t _AddScalar(const std::string& name, size_t baseAligement, size_t baseOffset, const VALUE_TYPE& type);
		virtual std::vector<size_t> _AddScalarArray(const std::string& name, size_t baseAligement, size_t baseOffset, const VALUE_TYPE& type, size_t arraySize);

		virtual size_t _AddVector(const std::string& name, size_t length, size_t baseAligement, size_t baseOffset, const VALUE_TYPE& type);
		virtual std::vector<size_t> _AddVectorArray(const std::string& name, size_t length, size_t baseAligement, size_t baseOffset, const VALUE_TYPE& type, size_t arraySize);

		virtual size_t _AddMatrix(const std::string& name, size_t columns, size_t rows, bool column_major, size_t baseAligement, size_t baseOffset, const VALUE_TYPE& type);
		virtual std::vector<size_t> _AddMatrixArray(const std::string& name, size_t columns, size_t rows, bool column_major, size_t baseAligement, size_t baseOffset, const VALUE_TYPE& type, size_t arraySize);

		virtual size_t _AddStruct(const std::string& name, size_t baseAligement, size_t baseOffset, const offsets_map& offsets, const names_map& names, const types_map& types);
		virtual std::vector<size_t> _AddStructArray(const std::string& name, size_t baseAligement, size_t baseOffset, const offsets_map& offsets, const names_map& names, const types_map& types, size_t arraySize);

	public:
		STDOffsets() = default;
		STDOffsets(STDOffsets& stdOff);
		STDOffsets(const STDOffsets& stdOff);
		STDOffsets(STDOffsets&& stdOff);
		/*template<class... Args, size_t... nums>
		requires(sizeof...(Args) == sizeof...(nums))
		STDOffsets(const STDVariable<Args, nums>&... vars) {
			_AddMultiple(vars...);
		}*/
		virtual ~STDOffsets();

		STDOffsets& operator=(STDOffsets& stdOff);
		STDOffsets& operator=(const STDOffsets& stdOff);
		STDOffsets& operator=(STDOffsets&& stdOff);

		DeclareCloneFunc(STDOffsets)

		bool Contains(const std::string& name) const;

		size_t Get(const std::string& name) const;
		std::vector<size_t> GetArray(const std::string& name) const;

		const ValueType* GetType(const std::string& name) const;
		std::vector<std::string> GetNames() const;

		size_t GetBaseAligement() const;
		size_t GetSize() const;

		void Clear();
	};
}