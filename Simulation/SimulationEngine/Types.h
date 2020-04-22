#pragma once

#include <array>
#include <vector>

namespace FootballSimulation
{
	using std::array;
	using std::vector;

	template <typename T, size_t COL>
	using Array = array<T, COL>;

	template <typename T, size_t ROW, size_t COL>
	using Array2D = array < array<T, COL>, ROW >;

	template <typename T, size_t INST, size_t ROW, size_t COL>
	using Array3D = array< array < array<T, COL>, ROW >, INST >;

	//	T: type to be stored
	//	E: enum being used to index store
	//	I: base type of enum used to convert enum to index
	//	This class should be instantiated using an enum value 
	//	indicating the max number of elements in the store
	template <typename T, typename I, typename E>
	class EnumIndexedArray : public vector<T>
	{

	public:

		EnumIndexedArray() : vector<T>()
		{

		}

		EnumIndexedArray(E enumCount) : vector<T>(static_cast<I>(enumCount))
		{

		}

		T& operator[](E index)
		{
			return this->at(static_cast<I>(index));
		}

	};


	template <typename T, typename I, typename E1, typename E2>
	class EnumIndexedArray2D : public EnumIndexedArray<EnumIndexedArray<T, I, E2>, I, E1>
	{

	public:
		EnumIndexedArray2D() : EnumIndexedArray<EnumIndexedArray<T, I, E2>, I, E1>()
		{
		}

		EnumIndexedArray2D(E1 enumCount1, E2 enumCount2) : EnumIndexedArray<EnumIndexedArray<T, I, E2>, I, E1>(enumCount1)
		{
			std::for_each(this->begin(), this->end(), [enumCount2](auto& v)
						  {
							  v.resize(static_cast<I>(enumCount2));
						  });
		}

		EnumIndexedArray<T, I, E2>& operator[](E1 index)
		{
			return this->at(static_cast<I>(index));
		}


	};

	template <typename T, typename I, typename E1, typename E2, typename E3>
	class EnumIndexedArray3D : public EnumIndexedArray<EnumIndexedArray2D<T, I, E2, E3>, I, E1>
	{

	public:
		EnumIndexedArray3D(E1 enumCount1, E2 enumCount2, E3 enumCount3) : EnumIndexedArray<EnumIndexedArray2D<T, I, E2, E3>, I, E1>(enumCount1)
		{
			std::for_each(this->begin(), this->end(), [enumCount2, enumCount3](auto& v)
				{
					v.resize(static_cast<I>(enumCount2));
					std::for_each(v.begin(), v.end(), [&](auto& vi)
						{
							vi.resize(static_cast<I>(enumCount3));
						});
				});
		}

		EnumIndexedArray2D<T, I, E2, E3>& operator[](E1 index)
		{
			return this->at(static_cast<I>(index));
		}


	};


	template <typename E1>
	using EnumArray = EnumIndexedArray<double, uint8_t, E1>;

	template <typename E1, typename E2>
	using EnumArray2D = EnumIndexedArray2D <double, uint8_t, E1, E2>;

	template <typename E1, typename E2, typename E3>
	using EnumArray3D = EnumIndexedArray3D <double, uint8_t, E1, E2, E3>;


}