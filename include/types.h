#pragma once
namespace glsl {
	class STD140Offsets;
	class STD430Offsets;
	template<class T, size_t num = 0> struct STDVariable;

	template<class _Offsets, typename = std::enable_if_t<(std::is_base_of_v<STD140Offsets, _Offsets> || std::is_same_v<STD140Offsets, _Offsets>)>> 
	class STDStruct;
	template<class T, size_t num = 0> struct STDValue;
}