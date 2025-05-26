#include "../FindMaxEx.h"
#include "../Sportsman.h"
#include <gtest/gtest.h>

struct TestStructure
{
	int intValue{};
	float floatValue{};
	char charValue{};
	std::string stringValue;
};

void FindMaxExTest(const std::vector<TestStructure>& structure,
	const TestStructure& expectedMaxIntValue, const TestStructure& expectedMinIntValue,
	const TestStructure& expectedMaxFloatValue, const TestStructure& expectedMinFloatValue,
	const TestStructure& expectedMaxCharValue, const TestStructure& expectedMinCharValue,
	const TestStructure& expectedMaxStringValue, const TestStructure& expectedMinStringValue, bool expectException = false)
{
	TestStructure maxIntValue;
	TestStructure minIntValue;
	TestStructure maxFloatValue;
	TestStructure minFloatValue;
	TestStructure maxCharValue;
	TestStructure minCharValue;
	TestStructure maxStringValue;
	TestStructure minStringValue;

	if (expectException)
	{
		auto returnException = [](const TestStructure& a, const TestStructure& b) {
			throw std::runtime_error("Comparison failed!");
			return a.intValue < b.intValue;
		};

		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, maxIntValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, minIntValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, maxFloatValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, minFloatValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, maxCharValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, minCharValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, maxStringValue, returnException));
		EXPECT_FALSE(FindMaxEx<TestStructure>(structure, minStringValue, returnException));
		return;
	}

	auto returnMaxIntValue
		= [](const TestStructure& a, const TestStructure& b) { return a.intValue < b.intValue; };
	auto returnMinIntValue
		= [](const TestStructure& a, const TestStructure& b) { return a.intValue > b.intValue; };
	auto returnMaxFloatValue = [](const TestStructure& a, const TestStructure& b) {
		return a.floatValue < b.floatValue;
	};
	auto returnMinFloatValue = [](const TestStructure& a, const TestStructure& b) {
		return a.floatValue > b.floatValue;
	};
	auto returnMaxCharValue
		= [](const TestStructure& a, const TestStructure& b) { return a.charValue < b.charValue; };
	auto returnMinCharValue
		= [](const TestStructure& a, const TestStructure& b) { return a.charValue > b.charValue; };
	auto returnMaxStringValue = [](const TestStructure& a, const TestStructure& b) {
		return a.stringValue < b.stringValue;
	};
	auto returnMinStringValue = [](const TestStructure& a, const TestStructure& b) {
		return a.stringValue > b.stringValue;
	};

	FindMaxEx<TestStructure>(structure, maxIntValue, returnMaxIntValue);
	FindMaxEx<TestStructure>(structure, minIntValue, returnMinIntValue);
	FindMaxEx<TestStructure>(structure, maxFloatValue, returnMaxFloatValue);
	FindMaxEx<TestStructure>(structure, minFloatValue, returnMinFloatValue);
	FindMaxEx<TestStructure>(structure, maxCharValue, returnMaxCharValue);
	FindMaxEx<TestStructure>(structure, minCharValue, returnMinCharValue);
	FindMaxEx<TestStructure>(structure, maxStringValue, returnMaxStringValue);
	FindMaxEx<TestStructure>(structure, minStringValue, returnMinStringValue);

	EXPECT_EQ(maxIntValue.intValue, expectedMaxIntValue.intValue);
	EXPECT_EQ(minIntValue.intValue, expectedMinIntValue.intValue);
	EXPECT_EQ(maxFloatValue.floatValue, expectedMaxFloatValue.floatValue);
	EXPECT_EQ(minFloatValue.floatValue, expectedMinFloatValue.floatValue);
	EXPECT_EQ(maxCharValue.charValue, expectedMaxCharValue.charValue);
	EXPECT_EQ(minCharValue.charValue, expectedMinCharValue.charValue);
	EXPECT_EQ(maxStringValue.stringValue, expectedMaxStringValue.stringValue);
	EXPECT_EQ(minStringValue.stringValue, expectedMinStringValue.stringValue);
}

TEST(FindMaxExTest, Empty)
{
	const TestStructure t = {};
	FindMaxExTest({}, t, t, t, t, t, t, t, t);
}

TEST(FindMaxExTest, SingleElement)
{
	TestStructure t = { 1, 1.1f, 'A', "Test" };
	FindMaxExTest({ t }, t, t, t, t, t, t, t, t);
}

TEST(FindMaxExTest, ZeroValues)
{
	TestStructure t = { 0, 0.0f, '\0', "" };
	FindMaxExTest({ t }, t, t, t, t, t, t, t, t);
}

TEST(FindMaxExTest, MultipleElementsSameValues)
{
	TestStructure t1 = { 10, 1.1f, 'X', "Test" };
	TestStructure t2 = { 10, 1.1f, 'X', "Test" };
	FindMaxExTest({ t1, t2 }, t1, t1, t1, t1, t1, t1, t1, t1);
}

TEST(FindMaxExTest, MultipleElementsDifferentValues)
{
	TestStructure t1 = { 10, 1.5f, 'A', "Test1" };
	TestStructure t2 = { 20, 1.1f, 'B', "Test2" };
	TestStructure t3 = { 15, 1.3f, 'C', "Test3" };
	FindMaxExTest({ t1, t2, t3 }, t2, t1,
		t1, t2,
		t3, t1,
		t3, t1);
}

TEST(FindMaxExTest, NegativeValues)
{
	TestStructure t1 = { -10, -1.5f, 'A', "Test1" };
	TestStructure t2 = { -20, -1.1f, 'B', "Test2" };
	FindMaxExTest({ t1, t2 }, t1, t2,
		t2, t1,
		t2, t1,
		t2, t1);
}

TEST(FindMaxExTest, MixedPositiveNegative)
{
	TestStructure t1 = { -10, 1.5f, 'A', "Test1" };
	TestStructure t2 = { 20, -1.1f, 'B', "Test2" };
	FindMaxExTest({ t1, t2 }, t2, t1,
		t1, t2,
		t2, t1,
		t2, t1);
}

TEST(FindMaxExTest, OnlyIntValueDifferent)
{
	TestStructure t1 = { 10, 1.0f, 'A', "Test" };
	TestStructure t2 = { 20, 1.0f, 'A', "Test" };
	FindMaxExTest({ t1, t2 }, t2, t1,
		t1, t1,
		t1, t1,
		t1, t1);
}

TEST(FindMaxExTest, OnlyIntValueDifferentReverse)
{
	TestStructure t1 = { 20, 1.0f, 'A', "Test" };
	TestStructure t2 = { 10, 1.0f, 'A', "Test" };
	FindMaxExTest({ t1, t2 }, t1, t2,
		t1, t1,
		t1, t1,
		t1, t1);
}

TEST(FindMaxExTest, OnlyFloatValueDifferent)
{
	TestStructure t1 = { 10, 1.0f, 'A', "Test" };
	TestStructure t2 = { 10, 1.1f, 'A', "Test" };
	FindMaxExTest({ t1, t2 }, t1, t1,
		t2, t1,
		t1, t1,
		t1, t1);
}

TEST(FindMaxExTest, OnlyFloatValueDifferentReverse)
{
	TestStructure t1 = { 10, 1.1f, 'A', "Test" };
	TestStructure t2 = { 10, 1.0f, 'A', "Test" };
	FindMaxExTest({ t1, t2 }, t1, t1,
		t1, t2,
		t1, t1,
		t1, t1);
}

TEST(FindMaxExTest, OnlyCharValueDifferent)
{
	TestStructure t1 = { 10, 1.1f, 'A', "Test" };
	TestStructure t2 = { 10, 1.1f, 'B', "Test" };
	FindMaxExTest({ t1, t2 }, t1, t1,
		t1, t1,
		t2, t1,
		t1, t1);
}

TEST(FindMaxExTest, OnlyCharValueDifferentReverse)
{
	TestStructure t1 = { 10, 1.1f, 'B', "Test" };
	TestStructure t2 = { 10, 1.1f, 'A', "Test" };
	FindMaxExTest({ t1, t2 }, t1, t1,
		t1, t1,
		t1, t2,
		t1, t1);
}

TEST(FindMaxExTest, OnlyStringValueDifferent)
{
	TestStructure t1 = { 10, 1.1f, 'A', "Test1" };
	TestStructure t2 = { 10, 1.1f, 'A', "Test2" };
	FindMaxExTest({ t1, t2 }, t1, t1,
		t1, t1,
		t1, t1,
		t2, t1);
}

TEST(FindMaxExTest, OnlyStringValueDifferentReverse)
{
	TestStructure t1 = { 10, 1.1f, 'A', "Test2" };
	TestStructure t2 = { 10, 1.1f, 'A', "Test1" };
	FindMaxExTest({ t1, t2 }, t1, t1,
		t1, t1,
		t1, t1,
		t1, t2);
}

TEST(FindMaxExTest, Exception)
{
	const TestStructure t = {};
	FindMaxExTest({}, t, t, t, t, t, t, t, t, true);
}

// TODO: проверить исключение. отвязать от спорстменов ++
