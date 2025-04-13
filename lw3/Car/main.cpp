#include "Car.h"
#include "CarController.h"

int main()
{
    Car car;
	CarController carController(car);
    while (true)
    {
		carController.HandleCommand();
    }

	return 0;
}
