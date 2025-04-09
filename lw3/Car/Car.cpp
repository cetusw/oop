//
// Created by cetus on 4/8/25.
//

#include "Car.h"

#include <stdexcept>

Car::Car(): m_gear(0), m_speed(0),
            m_direction(Direction::STANDING_STILL),
            m_isTurnedOn(false),
            m_gearToSpeed({
                {-1, {0, 20}},
                {0, {-1, -1}},
                {1, {0, 30}},
                {2, {20, 50}},
                {3, {30, 60}},
                {4, {40, 90}},
                {5, {50, 150}}
            })
{
}

bool Car::TurnOnEngine()
{
    m_isTurnedOn = true;
    return true;
}

bool Car::TurnOffEngine()
{
    if (m_gear != 0 || m_speed != 0)
    {
        return false;
    }
    m_isTurnedOn = false;
    return true;
}

bool Car::IsTurnedOn() const
{
    return m_isTurnedOn;
}

int Car::GetGear() const
{
    return m_gear;
}

int Car::GetSpeed() const
{
    return m_speed;
}

Direction Car::GetDirection() const
{
    return m_direction;
}

void Car::SetGear(const int gear)
{
    const auto availableSpeed = m_gearToSpeed.find(gear);
    const int currentSpeed = GetSpeed();

    if (availableSpeed == m_gearToSpeed.end())
    {
        throw std::invalid_argument("Invalid gear");
    }
    if (!m_isTurnedOn)
    {
        throw std::invalid_argument("Сannot set gear while engine is off");
    }
    if (gear == -1 && currentSpeed != 0)
    {
        throw std::invalid_argument("Cannot reverse while moving");
    }
    if (currentSpeed < availableSpeed->second.first || currentSpeed > availableSpeed->second.second)
    {
        throw std::invalid_argument("Unsuitable current speed");
    }
    m_gear = gear;
}

void Car::SetSpeed(const int speed)
{
    const int currentGear = GetGear();
    const auto availableSpeed = m_gearToSpeed.find(currentGear);
    if (speed < 0)
    {
        throw std::invalid_argument("Speed cannot be negative");
    }
    if (!m_isTurnedOn)
    {
        throw std::invalid_argument("Cannot set speed while engine is off");
    }
    if (m_gear == 0)
    {
        throw std::invalid_argument("Cannot accelerate on neutral");
    }
    if (speed < availableSpeed->second.first || speed > availableSpeed->second.second)
    {
        throw std::invalid_argument("Speed is out of gear range");
    }
    m_speed = speed;
}

void Car::SetDirection(const Direction direction)
{
    m_direction = direction;
}
