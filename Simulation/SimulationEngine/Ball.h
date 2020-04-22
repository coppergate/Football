#pragma once


#include "Enums.h"

namespace FootballSimulation
{
	struct Ball
	{
		FieldPosition CurrentPostion = FieldPosition::Center;
		Side CurrentPossesorTeam = Side::Neither;
		Player& CurrentPossesorPlayer;
		uint16_t Touches = 0;
	};

}