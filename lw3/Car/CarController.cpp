#include "CarController.h"

#include "Car.h"
#include <iostream>
#include <utility>

CarController::CarController(Car& car)
	: m_car(car)
	, m_carCommands({
		  { "Info", std::bind(&CarController::PrintCarInfo, this) },
		  { "EngineOn", std::bind(&CarController::HandleTurnOnEngine, this) },
		  { "EngineOff", std::bind(&CarController::HandleTurnOffEngine, this) },
		  { "SetGear", std::bind(&CarController::HandleSetGear, this, std::placeholders::_1) },
		  { "SetSpeed", std::bind(&CarController::HandleSetSpeed, this, std::placeholders::_1) },
	  })
{
}

bool CarController::HandleCommand(std::string command)
{
	const std::vector<std::string> splittedCommand = SplitString(std::move(command));
	const auto it = m_carCommands.find(splittedCommand[0]);
	if (it == m_carCommands.end())
	{
		std::cout << "Unknown command" << std::endl;
		return false;
	}
	return it->second(StringToInt(splittedCommand[1]));
}

bool CarController::PrintCarInfo() const
{
	const std::string engineStatus = m_car.IsTurnedOn() ? "on" : "off";
	std::string currentDirection;
	switch (m_car.GetDirection())
	{
	case Direction::FORWARD:
		currentDirection = "forward";
		break;
	case Direction::BACKWARD:
		currentDirection = "backward";
		break;
	case Direction::STANDING_STILL:
		currentDirection = "standing still";
	}
	std::cout << "Engine: " << engineStatus << std::endl
			  << "Direction: " << currentDirection << std::endl
			  << "Speed: " << m_car.GetSpeed() << std::endl
			  << "Gear: " << m_car.GetGear() << std::endl;
	return true;
}
bool CarController::HandleTurnOnEngine() const
{
	m_car.TurnOnEngine();
	return true;
}
bool CarController::HandleTurnOffEngine() const
{
	m_car.TurnOffEngine();
	return true;
}
bool CarController::HandleSetGear(const int gear) const
{
	m_car.SetGear(gear);
	return true;
}
bool CarController::HandleSetSpeed(const int speed) const
{
	m_car.SetSpeed(speed);
	return true;
}

std::vector<std::string> CarController::SplitString(std::string stringToSplit)
{
	std::vector<std::string> result;

	while (stringToSplit.find(' ') != std::string::npos)
	{
		result.push_back(stringToSplit.substr(0, stringToSplit.find(' ')));
		stringToSplit.erase(0, stringToSplit.find(' ') + 2);
	}
	result.push_back(stringToSplit);

	return result;
}

int CarController::StringToInt(const std::string& string)
{
	try
	{
		return std::stoi(string);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
}
