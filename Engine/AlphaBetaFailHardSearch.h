#pragma once
#include "Core/Moves.h"
#include "Core/Position.h"
#include "Core/Search.h"
#include "NegaMaxSearch.h"

namespace Search
{
	class AlphaBetaFailHard : public NegaMax
	{
	public:
		Result Eval(Position, Intensity) override;
	private:
		Score Eval_triage(Position, Window);
		Score Eval_0(Position, Window);
		Score Eval_1(Position, Window, Field);
		Score Eval_2(Position, Window, Field, Field);
		Score Eval_3(Position, Window, Field, Field, Field);
		Score Eval_4(Position, Window, Field, Field, Field, Field);
		Score Eval_N(Position, Window);

	};
}