#pragma once
#include "Core/Core.h"
#include "Search.h"
#include <optional>

class Puzzle
{
	Position position;
	Search::Intensity intensity;
	std::optional<Search::Result> result;
public:
	Puzzle(Position, Search::Intensity, Search::Result);
	Puzzle(Position, Search::Intensity);
	static Puzzle Exact(Position);

	auto Position() const { return position; }
	auto Intensity() const { return intensity; }
	auto Result() const { return result; }

	bool IsSolved() const;

	void Reset();
	void Solve(Search::Algorithm&, bool force = true);
};