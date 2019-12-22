#include "Puzzle.h"
#include <cassert>

Puzzle::Puzzle(::Position position, Search::Intensity intensity, Search::Result result)
	: position(position)
	, intensity(intensity)
	, result(result)
{
	assert(intensity.depth <= position.EmptyCount());
}

Puzzle::Puzzle(::Position position, Search::Intensity intensity)
	: position(position)
	, intensity(intensity)
	, result({})
{
	assert(intensity.depth <= position.EmptyCount());
}

Puzzle Puzzle::Exact(::Position pos)
{
	return Puzzle(pos, Search::Intensity::Exact(pos));
}

void Puzzle::Reset()
{
	result = {};
}

void Puzzle::Solve(Search::Algorithm& algorithm)
{
	result = algorithm.Eval(position, intensity);
}
