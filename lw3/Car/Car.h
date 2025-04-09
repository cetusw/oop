//
// Created by cetus on 4/8/25.
//

#ifndef CAR_H
#define CAR_H
#include <fstream>
#include <unordered_map>

#include "Types.h"


class Car
{
public:
    Car();

    bool TurnOnEngine();

    bool TurnOffEngine();

    bool IsTurnedOn() const;

    [[nodiscard]] int GetGear() const;

    [[nodiscard]] int GetSpeed() const;

    [[nodiscard]] Direction GetDirection() const;

    void SetGear(int gear);

    void SetSpeed(int speed);

    void SetDirection(Direction direction);

private:
    int m_gear;
    int m_speed;
    Direction m_direction;
    bool m_isTurnedOn;
    std::unordered_map<int, std::pair<int, int> > m_gearToSpeed;
};


#endif //CAR_H
