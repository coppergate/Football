#pragma once
#include "Enums.h"
#include "Types.h"
#include "Exceptions.h"

namespace FootballSimulation
{

	class PlayerID
	{
		uint32_t _ID = 0;

	public:
		bool IsAvailable = true;

		uint32_t ID() const
		{
			return _ID;
		}

		void SetID(uint32_t id)
		{
			if (_ID == 0)
			{
				_ID = id;
			}
			else
			{
				throw InvalidPlayerIDException(id, "Cannot reset player ID.  Create a new player instead.");
			}
		}

		void MakeInvalid()
		{
			_ID = 0;
		}

		bool IsValidPlayer() const 
		{
			return _ID != 0;
		}
	};

	class Player : public PlayerID
	{

		TeamPlayer _TeamIndex = TeamPlayer::EnumCount;
		Position _Position = Position::EnumCount;
		PlayerFocus _Focus = PlayerFocus::EnumCount;

		//	Player abilities
		//	Offensive
		//	take a ball delivered from various distances
		EnumArray<BallPlayedDistance> _Receive;
		//	hold on to a ball once received
		double _Hold = 0.0;
		//	distribute the ball to players at various distances
		EnumArray<BallPlayedDistance> _Distribute;
		//	hit the goal from various distances
		EnumArray<BallPlayedDistance> _Shoot;

		//	Defensive
		//	take a ball away from a player who has received it
		double _Take = 0.0;
		//	restrict distribution channels
		double _CloseDown = 0.0;	
		//	intercept a ball from various distances (NB: maybe able to model keeper this way?)
		EnumArray<BallPlayedDistance> _Intercept;

		//	Effectiveness multiplier (injury/fatigue/etc)
		double _Effectiveness = 0.0;

		//	Player energy (ability/desire to put forth effort) 
		//	divided into first/second half and divisions within the half
		EnumArray2D<Period, PeriodDivision> _EnergyLevel;
		//	multiplier to apply to the energy level depending on game variables
		double _EnergyLevelModifier = 0.0;

		//	Original player field position probability based on position
		//	this defines the position probability when the player resets.
		EnumArray<FieldPosition> _BasePositionProbability;
		//	Current player field position probability based on base position along with any 
		//	Position "shifts"
		EnumArray<FieldPosition> _CurrentPositionProbability;

		//	Probability distributions for ball distribution
		//	Direction probability given field position
		EnumArray2D<FieldPosition, DistributionDirection> _BallPositionDistributionDirection;
		//	Distance probability given field position and distribution direction
		EnumArray3D<FieldPosition, DistributionDirection, BallPlayedDistance> _BallPositionDistributionDistance;
		//	Action probability given field position
		EnumArray2D<FieldPosition, PlayerAction> _ActionProbability;
		//	



	public:
		Player() :
			_Receive(BallPlayedDistance::EnumCount),
			_Distribute(BallPlayedDistance::EnumCount),
			_Shoot(BallPlayedDistance::EnumCount),
			_Intercept(BallPlayedDistance::EnumCount),
			_EnergyLevel(Period::EnumCount, PeriodDivision::EnumCount),
			_BasePositionProbability(FieldPosition::EnumCount),
			_CurrentPositionProbability(FieldPosition::EnumCount),
			_BallPositionDistributionDirection(FieldPosition::EnumCount, DistributionDirection::EnumCount),
			_BallPositionDistributionDistance(FieldPosition::EnumCount, DistributionDirection::EnumCount, BallPlayedDistance::EnumCount),
			_ActionProbability(FieldPosition::EnumCount, PlayerAction::EnumCount)
		{
			double test = _Receive[BallPlayedDistance::Medium];
		}

	};

	static bool operator==(const Player& p1, const Player& p2)
	{
		return p1.ID() == p2.ID();
	}

}
