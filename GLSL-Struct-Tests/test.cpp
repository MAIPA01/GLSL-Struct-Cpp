#include "pch.h"

using namespace glsl;

TEST(STD140Offsets, AddScalars) {
	STD140Offsets structOffsets;
	size_t ret;

	// BOOL
	ret = structOffsets.Add<bool>("Bool1");
	EXPECT_EQ(ret, 0);
	ret = structOffsets.Add<bool>("Bool2");
	EXPECT_EQ(ret, 4);

	// INT
	ret = structOffsets.Add<int>("Int1");
	EXPECT_EQ(ret, 8);
	ret = structOffsets.Add<int>("Int2");
	EXPECT_EQ(ret, 12);

	// UINT
	ret = structOffsets.Add<unsigned int>("Uint1");
	EXPECT_EQ(ret, 16);
	ret = structOffsets.Add<unsigned int>("Uint2");
	EXPECT_EQ(ret, 20);

	// FLOAT
	ret = structOffsets.Add<float>("Float1");
	EXPECT_EQ(ret, 24);
	ret = structOffsets.Add<float>("Float2");
	EXPECT_EQ(ret, 28);

	// DOUBLE
	ret = structOffsets.Add<double>("Double1");
	EXPECT_EQ(ret, 32);
	ret = structOffsets.Add<double>("Double2");
	EXPECT_EQ(ret, 40);
}

TEST(STD140Offsets, AddScalarsArray) {
	STD140Offsets structOffsets;
	std::vector<size_t> results(2);
	std::vector<size_t> ret;

	// BOOL
	results[0] = 0;
	results[1] = 16;
	ret = structOffsets.Add<bool, 2>("Bool1");
	EXPECT_EQ(ret, results);
	results[0] = 32;
	results[1] = 48;
	ret = structOffsets.Add<bool, 2>("Bool2");
	EXPECT_EQ(ret, results);

	// INT
	results[0] = 64;
	results[1] = 80;
	ret = structOffsets.Add<int, 2>("Int1");
	EXPECT_EQ(ret, results);
	results[0] = 96;
	results[1] = 112;
	ret = structOffsets.Add<int, 2>("Int2");
	EXPECT_EQ(ret, results);

	// UINT
	results[0] = 128;
	results[1] = 144;
	ret = structOffsets.Add<unsigned int, 2>("Uint1");
	EXPECT_EQ(ret, results);
	results[0] = 160;
	results[1] = 176;
	ret = structOffsets.Add<unsigned int, 2>("Uint2");
	EXPECT_EQ(ret, results);

	// FLOAT
	results[0] = 192;
	results[1] = 208;
	ret = structOffsets.Add<float, 2>("Float1");
	EXPECT_EQ(ret, results);
	results[0] = 224;
	results[1] = 240;
	ret = structOffsets.Add<float, 2>("Float2");
	EXPECT_EQ(ret, results);

	// DOUBLE
	results[0] = 256;
	results[1] = 272;
	ret = structOffsets.Add<double, 2>("Double1");
	EXPECT_EQ(ret, results);
	results[0] = 288;
	results[1] = 304;
	ret = structOffsets.Add<double, 2>("Double2");
	EXPECT_EQ(ret, results);
}

TEST(STD140Offsets, AddVectors) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, AddVectorsArray) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, AddMatrixes) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, AddMarixesArray) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, AddStruct) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, AddStructArray) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, OffsetCalculation1) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, OffsetCalculation2) {
	STD140Offsets structOffsets;
}

TEST(STD140Offsets, OffsetCalculation3) {
	STD140Offsets structOffsets;
}