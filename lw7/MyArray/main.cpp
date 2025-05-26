#include "MyArray.h"

#include <iostream>
#include <ostream>

int main()
{
	MyArray<int> myArray1;
	MyArray<double> myArray2;
	myArray2.PushBack(1.1);
	myArray2.PushBack(1.1);
	myArray1 = myArray2;
	std::cout << myArray1[0] << std::endl;
}