#pragma once
namespace glsl {
	class STD140Offsets;
	class STD430Offsets;
	template<class T, size_t num> struct STDVariable;

	template<class _Offsets, typename> 
	class STDStruct;
	template<class T, size_t num> struct STDValue;
}