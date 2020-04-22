#pragma once

#include <stdlib.h>
#include <cstdint>
#include "Types.h"

namespace FootballSimulation
{

	template<typename U, typename T>
	constexpr U ToNumber(T enumValue)
	{
		return static_cast<U>(enumValue);
	}

	template<typename T>
	constexpr std::uint8_t _uint8(T enumValue)
	{
		return ToNumber<uint8_t>(enumValue);
	}

	enum class BallPlayedDistance : std::uint8_t
	{
		Short,
		Medium,
		Long,
		EnumCount
	};

	enum class  FieldPosition : std::uint8_t
	{
		AwayEndLine,
		AwayPenaltyBox,
		AwayBottomThird,
		AwayTopThird,
		Center,
		HomeTopThird,
		HomeBottomThird,
		HomePenaltyBox,
		HomeEndLine,
		EnumCount
	};


	enum class DistributionDirection : std::uint8_t
	{
		Forward,
		Square,
		Backward,
		EnumCount
	};

	enum class Period : std::uint8_t
	{
		First,
		Second,
		EnumCount
	};

	enum class PeriodDivision : std::uint8_t
	{
		First15Min,		//	00:00 - 15:00 / 45:01 - 60:00
		Second15Min,	//	15:01 - 30:00 / 60:01 - 75:00
		Third15Min,		//	30:01 - 45:00 / 75:01 - 90:00
		EnumCount
	};

	enum class Side : std::uint8_t
	{
		Neither,
		Home,
		Visitor,
		EnumCount
	};

	enum class PlayerFocus : std::uint8_t
	{
		Defense,
		Midfield,
		Attack,
		EnumCount
	};

	enum class PlayerAction : std::uint8_t
	{
		Keep,
		Pass,
		Shoot,
		EnumCount
	};

	enum class Position : std::uint8_t
	{								//	DefensiveEndLine	DefensivePenaltyBox	DefensiveBottomThird	DefensiveTopThird	Center	OffensiveTopThird	OffensiveBottomThird	OffensivePenaltyBox	OffensiveEndLine
		Keeper,						//	100	0	0
		CenterBack,					//	90	10	0
		FullBack,					//	90	10	0
		WingBack, 					//	50	20	30
		CenterMidfield,				//	30	50	20
		DefensiveMidfield,			//	40	50	10
		AttackingMidfield, 			//	10	50	40
		WideMidfield,				//	10	60	30
		MainStriker,				//	5	15	80
		SecondStriker,				//	10	20	70
		Winger,						//	10	15	75
		EnumCount
	};

	enum class TeamPlayer : std::uint8_t
	{
		Keeper,
		Player2,
		Player3,
		Player4,
		Player5,
		Player6,
		Player7,
		Player8,
		Player9,
		Player10,
		Player11,
		EnumCount
	};


	//	Added for iteration over team index
	constexpr TeamPlayer TeamPlayerIndex[] 
	{
		TeamPlayer::Keeper,
		TeamPlayer::Player2,
		TeamPlayer::Player3,
		TeamPlayer::Player4,
		TeamPlayer::Player5,
		TeamPlayer::Player6,
		TeamPlayer::Player7,
		TeamPlayer::Player8,
		TeamPlayer::Player9,
		TeamPlayer::Player10,
		TeamPlayer::Player11
	};

	enum class SubstitutionResult : std::uint8_t
	{
		Success,
		PlayerNotOnField,
		SubstituteNotAvailable,
		NoSubstitutesAvailable
	};
}