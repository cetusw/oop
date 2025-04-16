//
// Created by cetus on 4/8/25.
//

#include "Car.h"

#include <stdexcept>

Car::Car()
	: m_gear(0)
	, m_speed(0)
	, m_direction(Direction::STANDING_STILL)
	, m_isTurnedOn(false)
	, m_gearToSpeed({ { -1, { 0, 20 } }, { 0, { -1, -1 } }, { 1, { 0, 30 } }, { 2, { 20, 50 } },
		  { 3, { 30, 60 } }, { 4, { 40, 90 } }, { 5, { 50, 150 } } })
{
}

void Car::TurnOnEngine() { m_isTurnedOn = true; }

void Car::TurnOffEngine()
{
	if (m_gear != 0 || m_speed != 0)
	{
		throw std::runtime_error("Cannot turn off engine while moving or gear is not neutral");
	}
	m_isTurnedOn = false;
}

bool Car::IsTurnedOn() const { return m_isTurnedOn; }

int Car::GetGear() const { return m_gear; }

int Car::GetSpeed() const { return m_speed; }

Direction Car::GetDirection() const
{
	return m_direction;
}

void Car::SetGear(const int gear)
{
	const auto availableSpeed = m_gearToSpeed.find(gear);
	if (availableSpeed == m_gearToSpeed.end())
	{
		throw std::invalid_argument("Invalid gear");
	}
	if (!m_isTurnedOn && gear != 0)
	{
		throw std::invalid_argument("Сannot set gear while engine is off");
	}
	if (gear == -1 && m_speed != 0)
	{
		throw std::invalid_argument("Cannot reverse while moving");
	}
	if ((m_speed < availableSpeed->second.first || m_speed > availableSpeed->second.second)
		&& availableSpeed->second.first != -1)
	{
		throw std::invalid_argument("Unsuitable current speed");
	}
	m_gear = gear;
}

void Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::invalid_argument("Speed cannot be negative");
	}
	if (!m_isTurnedOn)
	{
		throw std::invalid_argument("Cannot set speed while engine is off");
	}
	if (m_gear == 0 && speed > std::abs(m_speed))
	{
		throw std::invalid_argument("Cannot accelerate on neutral");
	}
	const auto availableSpeed = m_gearToSpeed.find(m_gear);
	if ((speed < availableSpeed->second.first || speed > availableSpeed->second.second)
		&& availableSpeed->second.first != -1)
	{
		throw std::invalid_argument("Speed is out of gear range");
	}
	if (m_gear == -1)
	{
		speed = -speed;
	}
	if (speed == 0)
	{
		m_direction = Direction::STANDING_STILL;
	}
	if (speed > 0 && m_gear > 0)
	{
		m_direction = Direction::FORWARD;
	}
	if (speed < 0 && m_gear < 0)
	{
		m_direction = Direction::BACKWARD;
	}
	m_speed = speed;
}
