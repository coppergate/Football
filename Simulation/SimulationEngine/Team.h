#pragma once

#include <memory>
#include <vector>
#include <array>
#include <algorithm>

#include "Manager.h"
#include "Player.h"
#include "Exceptions.h"

using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::array;


namespace FootballSimulation
{
	class Team
	{
		unique_ptr<Manager> _Manager;
		Array<PlayerID*, _uint8(TeamPlayer::EnumCount)> _Players;
		//	This list will include both available substitutes 
		//	and players that have been substituted
		vector<unique_ptr<PlayerID>> _Bench;
		uint8_t _SubstitutionsAvailable;

	public:

		//	Clear the current bench player list and 
		//	add a new set of players to the bench
		void CreateBench(vector<Player*> players)
		{
			_Bench.clear();
			for (auto player : players)
			{
				PutOnBench(player);
			}
		}

		void CreateTeamFromBench(Array<uint32_t, _uint8(TeamPlayer::EnumCount)> playersByTeamIndex)
		{
			for (TeamPlayer playerIndex : TeamPlayerIndex)
			{
				PlayerID* player = GetBenchPlayer(playersByTeamIndex[_uint8(playerIndex)]);
				if (nullptr != player)
				{
					_Players[_uint8(playerIndex)] = player;
				}
				else
				{
					ClearTeamPlayers();
					throw new InvalidPlayerIDException(playersByTeamIndex[_uint8(playerIndex)]);
				}
			}
		}

		//	make one of the players on the bench active in place of 
		//	a player currently playing.
		SubstitutionResult SubstitutePlayer(uint32_t playerID, uint32_t substituteID)
		{
			if (_SubstitutionsAvailable <= 0)
			{
				return SubstitutionResult::NoSubstitutesAvailable;
			}

			TeamPlayer playerTeamIndex = TeamIndexFromPlayerID(playerID);
			if (playerTeamIndex != TeamPlayer::EnumCount)
			{
				PlayerID* sub = GetBenchPlayer(substituteID);
				if (nullptr != sub && sub->IsAvailable)
				{
					AddTeamPlayer(playerTeamIndex, sub);
					--_SubstitutionsAvailable;
					return SubstitutionResult::Success;
				}
				else
				{
					return SubstitutionResult::SubstituteNotAvailable;
				}
			}
			return SubstitutionResult::PlayerNotOnField;
		}

		//	Consumers should check the player's IsAvailable flag to ensure
		//	that the team player has not been removed for a red card
		//	or temporarily not on the field due to injury 
		//	or permenently removed due to injury and could not be substituted
		Player& GetPlayer(TeamPlayer playerNumber)
		{
			return static_cast<Player&>(*_Players[_uint8(playerNumber)]);
		}

	private:

		void SetManager(Manager* manager)
		{
			_Manager.reset(manager);
		}

		void AddBenchPlayerToTeam(TeamPlayer playerNumber, uint32_t playerID)
		{
			auto player = GetBenchPlayer(playerID);
			AddTeamPlayer(playerNumber, player);
		}

		void AddTeamPlayer(TeamPlayer playerNumber, PlayerID* player)
		{
			if (nullptr != player)
			{
				player->IsAvailable = false;
				_Players[_uint8(playerNumber)] = player;
			}
		}

		void PutOnBench(Player* player)
		{
			bool onBench = false;

			for (auto itor = _Bench.begin(); itor != _Bench.end(); ++itor)
			{
				if (itor->get()->ID() == player->ID())
				{
					onBench = true;
					break;
				}
			}
			if (!onBench)
			{
				player->IsAvailable = true;
				_Bench.push_back(unique_ptr<Player>(player));
			}
		}

		PlayerID* GetBenchPlayer(uint32_t playerID)
		{
			for (auto itor = _Bench.begin(); itor != _Bench.end(); ++itor)
			{
				PlayerID* sub = itor->get();
				if (sub->ID() == playerID)
				{
					return sub;
				}
			}
			return nullptr;
		}

		TeamPlayer TeamIndexFromPlayerID(uint32_t playerID)
		{
			for (TeamPlayer playerIndex : TeamPlayerIndex)
			{
				PlayerID* sub = _Players[_uint8(playerIndex)];
				if (sub->ID() == playerID && sub->IsAvailable)
				{
					return playerIndex;
				}
			}
			return TeamPlayer::EnumCount;
		}

		void ClearTeamPlayers()
		{
			for (TeamPlayer playerIndex : TeamPlayerIndex)
			{
				PlayerID* sub = _Players[_uint8(playerIndex)];
				sub->MakeInvalid();
			}

		}

	};

}
