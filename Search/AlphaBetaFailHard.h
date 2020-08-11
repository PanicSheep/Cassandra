#pragma once
#include "NegaMax.h"

namespace Search
{
	class AlphaBetaFailHard : public NegaMax
	{
	public:
		using Algorithm::Eval;
		Result Eval(Position, Intensity) override;
	private:
		Score Eval_triage(const Position&, OpenInterval);
		Score Eval_0(const Position&, OpenInterval);
		Score Eval_1(const Position&, OpenInterval, Field);
		Score Eval_2(const Position&, OpenInterval, Field, Field);
		Score Eval_3(const Position&, OpenInterval, Field, Field, Field);
		Score Eval_N(const Position&, OpenInterval);
	};
}