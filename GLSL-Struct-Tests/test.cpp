#include "pch.h"

using namespace glsl;
using namespace glm;

TEST(STD140Offsets, AddScalars) {
	STD140Offsets structOffsets;
	size_t ret;

	// BOOL
	ret = structOffsets.Add<bool>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<int>("Int");
	EXPECT_EQ(ret, 4);

	// UINT
	ret = structOffsets.Add<unsigned int>("Uint");
	EXPECT_EQ(ret, 8);

	// FLOAT
	ret = structOffsets.Add<float>("Float");
	EXPECT_EQ(ret, 12);

	// DOUBLE
	ret = structOffsets.Add<double>("Double");
	EXPECT_EQ(ret, 16);
}

TEST(STD140Offsets, AddScalarsArray) {
	STD140Offsets structOffsets;
	std::vector<size_t> results(2);
	std::vector<size_t> ret;

	// BOOL
	results[0] = 0;
	results[1] = 16;
	ret = structOffsets.Add<bool>("Bools", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 32;
	results[1] = 48;
	ret = structOffsets.Add<int>("Ints", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 64;
	results[1] = 80;
	ret = structOffsets.Add<unsigned int>("Uints", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 96;
	results[1] = 112;
	ret = structOffsets.Add<float>("Floats", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 128;
	results[1] = 144;
	ret = structOffsets.Add<double>("Doubles", 2);
	EXPECT_EQ(ret, results);
}

TEST(STD140Offsets, AddVectors) {
	STD140Offsets structOffsets;
	size_t ret;

#pragma region VEC2
	structOffsets.Clear();
	
	// BOOL
	ret = structOffsets.Add<bvec2>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<ivec2>("Int");
	EXPECT_EQ(ret, 8);

	// UINT
	ret = structOffsets.Add<uvec2>("Uint");
	EXPECT_EQ(ret, 16);

	// FLOAT
	ret = structOffsets.Add<vec2>("Float");
	EXPECT_EQ(ret, 24);

	// DOUBLE
	ret = structOffsets.Add<dvec2>("Double");
	EXPECT_EQ(ret, 32);
#pragma endregion

#pragma region VEC3
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bvec3>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<ivec3>("Int");
	EXPECT_EQ(ret, 16);

	// UINT
	ret = structOffsets.Add<uvec3>("Uint");
	EXPECT_EQ(ret, 32);

	// FLOAT
	ret = structOffsets.Add<vec3>("Float");
	EXPECT_EQ(ret, 48);

	// DOUBLE
	ret = structOffsets.Add<dvec3>("Double");
	EXPECT_EQ(ret, 64);
#pragma endregion

#pragma region VEC4
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bvec4>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<ivec4>("Int1");
	EXPECT_EQ(ret, 16);

	// UINT
	ret = structOffsets.Add<uvec4>("Uint1");
	EXPECT_EQ(ret, 32);

	// FLOAT
	ret = structOffsets.Add<vec4>("Float1");
	EXPECT_EQ(ret, 48);

	// DOUBLE
	ret = structOffsets.Add<dvec4>("Double1");
	EXPECT_EQ(ret, 64);
#pragma endregion
}

TEST(STD140Offsets, AddVectorsArray) {
	STD140Offsets structOffsets;
	std::vector<size_t> results(2);
	std::vector<size_t> ret;

#pragma region VEC2
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 16;
	ret = structOffsets.Add<bvec2>("Bools", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 32;
	results[1] = 48;
	ret = structOffsets.Add<ivec2>("Ints", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 64;
	results[1] = 80;
	ret = structOffsets.Add<uvec2>("Uints", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 96;
	results[1] = 112;
	ret = structOffsets.Add<vec2>("Floats", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 128;
	results[1] = 144;
	ret = structOffsets.Add<dvec2>("Doubles", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma region VEC3
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 16;
	ret = structOffsets.Add<bvec3>("Bools", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 32;
	results[1] = 48;
	ret = structOffsets.Add<ivec3>("Ints", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 64;
	results[1] = 80;
	ret = structOffsets.Add<uvec3>("Uints", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 96;
	results[1] = 112;
	ret = structOffsets.Add<vec3>("Floats", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 128;
	results[1] = 160;
	ret = structOffsets.Add<dvec3>("Doubles", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma region VEC4
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 16;
	ret = structOffsets.Add<bvec4>("Bools", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 32;
	results[1] = 48;
	ret = structOffsets.Add<ivec4>("Ints", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 64;
	results[1] = 80;
	ret = structOffsets.Add<uvec4>("Uints", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 96;
	results[1] = 112;
	ret = structOffsets.Add<vec4>("Floats", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 128;
	results[1] = 160;
	ret = structOffsets.Add<dvec4>("Doubles", 2);
	EXPECT_EQ(ret, results);
#pragma endregion
}

TEST(STD140Offsets, AddMatrixes) {
	STD140Offsets structOffsets;
	size_t ret;

#pragma region COLUMN_MAJOR

#pragma region MAT2x2
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bmat2>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<imat2>("Int");
	EXPECT_EQ(ret, 32);

	// UINT
	ret = structOffsets.Add<umat2>("Uint");
	EXPECT_EQ(ret, 64);

	// FLOAT
	ret = structOffsets.Add<fmat2>("Float");
	EXPECT_EQ(ret, 96);

	// DOUBLE
	ret = structOffsets.Add<dmat2>("Double");
	EXPECT_EQ(ret, 128);
#pragma endregion

#pragma region MAT2x3
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bmat2x3>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<imat2x3>("Int");
	EXPECT_EQ(ret, 32);

	// UINT
	ret = structOffsets.Add<umat2x3>("Uint");
	EXPECT_EQ(ret, 64);

	// FLOAT
	ret = structOffsets.Add<fmat2x3>("Float");
	EXPECT_EQ(ret, 96);

	// DOUBLE
	ret = structOffsets.Add<dmat2x3>("Double");
	EXPECT_EQ(ret, 128);
#pragma endregion

#pragma region MAT2x4
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bmat2x4>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<imat2x4>("Int");
	EXPECT_EQ(ret, 32);

	// UINT
	ret = structOffsets.Add<umat2x4>("Uint");
	EXPECT_EQ(ret, 64);

	// FLOAT
	ret = structOffsets.Add<fmat2x4>("Float");
	EXPECT_EQ(ret, 96);

	// DOUBLE
	ret = structOffsets.Add<dmat2x4>("Double");
	EXPECT_EQ(ret, 128);
#pragma endregion

#pragma endregion

#pragma region ROW_MAJOR

#pragma region MAT2x2
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bmat2, false>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<imat2, false>("Int");
	EXPECT_EQ(ret, 32);

	// UINT
	ret = structOffsets.Add<umat2, false>("Uint");
	EXPECT_EQ(ret, 64);

	// FLOAT
	ret = structOffsets.Add<fmat2, false>("Float");
	EXPECT_EQ(ret, 96);

	// DOUBLE
	ret = structOffsets.Add<dmat2, false>("Double");
	EXPECT_EQ(ret, 128);
#pragma endregion

#pragma region MAT2x3
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bmat2x3, false>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<imat2x3, false>("Int");
	EXPECT_EQ(ret, 48);

	// UINT
	ret = structOffsets.Add<umat2x3, false>("Uint");
	EXPECT_EQ(ret, 96);

	// FLOAT
	ret = structOffsets.Add<fmat2x3, false>("Float");
	EXPECT_EQ(ret, 144);

	// DOUBLE
	ret = structOffsets.Add<dmat2x3, false>("Double");
	EXPECT_EQ(ret, 192);
#pragma endregion

#pragma region MAT2x4
	structOffsets.Clear();

	// BOOL
	ret = structOffsets.Add<bmat2x4, false>("Bool");
	EXPECT_EQ(ret, 0);

	// INT
	ret = structOffsets.Add<imat2x4, false>("Int");
	EXPECT_EQ(ret, 64);

	// UINT
	ret = structOffsets.Add<umat2x4, false>("Uint");
	EXPECT_EQ(ret, 128);

	// FLOAT
	ret = structOffsets.Add<fmat2x4, false>("Float");
	EXPECT_EQ(ret, 192);

	// DOUBLE
	ret = structOffsets.Add<dmat2x4, false>("Double");
	EXPECT_EQ(ret, 256);
#pragma endregion

#pragma endregion
}

TEST(STD140Offsets, AddMarixesArray) {
	STD140Offsets structOffsets;
	std::vector<size_t> results(2);
	std::vector<size_t> ret;

#pragma region COLUMN_MAJOR

#pragma region MAT2x2
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 32;
	ret = structOffsets.Add<bmat2>("Bool", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 64;
	results[1] = 96;
	ret = structOffsets.Add<imat2>("Int", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 128;
	results[1] = 160;
	ret = structOffsets.Add<umat2>("Uint", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 192;
	results[1] = 224;
	ret = structOffsets.Add<fmat2>("Float", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 256;
	results[1] = 288;
	ret = structOffsets.Add<dmat2>("Double", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma region MAT2x3
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 32;
	ret = structOffsets.Add<bmat2x3>("Bool", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 64;
	results[1] = 96;
	ret = structOffsets.Add<imat2x3>("Int", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 128;
	results[1] = 160;
	ret = structOffsets.Add<umat2x3>("Uint", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 192;
	results[1] = 224;
	ret = structOffsets.Add<fmat2x3>("Float", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 256;
	results[1] = 320;
	ret = structOffsets.Add<dmat2x3>("Double", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma region MAT2x4
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 32;
	ret = structOffsets.Add<bmat2x4>("Bool", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 64;
	results[1] = 96;
	ret = structOffsets.Add<imat2x4>("Int", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 128;
	results[1] = 160;
	ret = structOffsets.Add<umat2x4>("Uint", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 192;
	results[1] = 224;
	ret = structOffsets.Add<fmat2x4>("Float", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 256;
	results[1] = 320;
	ret = structOffsets.Add<dmat2x4>("Double", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma endregion

#pragma region ROW_MAJOR

#pragma region MAT2x2
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 32;
	ret = structOffsets.Add<bmat2, false>("Bool", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 64;
	results[1] = 96;
	ret = structOffsets.Add<imat2, false>("Int", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 128;
	results[1] = 160;
	ret = structOffsets.Add<umat2, false>("Uint", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 192;
	results[1] = 224;
	ret = structOffsets.Add<fmat2, false>("Float", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 256;
	results[1] = 288;
	ret = structOffsets.Add<dmat2, false>("Double", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma region MAT2x3
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 48;
	ret = structOffsets.Add<bmat2x3, false>("Bool", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 96;
	results[1] = 144;
	ret = structOffsets.Add<imat2x3, false>("Int", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 192;
	results[1] = 240;
	ret = structOffsets.Add<umat2x3, false>("Uint", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 288;
	results[1] = 336;
	ret = structOffsets.Add<fmat2x3, false>("Float", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 384;
	results[1] = 432;
	ret = structOffsets.Add<dmat2x3, false>("Double", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma region MAT2x4
	structOffsets.Clear();

	// BOOL
	results[0] = 0;
	results[1] = 64;
	ret = structOffsets.Add<bmat2x4, false>("Bool", 2);
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 128;
	results[1] = 192;
	ret = structOffsets.Add<imat2x4, false>("Int", 2);
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 256;
	results[1] = 320;
	ret = structOffsets.Add<umat2x4, false>("Uint", 2);
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 384;
	results[1] = 448;
	ret = structOffsets.Add<fmat2x4, false>("Float", 2);
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 512;
	results[1] = 576;
	ret = structOffsets.Add<dmat2x4, false>("Double", 2);
	EXPECT_EQ(ret, results);
#pragma endregion

#pragma endregion
}

TEST(STD140Offsets, AddStruct) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, AddStructArray) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, OffsetCalculation1) {
	STD140Offsets structOffsets;
	STD140Offsets subStructOffsets;
	size_t ret;
	std::vector<size_t> retVec;
	std::vector<size_t> resultVec(2);

	ret = structOffsets.Add<float>("a");
	EXPECT_EQ(ret, 0);
	ret = structOffsets.Add<vec2>("b");
	EXPECT_EQ(ret, 8);
	ret = structOffsets.Add<vec3>("c");
	EXPECT_EQ(ret, 16);

	ret = subStructOffsets.Add<int>("d");
	EXPECT_EQ(ret, 0);
	ret = subStructOffsets.Add<bvec2>("e");
	EXPECT_EQ(ret, 8);
	ret = subStructOffsets.GetSize();
	EXPECT_EQ(ret, 16);

	ret = structOffsets.Add("f", subStructOffsets);
	EXPECT_EQ(ret, 32);
	ret = structOffsets.Add<float>("g");
	EXPECT_EQ(ret, 48);
	resultVec[0] = 64;
	resultVec[1] = 80;
	retVec = structOffsets.Add<float>("h", 2);
	EXPECT_EQ(retVec, resultVec);
	ret = structOffsets.Add<mat2x3>("i");
	EXPECT_EQ(ret, 96);

	subStructOffsets.Clear();
	ret = subStructOffsets.Add<uvec3>("j");
	EXPECT_EQ(ret, 0);
	ret = subStructOffsets.Add<vec2>("k");
	EXPECT_EQ(ret, 16);
	resultVec[0] = 32;
	resultVec[1] = 48;
	retVec = subStructOffsets.Add<float>("l", 2);
	EXPECT_EQ(retVec, resultVec);
	ret = subStructOffsets.Add<vec2>("m");
	EXPECT_EQ(ret, 64);
	resultVec[0] = 80;
	resultVec[1] = 128;
	retVec = subStructOffsets.Add<mat3>("n", 2);
	EXPECT_EQ(retVec, resultVec);
	ret = subStructOffsets.GetSize();
	EXPECT_EQ(ret, 176);

	resultVec[0] = 128;
	resultVec[1] = 304;
	retVec = structOffsets.Add("o", subStructOffsets, 2);
	EXPECT_EQ(retVec, resultVec);
	ret = structOffsets.GetSize();
	EXPECT_EQ(ret, 480);
}

TEST(STD140Offsets, OffsetCalculation2) {
	STD140Offsets structOffsets;
	STD140Offsets subStructOffsets;
	size_t ret;
	std::vector<size_t> retVec;
	std::vector<size_t> resultVec(8);

	ret = subStructOffsets.Add<bool>("has_diffuse_texture");
	EXPECT_EQ(ret, 0);
	ret = subStructOffsets.Add<bool>("has_specular_texture");
	EXPECT_EQ(ret, 4);
	ret = subStructOffsets.Add<vec3>("color");
	EXPECT_EQ(ret, 16);
	ret = subStructOffsets.Add<float>("shininess");
	EXPECT_EQ(ret, 28);
	ret = subStructOffsets.Add<unsigned int>("diffuse_toon_borders");
	EXPECT_EQ(ret, 32);
	ret = subStructOffsets.Add<unsigned int>("specular_toon_borders");
	EXPECT_EQ(ret, 36);
	ret = subStructOffsets.Add<vec2>("highlight_translate");
	EXPECT_EQ(ret, 40);
	ret = subStructOffsets.Add<vec2>("highlight_rotation");
	EXPECT_EQ(ret, 48);
	ret = subStructOffsets.Add<vec2>("highlight_scale");
	EXPECT_EQ(ret, 56);
	ret = subStructOffsets.Add<vec2>("highlight_split");
	EXPECT_EQ(ret, 64);
	ret = subStructOffsets.Add<int>("highlight_square_n");
	EXPECT_EQ(ret, 72);
	ret = subStructOffsets.Add<float>("highlight_square_x");
	EXPECT_EQ(ret, 76);
	ret = subStructOffsets.GetSize();
	EXPECT_EQ(ret, 80);

	resultVec[0] = 0;
	resultVec[1] = 80;
	resultVec[2] = 160;
	resultVec[3] = 240;
	resultVec[4] = 320;
	resultVec[5] = 400;
	resultVec[6] = 480;
	resultVec[7] = 560;
	retVec = structOffsets.Add("materialInputs", subStructOffsets, 8);
	EXPECT_EQ(retVec, resultVec);
	ret = structOffsets.GetSize();
	EXPECT_EQ(ret, 640);
}

TEST(STD140Offsets, OffsetCalculation3) {
	STD140Offsets structOffsets;
	STD140Offsets subStructOffsets;
	size_t ret;
	std::vector<size_t> retVec;
	std::vector<size_t> resultVec(2);

	ret = structOffsets.Add<vec2>("windowSize");
	EXPECT_EQ(ret, 0);
	ret = structOffsets.Add<float>("nearPlane");
	EXPECT_EQ(ret, 8);
	ret = structOffsets.Add<float>("farPlane");
	EXPECT_EQ(ret, 12);
	ret = structOffsets.Add<float>("gamma");
	EXPECT_EQ(ret, 16);
	ret = structOffsets.GetSize();
	EXPECT_EQ(ret, 32);
}