#pragma once

#include <CommonDefines.h>

#include <string>
#include <vector>

struct SimpleProgramArgs
{
    std::string m_InputFile { };
    bool m_Debug { false };
};

std::string SimpleGetInputFileFromArgs(int argc, char** argv);
SimpleProgramArgs SimpleGetProgramArgs(int argc, char** argv);
std::vector<uint> DecomposeInDigits(uint value);

template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = 0>
T GetMCD(T a, T b)
{
	// Your friendly neighbourhood Euclide's algorithm
	T residual = 0;
	a = std::abs(a);
	b = std::abs(b);

	while (b != 0)
	{
		residual = a % b;
		a = b;
		b = residual;
	}

	return a;
}

struct Position
{
public:
	Position() : Position(0, 0)
	{ }

	Position(int x, int y)
		: m_X(x), m_Y(y)
	{ }

	int m_X, m_Y;

	Position IntNormalize() const;

	inline int GetTaxiLength() const { return std::abs(m_X) + std::abs(m_Y); }

	inline bool operator==(const Position& other) const { return m_X == other.m_X && m_Y == other.m_Y; }
	inline std::size_t hash() const { return m_X ^ m_Y; }
};

namespace std
{
	template<>
	struct hash<Position>
	{
		std::size_t operator()(const Position& pos) const { return pos.hash(); }
	};
}

inline Position operator-(const Position& p1, const Position& p2)
{
	return Position{ p1.m_X - p2.m_X, p1.m_Y - p2.m_Y };
}

inline Position operator+(const Position& p1, const Position& p2)
{
	return Position{ p1.m_X + p2.m_X, p1.m_Y + p2.m_Y };
}