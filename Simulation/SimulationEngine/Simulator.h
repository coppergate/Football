#pragma once

#include "Ball.h"
#include "Enums.h"
#include "Manager.h"
#include "Player.h"
#include "Team.h"
#include "Types.h"


namespace FootballSimulation
{

	class Simulator
	{

		Ball _Ball;




	public : 
		void Initialize();

		void Run();

		// Run(Team homeTeam, Team visitingTeam, Field field, Conditions conditions, GameParameters parameters);
	
	};


}