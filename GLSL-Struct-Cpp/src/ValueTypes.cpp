#include <pch.h>
#include <ValueTypes.h>
#include <STD140Offsets.h>

using namespace glsl;
using namespace std;
using namespace extra;

static string glsl::GetVecType(const VALUE_TYPE& type)
{
	using enum VALUE_TYPE;
	switch (type) {
		case OTHER: return "other";
		case BOOL: return "bvec";
		case INT: return "ivec";
		case UINT: return "uvec";
		case FLOAT: return "vec";
		case DOUBLE: return "dvec";
		default: return "UNKNOWN";
	}
}

static string glsl::GetMatType(const VALUE_TYPE& type)
{
	using enum VALUE_TYPE;
	switch (type) {
		case OTHER: return "other";
		case BOOL: return "bmat";
		case INT: return "imat";
		case UINT: return "umat";
		case FLOAT: return "mat";
		case DOUBLE: return "dmat";
		default: return "UNKNOWN";
	}
}

static string glsl::to_string(const ValueType*& value)
{
	return value->to_string();
}

ScalarType::ScalarType(const VALUE_TYPE& type) : ValueType(), _type(type) {}

VALUE_TYPE ScalarType::GetType() const {
	return _type;
}

string ScalarType::to_string() const
{
	return glsl::to_string(_type);
}

static string glsl::to_string(const ScalarType& value)
{
	return value.to_string();
}

VecType::VecType(const VALUE_TYPE& type, const size_t& length) : ValueType(), _type(type), _length(length) {}

VALUE_TYPE VecType::GetType() const
{
	return _type;
}

size_t VecType::GetLength() const
{
	return _length;
}

string VecType::to_string() const
{
	return concat(GetVecType(_type), std::to_string(_length));
}

static string glsl::to_string(const VecType& value)
{
	return value.to_string();
}

MatType::MatType(const VALUE_TYPE& type, const size_t& cols, const size_t& rows) : ValueType(), _type(type), _cols(cols), _rows(rows) {}

VALUE_TYPE MatType::GetType() const
{
	return _type;
}

size_t MatType::GetRows() const
{
	return _rows;
}

size_t MatType::GetCols() const
{
	return _cols;
}

string MatType::to_string() const
{
	string out = GetMatType(_type);
	if (_cols == _rows) concat_ref(out, std::to_string(_cols));
	else concat_ref(out, std::to_string(_cols), "x"s, std::to_string(_rows));
	return out;
}

static string glsl::to_string(const MatType& value)
{
	return value.to_string();
}

StructType::StructType(const offsets_map& offsets, const names_map& names, const types_map& types) : ValueType(), _offsets(offsets), _names(names) {
	for (auto& type : types) {
		_types[type.first] = type.second->Clone();
	}
}

StructType::~StructType() {
	_offsets.clear();
	_names.clear();
	for (auto& type : _types) {
		if (type.second == nullptr) continue;
		delete type.second;
	}
	_types.clear();
}

DefineCloneFunc(StructType, StandardClone(_offsets), StandardClone(_names);
	for (const auto& type : _types) cloned->_types[type.first] = type.second->Clone()
)

StructType::offsets_map StructType::GetOffsets() const
{
	return _offsets;
}

StructType::names_map StructType::GetNames() const
{
	return _names;
}

StructType::types_map StructType::GetTypes() const
{
	return _types;
}

string StructType::to_string() const
{
	return "struct"s;
}

static string glsl::to_string(const StructType& value)
{
	return value.to_string();
}

ArrayType::ArrayType(const ValueType* type, const size_t& length) : ValueType(), _length(length) {
	_type = type;
}

ArrayType::~ArrayType() {
	delete _type;
}

const ValueType* ArrayType::GetType() const
{
	return _type;
}

size_t ArrayType::GetLength() const
{
	return _length;
}

string ArrayType::to_string() const
{
	return concat(_type->to_string(), "["s, std::to_string(_length), "]"s);
}

static string glsl::to_string(const ArrayType& value)
{
	return value.to_string();
}