#pragma once

#include <exception>
#include <cstdint>


namespace FootballSimulation
{
	using std::exception;

	class InvalidPlayerIDException : public exception
	{
		uint32_t _PlayerID;
		std::string _Message;

	public:
		InvalidPlayerIDException(uint32_t playerID)
		{
			_PlayerID = playerID;
		}

		InvalidPlayerIDException(uint32_t playerID, const std::string& message)
		{
			_PlayerID = playerID;
			_Message = message;
		}

	};

}