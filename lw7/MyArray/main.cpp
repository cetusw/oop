#include "MyArray.h"

#include <iostream>
#include <ostream>

int main()
{
	MyArray<std::string> myArray;
	MyArray<std::string> myArray2;
	myArray.PushBack("hello");
	myArray.PushBack("hello1");
	myArray2 = myArray;
	std::cout << *myArray2.begin() << std::endl;
}