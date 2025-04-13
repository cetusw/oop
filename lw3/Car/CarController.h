#ifndef CARCONTROLLER_H
#define CARCONTROLLER_H
#include "Car.h"
#include <functional>
#include <string>

class CarController
{
public:
	explicit CarController(Car& car);

	void HandleCommand();

private:
	void PrintCarInfo() const;

	bool HandleTurnOnEngine() const;
	bool HandleTurnOffEngine() const;
	bool HandleSetGear(int gear) const;
	bool HandleSetSpeed(int speed) const;

	static std::vector<std::string> SplitString(std::string& stringToSplit);

	static int StringToInt(const std::string& string);

	Car& m_car;

	using CarCommands
		= std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>>;
	CarCommands m_carCommands;
};

#endif // CARCONTROLLER_H
