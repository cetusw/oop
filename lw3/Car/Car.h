#ifndef CAR_H
#define CAR_H
#include <fstream>
#include <functional>
#include <unordered_map>

enum class Direction // вынести
	{
	FORWARD,
	BACKWARD,
	STANDING_STILL
};

class Car
{
public:
	Car();

	void TurnOnEngine();

	void TurnOffEngine();

	bool IsTurnedOn() const;

	[[nodiscard]] int GetGear() const;

	[[nodiscard]] int GetSpeed() const;

	[[nodiscard]] Direction GetDirection() const;

	void SetGear(int gear);

	void SetSpeed(int speed);

private:
	int m_gear;
	int m_speed;
	Direction m_direction;
	bool m_isTurnedOn;
	std::unordered_map<int, std::pair<int, int>> m_gearToSpeed;
};

#endif // CAR_H
