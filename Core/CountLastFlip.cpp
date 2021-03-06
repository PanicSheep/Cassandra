#include "Position.h"
#include "Bit.h"
#include <array>

class CLF
{
	std::array<std::array<BitBoard, 4>, 64> mask;
	std::array<std::array<uint8, 256>, 8> flip_count;
public:
	constexpr CLF() noexcept
	{
		for (uint8 i = 0; i < 64; i++)
		{
			Field move = static_cast<Field>(i);

			const BitBoard relevant = BitBoard::HorizontalLine(move)
				| BitBoard::VerticalLine(move)
				| BitBoard::DiagonalLine(move)
				| BitBoard::CodiagonalLine(move);
			
			BitBoard r = ~relevant;
			BitBoard codiagonal = BitBoard::CodiagonalLine(move);
			while (PExt(BitBoard(move), codiagonal) != 1ULL << (i / 8))
			{
				codiagonal |= r.FirstSet();
				r.ClearFirstSet();
			}

			r = ~relevant;
			BitBoard diagonal = BitBoard::DiagonalLine(move);
			while (PExt(BitBoard(move), diagonal) != 1ULL << (i / 8))
			{
				diagonal |= r.FirstSet();
				r.ClearFirstSet();
			}

			mask[i][0] = relevant;
			mask[i][1] = codiagonal;
			mask[i][2] = diagonal;
			mask[i][3] = BitBoard::VerticalLine(move);
		}

		for (Field move : {Field::A1, Field::B1, Field::C1, Field::D1, Field::E1, Field::F1, Field::G1, Field::H1})
			for (uint64 r = 0; r < 256; r++)
			{
				Position pos(r & ~BitBoard(move), ~r & ~BitBoard(move));
				flip_count[static_cast<uint8>(move)][r] = popcount(Flips(pos, move));
			}
	}

	int Count(const Position& pos, Field f) const noexcept
	{
		const auto move = static_cast<uint8>(f);
		const auto x = move % 8;
		const auto y = move / 8;

		const auto P = pos.Player() & mask[move][0]; // mask out unrelated bits to make dummy 0 bits for outside

		return flip_count[x][BExtr(P, move & 0xF8, 8)]
			+ flip_count[y][PExt(P, mask[move][1])]
			+ flip_count[y][PExt(P, mask[move][2])]
			+ flip_count[y][PExt(P, mask[move][3])];
	}
};

static CLF clf;

int CountLastFlip(const Position& pos, Field f) noexcept
{
	return clf.Count(pos, f);
}
