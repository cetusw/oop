#include "CarController.h"

#include "Car.h"
#include <iostream>
#include <utility>

CarController::CarController(Car& car)
	: m_car(car)
	, m_carCommands(
		  { { "Info", [this](const std::vector<std::string>& args) { return PrintCarInfo(); } },
			  { "EngineOn",
				  [this](const std::vector<std::string>& args) { return HandleTurnOnEngine(); } },
			  { "EngineOff",
				  [this](const std::vector<std::string>& args) { return HandleTurnOffEngine(); } },
			  { "SetGear",
				  [this](const std::vector<std::string>& args) {
					  if (args.empty())
					  {
						  return false;
					  }
					  return HandleSetGear(StringToInt(args[1]));
				  } },
			  { "SetSpeed", [this](const std::vector<std::string>& args) {
				   if (args.empty())
				   {
					   return false;
				   }
				   return HandleSetSpeed(StringToInt(args[1]));
			   } } })
{
}

void CarController::HandleCommand()
{
	std::string command;
	std::getline(std::cin, command);
	const std::vector<std::string> args = SplitString(command);
	const auto it = m_carCommands.find(args[0]);
	if (it == m_carCommands.end())
	{
		std::cout << "Unknown command" << std::endl;
	}
	it->second(args);
}

void CarController::PrintCarInfo() const
{
	const std::string engineStatus = m_car.IsTurnedOn() ? "on" : "off";
	std::string currentDirection;
	switch (m_car.GetDirection())
	{
	case Direction::STANDING_STILL:
		currentDirection = "standing still";
		break;
	case Direction::FORWARD:
		currentDirection = "forward";
		break;
	case Direction::BACKWARD:
		currentDirection = "backward";
		break;
	default:
		throw std::invalid_argument("Invalid direction");
	}
	std::cout << "Engine: " << engineStatus << std::endl
			  << "Direction: " << currentDirection << std::endl
			  << "Speed: " << m_car.GetSpeed() << std::endl
			  << "Gear: " << m_car.GetGear() << std::endl;
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

std::vector<std::string> CarController::SplitString(std::string& stringToSplit)
{
	std::vector<std::string> result;
	while (stringToSplit.find(' ') != std::string::npos)
	{
		result.push_back(stringToSplit.substr(0, stringToSplit.find(' ')));
		stringToSplit.erase(0, stringToSplit.find(' ') + 1);
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

// изучить отношения между классами
