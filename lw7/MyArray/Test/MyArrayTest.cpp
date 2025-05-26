#include "../MyArray.h"

#include <gtest/gtest.h>

template <typename T> void MyArrayTest()
{
	const MyArray<T> myArray;
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_EQ(myArray.begin(), nullptr);
	EXPECT_EQ(myArray.end(), nullptr);
}

template <typename T> void MyArrayCopyTest(const T& value)
{
	MyArray<T> myArray;
	myArray.PushBack(value);
	myArray.PushBack(value);
	MyArray<T> myArrayCopy(myArray);
	EXPECT_EQ(myArray.GetSize(), myArrayCopy.GetSize());
	EXPECT_EQ(myArray.GetCapacity(), myArrayCopy.GetCapacity());
	EXPECT_EQ(myArray[0], myArrayCopy[0]);
}

template <typename T> void MyArrayMoveTest(const T& value)
{
	MyArray<T> myArray;
	myArray.PushBack(value);
	myArray.PushBack(value);
	MyArray<T> myArrayMove(std::move(myArray));
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_EQ(myArray.begin(), nullptr);
	EXPECT_EQ(*myArrayMove.begin(), value);
}

template <typename T>
void PushBackTest(
	MyArray<T>& myArray, const T& value, const size_t expectedSize, const size_t expectedCapacity)
{
	myArray.PushBack(value);
	EXPECT_EQ(myArray.GetSize(), expectedSize);
	EXPECT_EQ(myArray.GetCapacity(), expectedCapacity);
	EXPECT_EQ(myArray[myArray.GetSize() - 1], value);
}

template <typename T>
void ResizeTest(MyArray<T>& myArray, size_t newCapacity, const size_t expectedSize)
{
	myArray.Resize(newCapacity);
	EXPECT_EQ(myArray.GetSize(), expectedSize);
	EXPECT_EQ(myArray.GetCapacity(), newCapacity);
}

template <typename T> void ClearTest(MyArray<T>& myArray)
{
	myArray.Clear();
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_EQ(myArray.begin(), nullptr);
}

template <typename T> void GetSizeTest(MyArray<T>& myArray, const size_t expectedSize)
{
	EXPECT_EQ(myArray.GetSize(), expectedSize);
}

template <typename T> void IteratorsTest(MyArray<T>& myArray, std::vector<T> expectedValues)
{
	auto it = myArray.begin();
	size_t i = 0;
	while (it != myArray.end())
	{
		EXPECT_EQ(*it, expectedValues[i]);
		++it;
		++i;
	}

	i = expectedValues.size() - 1;
	auto revit = myArray.rbegin();
	while (revit != myArray.rend())
	{
		EXPECT_EQ(*revit, expectedValues[i]);
		++revit;
		--i;
	}
}

template <typename T> void GetElementByIndexTest(MyArray<T>& myArray, std::vector<T> expectedValues)
{
	for (int i = 0; i < myArray.GetSize(); i++)
	{
		EXPECT_EQ(myArray[i], expectedValues[i]);
	}
	EXPECT_THROW(myArray[myArray.GetSize()], std::out_of_range);
	EXPECT_THROW(myArray[-1], std::out_of_range);
}

template <typename T, typename U>
void AppropriationTest(MyArray<T>& firstArray, MyArray<U>& secondArray, const bool expectException = false)
{
	if (expectException)
	{
		EXPECT_THROW(firstArray = secondArray, std::invalid_argument);
		return;
	}

	firstArray = secondArray;
	for (size_t i = 0; i < firstArray.GetSize(); i++)
	{
		EXPECT_EQ(firstArray[i], secondArray[i]);
	}
	EXPECT_EQ(firstArray.GetSize(), secondArray.GetSize());
}

TEST(MyArrayTest, Constructors)
{
	MyArrayTest<int>();
	MyArrayTest<float>();
	MyArrayTest<double>();
	MyArrayTest<char>();
	MyArrayTest<std::string>();
}

TEST(MyArrayTest, CopyConstructors)
{
	MyArrayCopyTest<int>(1);
	MyArrayCopyTest<int>(-1);
	MyArrayCopyTest<int>(0);
	MyArrayCopyTest<float>(1.1);
	MyArrayCopyTest<float>(-1.1);
	MyArrayCopyTest<float>(0);
	MyArrayCopyTest<double>(1.1);
	MyArrayCopyTest<double>(-1.1);
	MyArrayCopyTest<double>(0);
	MyArrayCopyTest<char>('a');
	MyArrayCopyTest<std::string>("hello");
	MyArrayCopyTest<std::string>("");
}

TEST(MyArrayTest, MoveConstructors)
{
	MyArrayMoveTest<int>(1);
	MyArrayMoveTest<int>(-1);
	MyArrayMoveTest<int>(0);
	MyArrayMoveTest<float>(1.1);
	MyArrayMoveTest<float>(-1.1);
	MyArrayMoveTest<float>(0);
	MyArrayMoveTest<double>(1.1);
	MyArrayMoveTest<double>(-1.1);
	MyArrayMoveTest<double>(0);
	MyArrayMoveTest<char>('a');
	MyArrayMoveTest<std::string>("hello");
	MyArrayMoveTest<std::string>("");
}

TEST(PushBackTest, SinglePush)
{
	MyArray<int> arrInt;
	PushBackTest<int>(arrInt, 1, 1, 1);

	MyArray<float> arrFloat;
	PushBackTest<float>(arrFloat, 1.1, 1, 1);

	MyArray<std::string> arrStr;
	PushBackTest<std::string>(arrStr, "hello", 1, 1);
}

TEST(PushBackTest, ZeroPush)
{
	MyArray<int> arrInt;
	PushBackTest<int>(arrInt, 0, 1, 1);

	MyArray<float> arrFloat;
	PushBackTest<float>(arrFloat, 0, 1, 1);

	MyArray<std::string> arrStr;
	PushBackTest<std::string>(arrStr, "", 1, 1);
}

TEST(PushBackTest, MultiplePush)
{
	MyArray<int> arrInt;
	PushBackTest<int>(arrInt, 1, 1, 1);
	PushBackTest<int>(arrInt, 100, 2, 2);
	PushBackTest<int>(arrInt, -5, 3, 4);

	MyArray<float> arrFloat;
	PushBackTest<float>(arrFloat, 1.1, 1, 1);
	PushBackTest<float>(arrFloat, 1.5, 2, 2);
	PushBackTest<float>(arrFloat, 3.14, 3, 4);

	MyArray<std::string> arrStr;
	PushBackTest<std::string>(arrStr, "hello", 1, 1);
	PushBackTest<std::string>(arrStr, "world", 2, 2);
	PushBackTest<std::string>(arrStr, "!", 3, 4);
}

TEST(ResizeTest, ResizeByZero)
{
	MyArray<int> arrInt;
	ResizeTest<int>(arrInt, 0, 0);

	MyArray<float> arrFloat;
	ResizeTest<float>(arrFloat, 0, 0);

	MyArray<std::string> arrStr;
	ResizeTest<std::string>(arrStr, 0, 0);
}

TEST(ResizeTest, ResizeByOne)
{
	MyArray<int> arrInt;
	ResizeTest<int>(arrInt, 1, 0);

	MyArray<float> arrFloat;
	ResizeTest<float>(arrFloat, 1, 0);

	MyArray<std::string> arrStr;
	ResizeTest<std::string>(arrStr, 1, 0);
}

TEST(ResizeTest, ResizeByMore)
{
	MyArray<int> arrInt;
	ResizeTest<int>(arrInt, 5, 0);

	MyArray<float> arrFloat;
	ResizeTest<float>(arrFloat, 5, 0);

	MyArray<std::string> arrStr;
	ResizeTest<std::string>(arrStr, 5, 0);
}

TEST(ResizeTest, ResizeNotAffectValues)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	ResizeTest<int>(arrInt, 5, 1);

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	ResizeTest<float>(arrFloat, 5, 1);

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	ResizeTest<std::string>(arrStr, 5, 1);
}

TEST(ResizeTest, ResizeAffectValues)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	ResizeTest<int>(arrInt, 0, 0);

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	ResizeTest<float>(arrFloat, 0, 0);

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	ResizeTest<std::string>(arrStr, 0, 0);
}

TEST(ClearTest, EmptyArray)
{
	MyArray<int> arrInt;
	ClearTest(arrInt);

	MyArray<float> arrFloat;
	ClearTest(arrFloat);

	MyArray<std::string> arrStr;
	ClearTest(arrStr);
}

TEST(ClearTest, ArrayWithValue)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	ClearTest(arrInt);

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	ClearTest(arrFloat);

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	ClearTest(arrStr);
}

TEST(ClearTest, ArrayWithValues)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	arrInt.PushBack(2);
	arrInt.PushBack(3);
	ClearTest(arrInt);

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	arrFloat.PushBack(1.3);
	arrFloat.PushBack(1.4);
	ClearTest(arrFloat);

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	arrStr.PushBack("world");
	arrStr.PushBack("!");
	ClearTest(arrStr);
}

TEST(ClearTest, ArrayWithNegativeValues)
{
	MyArray<int> arrInt;
	arrInt.PushBack(-1);
	arrInt.PushBack(-2);
	arrInt.PushBack(-3);
	ClearTest(arrInt);

	MyArray<float> arrFloat;
	arrFloat.PushBack(-1.2);
	arrFloat.PushBack(-1.3);
	arrFloat.PushBack(-1.4);
	ClearTest(arrFloat);
}

TEST(ClearTest, EmptyStringArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	ClearTest(arrStr);
}

TEST(ClearTest, EmptyStringsArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	arrStr.PushBack("");
	ClearTest(arrStr);
}

TEST(GetSizeTest, EmptyArray)
{
	MyArray<int> arrInt;
	GetSizeTest(arrInt, 0);

	MyArray<float> arrFloat;
	GetSizeTest(arrFloat, 0);

	MyArray<std::string> arrStr;
	GetSizeTest(arrStr, 0);
}

TEST(GetSizeTest, OneElementArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	GetSizeTest(arrInt, 1);

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	GetSizeTest(arrFloat, 1);

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	GetSizeTest(arrStr, 1);
}

TEST(GetSizeTest, ManyElementsArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	arrInt.PushBack(2);
	arrInt.PushBack(3);
	GetSizeTest(arrInt, 3);

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	arrFloat.PushBack(1.3);
	arrFloat.PushBack(1.4);
	GetSizeTest(arrFloat, 3);

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	arrStr.PushBack("world");
	arrStr.PushBack("!");
	GetSizeTest(arrStr, 3);
}

TEST(GetSizeTest, NegativeElementsArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(-1);
	arrInt.PushBack(-2);
	arrInt.PushBack(-3);
	GetSizeTest(arrInt, 3);

	MyArray<float> arrFloat;
	arrFloat.PushBack(-1.2);
	arrFloat.PushBack(-1.3);
	arrFloat.PushBack(-1.4);
	GetSizeTest(arrFloat, 3);
}

TEST(GetSizeTest, EmptyStringArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	GetSizeTest(arrStr, 1);
}

TEST(GetSizeTest, EmptyStringsArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	arrStr.PushBack("");
	GetSizeTest(arrStr, 2);
}

TEST(IteratorsTest, EmptyArray)
{
	MyArray<int> arrInt;
	IteratorsTest(arrInt, {});

	MyArray<float> arrFloat;
	IteratorsTest(arrFloat, {});

	MyArray<std::string> arrStr;
	IteratorsTest(arrStr, {});
}

TEST(IteratorsTest, OneElementArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	IteratorsTest(arrInt, { 1 });

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	IteratorsTest(arrFloat, { 1.2 });

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	IteratorsTest(arrStr, { "hello" });
}

TEST(IteratorsTest, ManyElementsArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	arrInt.PushBack(2);
	arrInt.PushBack(3);
	IteratorsTest(arrInt, { 1, 2, 3 });

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	arrFloat.PushBack(1.3);
	arrFloat.PushBack(1.4);
	IteratorsTest(arrFloat, { 1.2, 1.3, 1.4 });

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	arrStr.PushBack("world");
	arrStr.PushBack("!");
	IteratorsTest(arrStr, { "hello", "world", "!" });
}

TEST(IteratorsTest, NegativeElementsArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(-1);
	arrInt.PushBack(-2);
	arrInt.PushBack(-3);
	IteratorsTest(arrInt, { -1, -2, -3 });

	MyArray<float> arrFloat;
	arrFloat.PushBack(-1.2);
	arrFloat.PushBack(-1.3);
	arrFloat.PushBack(-1.4);
	IteratorsTest(arrFloat, { -1.2, -1.3, -1.4 });
}

TEST(IteratorsTest, EmptyStringArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	IteratorsTest(arrStr, { "" });
}

TEST(IteratorsTest, EmptyStringsArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	arrStr.PushBack("");
	IteratorsTest(arrStr, { "", "" });
}

TEST(GetElementByIndexTest, EmptyArray)
{
	MyArray<int> arrInt;
	GetElementByIndexTest(arrInt, {});

	MyArray<float> arrFloat;
	GetElementByIndexTest(arrFloat, {});

	MyArray<std::string> arrStr;
	GetElementByIndexTest(arrInt, {});
}

TEST(GetElementByIndexTest, OneElementArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	GetElementByIndexTest(arrInt, {1});

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	GetElementByIndexTest(arrFloat, { 1.2 });

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	GetElementByIndexTest(arrStr, { "hello" });
}

TEST(GetElementByIndexTest, ManyElementsArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(1);
	arrInt.PushBack(2);
	arrInt.PushBack(3);
	GetElementByIndexTest(arrInt, { 1, 2, 3 });

	MyArray<float> arrFloat;
	arrFloat.PushBack(1.2);
	arrFloat.PushBack(1.3);
	arrFloat.PushBack(1.4);
	GetElementByIndexTest(arrFloat, { 1.2, 1.3, 1.4 });

	MyArray<std::string> arrStr;
	arrStr.PushBack("hello");
	arrStr.PushBack("world");
	arrStr.PushBack("!");
	GetElementByIndexTest(arrStr, { "hello", "world", "!" });
}

TEST(GetElementByIndexTest, NegativeElementsArray)
{
	MyArray<int> arrInt;
	arrInt.PushBack(-1);
	arrInt.PushBack(-2);
	arrInt.PushBack(-3);
	GetElementByIndexTest(arrInt, { -1, -2, -3 });

	MyArray<float> arrFloat;
	arrFloat.PushBack(-1.2);
	arrFloat.PushBack(-1.3);
	arrFloat.PushBack(-1.4);
	GetElementByIndexTest(arrFloat, { -1.2, -1.3, -1.4 });
}

TEST(GetElementByIndexTest, EmptyStringArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	GetElementByIndexTest(arrStr, { "" });
}

TEST(GetElementByIndexTest, EmptyStringsArray)
{
	MyArray<std::string> arrStr;
	arrStr.PushBack("");
	arrStr.PushBack("");
	GetElementByIndexTest(arrStr, { "", "" });
}

TEST(AppropriationTest, EmptyArrayAssignEmptyArray)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, EmptyArrayAssignArrayWithOneElement)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt2.PushBack(1);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat2.PushBack(1.2);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr2.PushBack("hello");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithOneElementAssignEmptyArray)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(1);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(1.2);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("hello");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, EmptyArrayAssignArrayWithManyElements)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt2.PushBack(1);
	arrInt2.PushBack(2);
	arrInt2.PushBack(3);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat2.PushBack(1.2);
	arrFloat2.PushBack(1.3);
	arrFloat2.PushBack(1.4);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr2.PushBack("hello");
	arrStr2.PushBack("world");
	arrStr2.PushBack("!");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithManyElementsAssignEmptyArray)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(1);
	arrInt1.PushBack(2);
	arrInt1.PushBack(3);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(1.2);
	arrFloat1.PushBack(1.3);
	arrFloat1.PushBack(1.4);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("hello");
	arrStr1.PushBack("world");
	arrStr1.PushBack("!");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithLessElementsAssignArrayWithMoreElements)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(0);
	arrInt2.PushBack(1);
	arrInt2.PushBack(2);
	arrInt2.PushBack(3);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(1.1);
	arrFloat2.PushBack(1.2);
	arrFloat2.PushBack(1.3);
	arrFloat2.PushBack(1.4);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("hello1");
	arrStr2.PushBack("hello");
	arrStr2.PushBack("world");
	arrStr2.PushBack("!");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithMoreElementsAssignArrayWithLessElements)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(1);
	arrInt1.PushBack(2);
	arrInt1.PushBack(3);
	arrInt2.PushBack(4);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(1.2);
	arrFloat1.PushBack(1.3);
	arrFloat1.PushBack(1.4);
	arrFloat2.PushBack(1.5);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("hello");
	arrStr1.PushBack("world");
	arrStr1.PushBack("!");
	arrStr2.PushBack("!");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, EmptyArrayAssignArrayWithOneElementNegative)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt2.PushBack(-1);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat2.PushBack(-1.2);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr2.PushBack("");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithOneElementAssignEmptyArrayNegative)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(-1);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(-1.2);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, EmptyArrayAssignArrayWithManyElementsNegative)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt2.PushBack(-1);
	arrInt2.PushBack(-2);
	arrInt2.PushBack(-3);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat2.PushBack(-1.2);
	arrFloat2.PushBack(-1.3);
	arrFloat2.PushBack(-1.4);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr2.PushBack("");
	arrStr2.PushBack("");
	arrStr2.PushBack("");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithManyElementsAssignEmptyArrayNegative)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(-1);
	arrInt1.PushBack(-2);
	arrInt1.PushBack(-3);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(-1.2);
	arrFloat1.PushBack(-1.3);
	arrFloat1.PushBack(-1.4);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithLessElementsAssignArrayWithMoreElementsNegative)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(0);
	arrInt2.PushBack(-1);
	arrInt2.PushBack(-2);
	arrInt2.PushBack(-3);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(-1.1);
	arrFloat2.PushBack(-1.2);
	arrFloat2.PushBack(-1.3);
	arrFloat2.PushBack(-1.4);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("");
	arrStr2.PushBack("");
	arrStr2.PushBack("");
	arrStr2.PushBack("");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, ArrayWithMoreElementsAssignArrayWithLessElementsNegstive)
{
	MyArray<int> arrInt1;
	MyArray<int> arrInt2;
	arrInt1.PushBack(-1);
	arrInt1.PushBack(-2);
	arrInt1.PushBack(-3);
	arrInt2.PushBack(-4);
	AppropriationTest(arrInt1, arrInt2);

	MyArray<float> arrFloat1;
	MyArray<float> arrFloat2;
	arrFloat1.PushBack(-1.2);
	arrFloat1.PushBack(-1.3);
	arrFloat1.PushBack(-1.4);
	arrFloat2.PushBack(-1.5);
	AppropriationTest(arrFloat1, arrFloat2);

	MyArray<std::string> arrStr1;
	MyArray<std::string> arrStr2;
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	arrStr2.PushBack("");
	AppropriationTest(arrStr1, arrStr2);
}

TEST(AppropriationTest, AssignSameEmptyArray)
{
	MyArray<int> arrInt1;
	AppropriationTest(arrInt1, arrInt1);

	MyArray<float> arrFloat1;
	AppropriationTest(arrFloat1, arrFloat1);

	MyArray<std::string> arrStr1;
	AppropriationTest(arrStr1, arrStr1);
}

TEST(AppropriationTest, AssignSameArrayWithElements)
{
	MyArray<int> arrInt1;
	arrInt1.PushBack(1);
	arrInt1.PushBack(2);
	arrInt1.PushBack(3);
	AppropriationTest(arrInt1, arrInt1);

	MyArray<float> arrFloat1;
	arrFloat1.PushBack(1.2);
	arrFloat1.PushBack(1.3);
	arrFloat1.PushBack(1.4);
	AppropriationTest(arrFloat1, arrFloat1);

	MyArray<std::string> arrStr1;
	arrStr1.PushBack("hello");
	arrStr1.PushBack("world");
	arrStr1.PushBack("!");
	AppropriationTest(arrStr1, arrStr1);
}

TEST(AppropriationTest, AssignSameArrayWithNegativeElements)
{
	MyArray<int> arrInt1;
	arrInt1.PushBack(-1);
	arrInt1.PushBack(-2);
	arrInt1.PushBack(-3);
	AppropriationTest(arrInt1, arrInt1);

	MyArray<float> arrFloat1;
	arrFloat1.PushBack(-1.2);
	arrFloat1.PushBack(-1.3);
	arrFloat1.PushBack(-1.4);
	AppropriationTest(arrFloat1, arrFloat1);

	MyArray<std::string> arrStr1;
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	AppropriationTest(arrStr1, arrStr1);
}

TEST(AppropriationTest, AssignSameArrayWithZeroElements)
{
	MyArray<int> arrInt1;
	arrInt1.PushBack(0);
	arrInt1.PushBack(0);
	arrInt1.PushBack(0);
	AppropriationTest(arrInt1, arrInt1);

	MyArray<float> arrFloat1;
	arrFloat1.PushBack(0);
	arrFloat1.PushBack(0);
	arrFloat1.PushBack(0);
	AppropriationTest(arrFloat1, arrFloat1);

	MyArray<std::string> arrStr1;
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	arrStr1.PushBack("");
	AppropriationTest(arrStr1, arrStr1);
}

TEST(AppropriationTest, EmptyArrayAssignEmptyArrayWithCast)
{
	MyArray<int> arrInt1;
	MyArray<double> arrDouble1;
	AppropriationTest(arrInt1, arrDouble1);

	MyArray<double> arrDouble2;
	MyArray<int> arrInt2;
	AppropriationTest(arrDouble2, arrInt2);

	MyArray<int> arrInt3;
	MyArray<float> arrFloat1;
	AppropriationTest(arrInt3, arrFloat1);

	MyArray<float> arrFloat2;
	MyArray<int> arrInt4;
	AppropriationTest(arrFloat2, arrInt4);

	MyArray<float> arrFloat3;
	MyArray<double> arrDouble3;
	AppropriationTest(arrFloat3, arrDouble3);

	MyArray<double> arrDouble4;
	MyArray<float> arrFloat4;
	AppropriationTest(arrDouble4, arrFloat4);
}

TEST(AppropriationTest, EmptyArrayAssignArrayWithElementsWithCast)
{
	MyArray<int> arrInt1;
	MyArray<double> arrDouble1;
	arrDouble1.PushBack(1);
	AppropriationTest(arrInt1, arrDouble1);

	MyArray<double> arrDouble2;
	MyArray<int> arrInt2;
	arrInt2.PushBack(2);
	AppropriationTest(arrDouble2, arrInt2);

	MyArray<int> arrInt3;
	MyArray<float> arrFloat1;
	arrFloat1.PushBack(1);
	AppropriationTest(arrInt3, arrFloat1);

	MyArray<float> arrFloat2;
	MyArray<int> arrInt4;
	arrInt4.PushBack(2);
	AppropriationTest(arrFloat2, arrInt4);

	MyArray<float> arrFloat3;
	MyArray<double> arrDouble3;
	arrDouble3.PushBack(1);
	AppropriationTest(arrFloat3, arrDouble3);

	MyArray<double> arrDouble4;
	MyArray<float> arrFloat4;
	arrFloat4.PushBack(1);
	AppropriationTest(arrDouble4, arrFloat4);
}

TEST(AppropriationTest, ArrayWithElementsAssignEmptyArrayWithCast)
{
	MyArray<int> arrInt1;
	MyArray<double> arrDouble1;
	arrInt1.PushBack(1);
	AppropriationTest(arrInt1, arrDouble1);

	MyArray<double> arrDouble2;
	MyArray<int> arrInt2;
	arrDouble2.PushBack(2);
	AppropriationTest(arrDouble2, arrInt2);

	MyArray<int> arrInt3;
	MyArray<float> arrFloat1;
	arrInt3.PushBack(1);
	AppropriationTest(arrInt3, arrFloat1);

	MyArray<float> arrFloat2;
	MyArray<int> arrInt4;
	arrFloat2.PushBack(2);
	AppropriationTest(arrFloat2, arrInt4);

	MyArray<float> arrFloat3;
	MyArray<double> arrDouble3;
	arrFloat3.PushBack(1);
	AppropriationTest(arrFloat3, arrDouble3);

	MyArray<double> arrDouble4;
	MyArray<float> arrFloat4;
	arrDouble4.PushBack(1);
	AppropriationTest(arrDouble4, arrFloat4);
}

TEST(AppropriationTest, ArrayWithElementsAssignArrayWithElementsWithCast)
{
	MyArray<int> arrInt1;
	MyArray<double> arrDouble1;
	arrInt1.PushBack(1);
	arrDouble1.PushBack(2);
	AppropriationTest(arrInt1, arrDouble1);

	MyArray<double> arrDouble2;
	MyArray<int> arrInt2;
	arrDouble2.PushBack(2);
	arrInt2.PushBack(3);
	AppropriationTest(arrDouble2, arrInt2);

	MyArray<int> arrInt3;
	MyArray<float> arrFloat1;
	arrInt3.PushBack(1);
	arrFloat1.PushBack(2);
	AppropriationTest(arrInt3, arrFloat1);

	MyArray<float> arrFloat2;
	MyArray<int> arrInt4;
	arrFloat2.PushBack(2);
	arrInt4.PushBack(3);
	AppropriationTest(arrFloat2, arrInt4);

	MyArray<float> arrFloat3;
	MyArray<double> arrDouble3;
	arrFloat3.PushBack(1);
	arrDouble3.PushBack(2);
	AppropriationTest(arrFloat3, arrDouble3);

	MyArray<double> arrDouble4;
	MyArray<float> arrFloat4;
	arrDouble4.PushBack(1);
	arrFloat4.PushBack(2);
	AppropriationTest(arrDouble4, arrFloat4);
}

TEST(AppropriationTest, ArrayWithLessElementsAssignArrayWithMoreElementsWithCast)
{
	MyArray<int> arrInt1;
	MyArray<double> arrDouble1;
	arrInt1.PushBack(1);
	arrDouble1.PushBack(2);
	arrDouble1.PushBack(2);
	AppropriationTest(arrInt1, arrDouble1);

	MyArray<double> arrDouble2;
	MyArray<int> arrInt2;
	arrDouble2.PushBack(2);
	arrInt2.PushBack(3);
	arrInt2.PushBack(3);
	AppropriationTest(arrDouble2, arrInt2);

	MyArray<int> arrInt3;
	MyArray<float> arrFloat1;
	arrInt3.PushBack(1);
	arrFloat1.PushBack(2);
	arrFloat1.PushBack(2);
	AppropriationTest(arrInt3, arrFloat1);

	MyArray<float> arrFloat2;
	MyArray<int> arrInt4;
	arrFloat2.PushBack(2);
	arrInt4.PushBack(3);
	arrInt4.PushBack(3);
	AppropriationTest(arrFloat2, arrInt4);

	MyArray<float> arrFloat3;
	MyArray<double> arrDouble3;
	arrFloat3.PushBack(1);
	arrDouble3.PushBack(2);
	arrDouble3.PushBack(2);
	AppropriationTest(arrFloat3, arrDouble3);

	MyArray<double> arrDouble4;
	MyArray<float> arrFloat4;
	arrDouble4.PushBack(1);
	arrFloat4.PushBack(2);
	arrFloat4.PushBack(2);
	AppropriationTest(arrDouble4, arrFloat4);
}