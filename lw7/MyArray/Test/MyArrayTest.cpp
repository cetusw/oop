#include "../MyArray.h"

#include <gtest/gtest.h>

template <typename T>
void MyArrayTest()
{
	const MyArray<T> myArray;
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_EQ(myArray.begin(), nullptr);
	EXPECT_EQ(myArray.end(), nullptr);
}

template <typename T>
void MyArrayCopyTest(const T& value)
{
	MyArray<T> myArray;
	myArray.PushBack(value);
	myArray.PushBack(value);
	MyArray<T> myArrayCopy(myArray);
	EXPECT_EQ(myArray.GetSize(), myArrayCopy.GetSize());
	EXPECT_EQ(myArray.GetCapacity(), myArrayCopy.GetCapacity());
	EXPECT_EQ(myArray[0], myArrayCopy[0]);
}

template <typename T>
void MyArrayMoveTest(const T& value)
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
void PushBackTest(MyArray<T>& myArray, const T& value, const size_t expectedSize, const size_t expectedCapacity)
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

template <typename T>
void ClearTest(MyArray<T>& myArray)
{
	myArray.Clear();
	EXPECT_EQ(myArray.GetSize(), 0);
	EXPECT_EQ(myArray.GetCapacity(), 0);
	EXPECT_EQ(myArray.begin(), nullptr);
}

template <typename T>
void GetSizeTest(MyArray<T>& myArray, const size_t expectedSize)
{
	EXPECT_EQ(myArray.GetSize(), expectedSize);
}

template <typename T>
void IteratorsTest(MyArray<T>& myArray, std::vector<T> expectedValues)
{
	auto it = myArray.begin();
	size_t i = 0;
	while (it != myArray.end())
	{
		EXPECT_EQ(*it, expectedValues[i]);
		++it;
		++i;
	}

	i = expectedValues.size();
	it = myArray.rbegin();
	while (it != myArray.rend())
	{
		EXPECT_EQ(*it, expectedValues[i]);
		++it;
		--i;
	}

}

template <typename T>
void GetElementByIndexTest(MyArray<T>& myArray, size_t index, T expectedValue)
{
	EXPECT_EQ(myArray[index], expectedValue);
}

template <typename T>
void AppropriationTest(MyArray<T>& firstArray, MyArray<T>& secondArray, MyArray<T>& expectedArray)
{
	auto result = firstArray + secondArray;
	for (size_t i = 0; i < result.GetSize(); i++)
	{
		EXPECT_EQ(result[i], expectedArray[i]);
	}
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