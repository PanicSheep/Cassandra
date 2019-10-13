#include "AlphaBetaFailSoftSearch.h"
#include "Core/Machine.h"
#include <algorithm>

using namespace Search;

Result AlphaBetaFailSoft::Eval(Position pos, Intensity intensity)
{
	node_counter = 0;
	Score score = Eval_triage(pos, intensity.window);
	return { score, Field::invalid, node_counter };
}

Score AlphaBetaFailSoft::Eval_triage(Position pos, Window w)
{
	auto moves = Moves(pos.Empties());
	const auto move1 = moves.front(); moves.pop_front();
	const auto move2 = moves.front(); moves.pop_front();
	const auto move3 = moves.front(); moves.pop_front();
	const auto move4 = moves.front(); moves.pop_front();
	switch (pos.EmptyCount())
	{
		case 0: return NegaMax::Eval_0(pos);
		case 1: return NegaMax::Eval_1(pos, move1);
		case 2: return Eval_2(pos, w, move1, move2);
		case 3: return Eval_3(pos, w, move1, move2, move3);
		case 4: return Eval_4(pos, w, move1, move2, move3, move4);
		default: return Eval_N(pos, w);
	}
}

Score AlphaBetaFailSoft::Eval_2(Position pos, Window w, const Field move1, const Field move2)
{
	node_counter++;
	Score bestscore = -infinity;

	if (const auto flips = Flips(pos, move1)) {
		bestscore = -NegaMax::Eval_1(Play(pos, move1, flips), move2);
		if (bestscore >= w.beta) return bestscore;
	}

	if (const auto flips = Flips(pos, move2))
		return std::max(bestscore, -NegaMax::Eval_1(Play(pos, move2, flips), move1));

	if (bestscore != -infinity)
		return bestscore;
	bestscore = infinity;

	const auto passed = PlayPass(pos);
	node_counter++;

	if (const auto flips = Flips(passed, move1)) {
		bestscore = NegaMax::Eval_1(Play(passed, move1, flips), move2);
		if (bestscore <= w.alpha) return bestscore;
	}

	if (const auto flips = Flips(passed, move2))
		return std::min(bestscore, NegaMax::Eval_1(Play(passed, move2, flips), move1));

	if (bestscore != infinity)
		return bestscore;
	
	node_counter--;
	return -EvalGameOver(passed);
}

Score AlphaBetaFailSoft::Eval_3(Position pos, Window w, const Field move1, const Field move2, const Field move3)
{
	node_counter++;
	Score bestscore = -infinity;

	if (const auto flips = Flips(pos, move1)) {
		bestscore = -Eval_2(Play(pos, move1, flips), -w, move2, move3);
		if (bestscore >= w.beta) return bestscore;
		if (bestscore > w.alpha) w.alpha = bestscore;
	}

	if (const auto flips = Flips(pos, move2)) {
		const auto score = -Eval_2(Play(pos, move2, flips), -w, move1, move3);
		if (score >= w.beta) return score;
		if (score > w.alpha) w.alpha = score;
		bestscore = std::max(bestscore, score);
	}

	if (const auto flips = Flips(pos, move3))
		return std::max(bestscore, -Eval_2(Play(pos, move3, flips), -w, move1, move2));

	if (bestscore != -infinity)
		return bestscore;
	bestscore = infinity;

	const auto passed = PlayPass(pos);
	node_counter++;

	if (const auto flips = Flips(passed, move1)) {
		bestscore = Eval_2(Play(passed, move1, flips), w, move2, move3);
		if (bestscore <= w.alpha) return bestscore;
		if (bestscore < w.beta) w.beta = bestscore;
	}

	if (const auto flips = Flips(passed, move2)) {
		const auto score = Eval_2(Play(passed, move2, flips), w, move1, move3);
		if (score <= w.alpha) return score;
		if (score < w.beta) w.beta = score;
		if (score < bestscore) bestscore = score;
	}

	if (const auto flips = Flips(passed, move3))
		return std::min(bestscore, Eval_2(Play(passed, move3, flips), w, move1, move2));

	if (bestscore != infinity)
		return bestscore;

	node_counter--;
	return -EvalGameOver(passed);
}

Score AlphaBetaFailSoft::Eval_4(Position pos, Window w, const Field move1, const Field move2, const Field move3, const Field move4)
{
	node_counter++;
	Score bestscore = -infinity;

	if (const auto flips = Flips(pos, move1)) {
		bestscore = -Eval_3(Play(pos, move1, flips), -w, move2, move3, move4);
		if (bestscore >= w.beta) return bestscore;
		if (bestscore > w.alpha) w.alpha = bestscore;
	}

	if (const auto flips = Flips(pos, move2)) {
		const auto score = -Eval_3(Play(pos, move2, flips), -w, move1, move3, move4);
		if (score >= w.beta) return score;
		if (score > w.alpha) w.alpha = score;
		if (score > bestscore) bestscore = score;
	}

	if (const auto flips = Flips(pos, move3)) {
		const auto score = -Eval_3(Play(pos, move3, flips), -w, move1, move2, move4);
		if (score >= w.beta) return score;
		if (score > w.alpha) w.alpha = score;
		if (score > bestscore) bestscore = score;
	}

	if (const auto flips = Flips(pos, move4))
		return std::max(bestscore, -Eval_3(Play(pos, move4, flips), -w, move1, move2, move3));

	if (bestscore != -infinity)
		return bestscore;
	bestscore = infinity;

	const auto passed = PlayPass(pos);
	node_counter++;

	if (const auto flips = Flips(passed, move1)) {
		bestscore = Eval_3(Play(passed, move1, flips), w, move2, move3, move4);
		if (bestscore <= w.alpha) return bestscore;
		if (bestscore < w.beta) w.beta = bestscore;
	}

	if (const auto flips = Flips(passed, move2)) {
		const auto score = Eval_3(Play(passed, move2, flips), w, move1, move3, move4);
		if (score <= w.alpha) return score;
		if (score < w.beta) w.beta = score;
		if (score < bestscore) bestscore = score;
	}

	if (const auto flips = Flips(passed, move3)) {
		const auto score = Eval_3(Play(passed, move3, flips), w, move1, move2, move4);
		if (score <= w.alpha) return score;
		if (score < w.beta) w.beta = score;
		if (score < bestscore) bestscore = score;
	}

	if (const auto flips = Flips(passed, move4))
		return std::min(bestscore, Eval_3(Play(passed, move4, flips), w, move1, move2, move3));

	if (bestscore != infinity)
		return bestscore;

	node_counter--;
	return -EvalGameOver(passed);
}

Score AlphaBetaFailSoft::Eval_N(Position pos, Window w)
{
	if (pos.EmptyCount() <= 4)
		return Eval_triage(pos, w);

	node_counter++;

	Moves moves = PossibleMoves(pos);
	if (moves.empty()) {
		const auto PosPass = PlayPass(pos);
		if (PossibleMoves(PosPass).empty())
			return EvalGameOver(pos);
		return -Eval_N(PosPass, -w);
	}

	Score bestscore = -infinity;
	for (auto move : moves)
	{
		const auto score = -Eval_N(Play(pos, move), -w);
		if (score >= w.beta) return score;
		if (score > w.alpha) w.alpha = score;
		if (score > bestscore) bestscore = score;
	}

	return bestscore;
}
