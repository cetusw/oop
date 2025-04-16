#include "../Car.h"
#include "../CarController.h"
#include "catch2/catch_all.hpp"

void ProcessTest(Car& car, const std::function<void(Car&)>& cmd, const int expectedGear,
	const int expectedSpeed, const Direction& expectedDirection, const bool expectedIsTurnedOn,
	const std::string& expectedExceptionMessage = "")
{
	if (!expectedExceptionMessage.empty())
	{
		REQUIRE_THROWS_WITH(cmd(car), expectedExceptionMessage);
	}
	else
	{
		REQUIRE_NOTHROW(cmd(car));
	}

	REQUIRE(car.GetGear() == expectedGear);
	REQUIRE(car.GetSpeed() == expectedSpeed);
	REQUIRE(car.GetDirection() == expectedDirection);
	REQUIRE(car.IsTurnedOn() == expectedIsTurnedOn);
}

TEST_CASE("Управление двигателем")
{
	Car car;

	SECTION("Двигатель включается корректно")
	{
		ProcessTest(car, [](Car& c) { c.TurnOnEngine(); }, 0, 0, Direction::STANDING_STILL, true);
	}

	SECTION("Выключение двигателя при остановке")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.TurnOffEngine();
			},
			0, 0, Direction::STANDING_STILL, false);
	}

	SECTION("Попытка выключить двигатель в движении вперёд")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(1);
				c.SetSpeed(10);
				c.TurnOffEngine();
			},
			1, 10, Direction::FORWARD, true, "Cannot turn off engine while moving or gear is not neutral");
	}

	SECTION("Попытка выключить двигатель в движении назад")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(-1);
				c.SetSpeed(10);
				c.TurnOffEngine();
			},
			-1, -10, Direction::BACKWARD, true,
			"Cannot turn off engine while moving or gear is not neutral");
	}

	SECTION("Попытка выключить двигатель на первой передаче без движения")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(1);
				c.TurnOffEngine();
			},
			1, 0, Direction::STANDING_STILL, true,
			"Cannot turn off engine while moving or gear is not neutral");
	}

	SECTION("Попытка выключить двигатель на задней передаче без движения")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(-1);
				c.TurnOffEngine();
			},
			-1, 0, Direction::STANDING_STILL, true,
			"Cannot turn off engine while moving or gear is not neutral");
	}
}

TEST_CASE("Переключение передач")
{
	Car car;
	car.TurnOnEngine();

	SECTION("Недопустимая передача")
	{
		ProcessTest(
			car, [](Car& c) { c.SetGear(6); }, 0, 0, Direction::STANDING_STILL, true, "Invalid gear");
	}

	SECTION("Задняя передача на нулевой скорости")
	{
		ProcessTest(car, [](Car& c) { c.SetGear(-1); }, -1, 0, Direction::STANDING_STILL, true);
	}

	SECTION("Задняя передача при движении вперед")
	{
		car.SetGear(1);
		car.SetSpeed(10);
		ProcessTest(
			car, [](Car& c) { c.SetGear(-1); }, 1, 10, Direction::FORWARD, true,
			"Cannot reverse while moving");
	}

	SECTION("Переключение на 2 передачу с 1 передачи: скорость ниже диапазона (19)")
	{
		car.SetGear(1);
		car.SetSpeed(19);
		ProcessTest(
			car, [](Car& c) { c.SetGear(2); }, 1, 19, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 2 передачу с 1 передачи: нижняя граница (20)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		ProcessTest(car, [](Car& c) { c.SetGear(2); }, 2, 20, Direction::FORWARD, true);
	}

	SECTION("Переключение на 2 передачу с 3 передачи: верхняя граница (50)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		ProcessTest(car, [](Car& c) { c.SetGear(2); }, 2, 50, Direction::FORWARD, true);
	}

	SECTION("Переключение на 2 передачу с 3 передачи: скорость выше диапазона (51)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(51);
		ProcessTest(
			car, [](Car& c) { c.SetGear(2); }, 3, 51, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 3 передачу с 2: скорость ниже диапазона (29)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(29);
		ProcessTest(
			car, [](Car& c) { c.SetGear(3); }, 2, 29, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 3 передачу с 2: нижняя граница (30)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(30);
		ProcessTest(car, [](Car& c) { c.SetGear(3); }, 3, 30, Direction::FORWARD, true);
	}

	SECTION("Переключение на 3 передачу с 4: верхняя граница (60)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		car.SetGear(4);
		ProcessTest(car, [](Car& c) { c.SetGear(3); }, 3, 60, Direction::FORWARD, true);
	}

	SECTION("Переключение на 3 передачу с 4: скорость выше диапазона (61)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		car.SetGear(4);
		car.SetSpeed(61);
		ProcessTest(
			car, [](Car& c) { c.SetGear(3); }, 4, 61, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 4 передачу с 3: скорость ниже диапазона (39)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(39);
		car.SetGear(3);
		ProcessTest(
			car, [](Car& c) { c.SetGear(4); }, 3, 39, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 4 передачу с 3: нижняя граница (40)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(40);
		car.SetGear(3);
		ProcessTest(car, [](Car& c) { c.SetGear(4); }, 4, 40, Direction::FORWARD, true);
	}

	SECTION("Переключение на 4 передачу с 5: верхняя граница (90)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		car.SetGear(4);
		car.SetSpeed(90);
		car.SetGear(5);
		ProcessTest(car, [](Car& c) { c.SetGear(4); }, 4, 90, Direction::FORWARD, true);
	}

	SECTION("Переключение на 4 передачу с 5: скорость выше диапазона (91)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(60);
		car.SetGear(4);
		car.SetSpeed(90);
		car.SetGear(5);
		car.SetSpeed(91);
		ProcessTest(
			car, [](Car& c) { c.SetGear(4); }, 5, 91, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 5 передачу с 4: скорость ниже диапазона (49)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(49);
		car.SetGear(4);
		ProcessTest(
			car, [](Car& c) { c.SetGear(5); }, 4, 49, Direction::FORWARD, true, "Unsuitable current speed");
	}

	SECTION("Переключение на 5 передачу с 4: нижняя граница (50)")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(2);
		car.SetSpeed(50);
		car.SetGear(3);
		car.SetSpeed(50);
		car.SetGear(4);
		ProcessTest(car, [](Car& c) { c.SetGear(5); }, 5, 50, Direction::FORWARD, true);
	}
}

TEST_CASE("Управление скоростью")
{
	Car car;
	car.TurnOnEngine();

	SECTION("Установка отрицательной скорости")
	{
		car.SetGear(1);
		ProcessTest(
			car, [](Car& c) { c.SetSpeed(-30); }, 1, 0, Direction::STANDING_STILL, true,
			"Speed cannot be negative");
	}

	SECTION("Разгон на нейтрали")
	{
		car.SetGear(0);
		ProcessTest(
			car, [](Car& c) { c.SetSpeed(30); }, 0, 0, Direction::STANDING_STILL, true,
			"Cannot accelerate on neutral");
	}

	SECTION("Разгон на первой передаче")
	{
		car.SetGear(1);
		ProcessTest(car, [](Car& c) { c.SetSpeed(30); }, 1, 30, Direction::FORWARD, true);
	}

	SECTION("Превышение скорости для передачи")
	{
		car.SetGear(1);
		ProcessTest(
			car, [](Car& c) { c.SetSpeed(31); }, 1, 0, Direction::STANDING_STILL, true,
			"Speed is out of gear range");
	}

	SECTION("Торможение на нейтрали")
	{
		car.SetGear(1);
		car.SetSpeed(20);
		car.SetGear(0);
		ProcessTest(car, [](Car& c) { c.SetSpeed(15); }, 0, 15, Direction::FORWARD, true);
	}

	SECTION("Торможение на задней передаче")
	{
		car.SetGear(-1);
		car.SetSpeed(20);
		car.SetGear(0);
		ProcessTest(car, [](Car& c) { c.SetSpeed(15); }, 0, 15, Direction::BACKWARD, true);
	}

	SECTION("Движение задним ходом")
	{
		car.SetGear(-1);
		ProcessTest(car, [](Car& c) { c.SetSpeed(15); }, -1, -15, Direction::BACKWARD, true);
	}
}

TEST_CASE("Направление движения")
{
	Car car;

	SECTION("Движение вперед")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(1);
				c.SetSpeed(10);
			},
			1, 10, Direction::FORWARD, true);
	}

	SECTION("Движение назад")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(-1);
				c.SetSpeed(10);
			},
			-1, -10, Direction::BACKWARD, true);
	}

	SECTION("Остановка после движения")
	{
		ProcessTest(
			car,
			[](Car& c) {
				c.TurnOnEngine();
				c.SetGear(1);
				c.SetSpeed(10);
				c.SetGear(0);
				c.SetSpeed(0);
			},
			0, 0, Direction::STANDING_STILL, true);
	}
}

TEST_CASE("Поведение при выключенном двигателе")
{
	Car car;

	SECTION("Переключение передачи при выключенном двигателе")
	{
		ProcessTest(
			car, [](Car& c) { c.SetGear(1); }, 0, 0, Direction::STANDING_STILL, false,
			"Сannot set gear while engine is off");
	}

	SECTION("Изменение скорости при выключенном двигателе")
	{
		ProcessTest(
			car, [](Car& c) { c.SetSpeed(10); }, 0, 0, Direction::STANDING_STILL, false,
			"Cannot set speed while engine is off");
	}
}