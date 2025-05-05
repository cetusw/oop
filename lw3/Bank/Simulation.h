#pragma once
#include "./Actors/Apu.h"
#include "./Actors/Bart.h"
#include "./Actors/Homer.h"
#include "./Actors/Liza.h"
#include "./Actors/Marge.h"
#include "./Actors/MrBurns.h"
#include "./Actors/Nelson.h"
#include "./Actors/Smithers.h"
#include "./Actors/Snake.h"
#include "Actor.h"

#include <memory>

class Simulation
{
public:
	explicit Simulation(Money homerInitialCash, Money margeInitialCash, Money bartInitialCash,
		Money lizaInitialCash, Money apuInitialCash, Money mrBurnsInitialCash,
		Money nelsonInitialCash, Money snakeInitialCash, Money smithersInitialCash);

	void StartSimulation(int iterationsCount);
	void PrintResult() const;

	[[nodiscard]] Money GetFinalCash() const;

private:
	void GetResult();

	std::unique_ptr<Bank> m_bank;

	std::unique_ptr<Homer> m_homer;
	std::unique_ptr<Marge> m_marge;
	std::unique_ptr<Bart> m_bart;
	std::unique_ptr<Liza> m_liza;
	std::unique_ptr<Apu> m_apu;
	std::unique_ptr<MrBurns> m_mrBurns;
	std::unique_ptr<Nelson> m_nelson;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Smithers> m_smithers;

	Actors m_actors{};

	Money m_initialCash;
	Money m_finalCash;
};