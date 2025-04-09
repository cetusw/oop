#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H
#include "Car.h"
#include <functional>
#include <string>

class CarController
{
public:
	explicit CarController(Car& car);

	bool HandleCommand(std::string command);

private:
	bool PrintCarInfo() const;

	bool HandleTurnOnEngine() const;
	bool HandleTurnOffEngine() const;
	bool HandleSetGear(int gear) const;
	bool HandleSetSpeed(int speed) const;

	static std::vector<std::string> SplitString(std::string stringToSplit);

	static int StringToInt(const std::string& string);

	Car& m_car;

	CarCommands m_carCommands;
};

#endif // CARCONTROLLER_H
