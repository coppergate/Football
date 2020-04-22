#pragma once

#include "Enums.h"
#include "Types.h"

namespace FootballSimulation
{
	class Strategy
	{
		// Player base position probability
		
		
		// Player base disposition
		//	This will modify the player focus as a function of field position
		//	this will be interpreted as the likelyhood the player will perform
		//	the focus action
		//	e.g. for a "high press" the probability that an 'attacking' player
		//		might engage in a defensive action would be increased.
		//		- or - for a "push attack" the probability that a 'defending' 
		//		player might ingage in an attacking action would be increased.
		//	See ->  Player::_ActionProbability
		Array3D<double, _uint8(TeamPlayer::EnumCount), _uint8(FieldPosition::EnumCount), _uint8(PlayerAction::EnumCount)>  _PlayerActionProbability;

	};

}