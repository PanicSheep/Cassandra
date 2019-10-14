#include "pch.h"

const PosScore Zero_empty_0 = {
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"_pos, 0 };

const PosScore Zero_empty_1 = {
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"X X X X X X X X"_pos, +16};

const PosScore Zero_empty_2 = {
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"
	"X X X X X X X X"
	"O O O O O O O O"
	"O O O O O O O O"
	"O O O O O O O O"_pos, -16};

const PosScore One_empty_0 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X  "_pos, +64};

const PosScore One_empty_1 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X O O"
	"X X X X X X O  "_pos, +64};

const PosScore One_empty_2 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"O X X X X X X  "_pos, +48};

const PosScore One_empty_3 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X O"
	"O X X X X X X  "_pos, +62};

const PosScore Two_empty_0 = {
	"X X X X X X X  "
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X  "_pos, +64};

const PosScore Two_empty_1 = {
	"X X X X X X O  "
	"X X X X X X O O"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X O O"
	"X X X X X X O  "_pos, +64};

const PosScore Two_empty_2 = {
	"X X X X X X X  "
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"O X X X X X X  "_pos, +22};

const PosScore Two_empty_3 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X O X X"
	"X X X X X X X O"
	"X X X X X X O  "
	"O X X X X X X  "_pos, +54};

const PosScore Three_empty_0 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X      "_pos, +64 };

const PosScore Three_empty_1 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X O X"
	"X X X X X      "_pos, +64 };

const PosScore Three_empty_2 = {
	"X X X X X O O O"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X      "_pos, +16 };

const PosScore Three_empty_3 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X O"
	"X X X X X O X X"
	"X X X X X X X  "
	"X X X X X X O  "
	"O X X X X X X  "_pos, +58};

const PosScore Four_empty_0 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X        "_pos, +64};

const PosScore Four_empty_1 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X O O O O O"
	"X X X O        "_pos, +64 };

const PosScore Four_empty_2 = {
	"X X X X O O O O"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X        "_pos, 0};

const PosScore Four_empty_3 = {
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X X X X X X"
	"X X X O O X X X"
	"X X O X X O X X"
	"X X         X X"_pos, +56};

void TestAlgorithm(Search::Algorithm& alg, PosScore pos_score)
{
	const Position pos = pos_score.pos;
	const Score correct = pos_score.score;

	const auto result = alg.Eval(pos, Search::Intensity::Exact(pos));

	ASSERT_EQ(result.score, correct);
}

class NegaMax : public ::testing::Test
{
public:
	Search::NegaMax alg;
};

TEST_F(NegaMax, Zero_empty_0) { TestAlgorithm(alg, Zero_empty_0); }
TEST_F(NegaMax, Zero_empty_1) { TestAlgorithm(alg, Zero_empty_1); }
TEST_F(NegaMax, Zero_empty_2) { TestAlgorithm(alg, Zero_empty_2); }
TEST_F(NegaMax, One_empty_0) { TestAlgorithm(alg, One_empty_0); }
TEST_F(NegaMax, One_empty_1) { TestAlgorithm(alg, One_empty_1); }
TEST_F(NegaMax, One_empty_2) { TestAlgorithm(alg, One_empty_2); }
TEST_F(NegaMax, One_empty_3) { TestAlgorithm(alg, One_empty_3); }
TEST_F(NegaMax, Two_empty_0) { TestAlgorithm(alg, Two_empty_0); }
TEST_F(NegaMax, Two_empty_1) { TestAlgorithm(alg, Two_empty_1); }
TEST_F(NegaMax, Two_empty_2) { TestAlgorithm(alg, Two_empty_2); }
TEST_F(NegaMax, Two_empty_3) { TestAlgorithm(alg, Two_empty_3); }
TEST_F(NegaMax, Three_empty_0) { TestAlgorithm(alg, Three_empty_0); }
TEST_F(NegaMax, Three_empty_1) { TestAlgorithm(alg, Three_empty_1); }
TEST_F(NegaMax, Three_empty_2) { TestAlgorithm(alg, Three_empty_2); }
TEST_F(NegaMax, Three_empty_3) { TestAlgorithm(alg, Three_empty_3); }
TEST_F(NegaMax, Four_empty_0) { TestAlgorithm(alg, Four_empty_0); }
TEST_F(NegaMax, Four_empty_1) { TestAlgorithm(alg, Four_empty_1); }
TEST_F(NegaMax, Four_empty_2) { TestAlgorithm(alg, Four_empty_2); }
TEST_F(NegaMax, Four_empty_3) { TestAlgorithm(alg, Four_empty_3); }

class AlphaBetaFailHard : public ::testing::Test
{
public:
	Search::AlphaBetaFailHard alg;
};

TEST_F(AlphaBetaFailHard, Zero_empty_0) { TestAlgorithm(alg, Zero_empty_0); }
TEST_F(AlphaBetaFailHard, Zero_empty_1) { TestAlgorithm(alg, Zero_empty_1); }
TEST_F(AlphaBetaFailHard, Zero_empty_2) { TestAlgorithm(alg, Zero_empty_2); }
TEST_F(AlphaBetaFailHard, One_empty_0) { TestAlgorithm(alg, One_empty_0); }
TEST_F(AlphaBetaFailHard, One_empty_1) { TestAlgorithm(alg, One_empty_1); }
TEST_F(AlphaBetaFailHard, One_empty_2) { TestAlgorithm(alg, One_empty_2); }
TEST_F(AlphaBetaFailHard, One_empty_3) { TestAlgorithm(alg, One_empty_3); }
TEST_F(AlphaBetaFailHard, Two_empty_0) { TestAlgorithm(alg, Two_empty_0); }
TEST_F(AlphaBetaFailHard, Two_empty_1) { TestAlgorithm(alg, Two_empty_1); }
TEST_F(AlphaBetaFailHard, Two_empty_2) { TestAlgorithm(alg, Two_empty_2); }
TEST_F(AlphaBetaFailHard, Two_empty_3) { TestAlgorithm(alg, Two_empty_3); }
TEST_F(AlphaBetaFailHard, Three_empty_0) { TestAlgorithm(alg, Three_empty_0); }
TEST_F(AlphaBetaFailHard, Three_empty_1) { TestAlgorithm(alg, Three_empty_1); }
TEST_F(AlphaBetaFailHard, Three_empty_2) { TestAlgorithm(alg, Three_empty_2); }
TEST_F(AlphaBetaFailHard, Three_empty_3) { TestAlgorithm(alg, Three_empty_3); }
TEST_F(AlphaBetaFailHard, Four_empty_0) { TestAlgorithm(alg, Four_empty_0); }
TEST_F(AlphaBetaFailHard, Four_empty_1) { TestAlgorithm(alg, Four_empty_1); }
TEST_F(AlphaBetaFailHard, Four_empty_2) { TestAlgorithm(alg, Four_empty_2); }
TEST_F(AlphaBetaFailHard, Four_empty_3) { TestAlgorithm(alg, Four_empty_3); }
TEST_F(AlphaBetaFailHard, FForum_1) { TestAlgorithm(alg, FForum[1]); }
TEST_F(AlphaBetaFailHard, FForum_2) { TestAlgorithm(alg, FForum[2]); }
TEST_F(AlphaBetaFailHard, FForum_3) { TestAlgorithm(alg, FForum[3]); }
TEST_F(AlphaBetaFailHard, FForum_4) { TestAlgorithm(alg, FForum[4]); }
TEST_F(AlphaBetaFailHard, FForum_5) { TestAlgorithm(alg, FForum[5]); }
TEST_F(AlphaBetaFailHard, FForum_6) { TestAlgorithm(alg, FForum[6]); }
TEST_F(AlphaBetaFailHard, FForum_7) { TestAlgorithm(alg, FForum[7]); }
TEST_F(AlphaBetaFailHard, FForum_8) { TestAlgorithm(alg, FForum[8]); }
TEST_F(AlphaBetaFailHard, FForum_9) { TestAlgorithm(alg, FForum[9]); }
TEST_F(AlphaBetaFailHard, FForum_10) { TestAlgorithm(alg, FForum[10]); }

class AlphaBetaFailSoft : public ::testing::Test
{
public:
	Search::AlphaBetaFailSoft alg;
};

TEST_F(AlphaBetaFailSoft, Zero_empty_0) { TestAlgorithm(alg, Zero_empty_0); }
TEST_F(AlphaBetaFailSoft, Zero_empty_1) { TestAlgorithm(alg, Zero_empty_1); }
TEST_F(AlphaBetaFailSoft, Zero_empty_2) { TestAlgorithm(alg, Zero_empty_2); }
TEST_F(AlphaBetaFailSoft, One_empty_0) { TestAlgorithm(alg, One_empty_0); }
TEST_F(AlphaBetaFailSoft, One_empty_1) { TestAlgorithm(alg, One_empty_1); }
TEST_F(AlphaBetaFailSoft, One_empty_2) { TestAlgorithm(alg, One_empty_2); }
TEST_F(AlphaBetaFailSoft, One_empty_3) { TestAlgorithm(alg, One_empty_3); }
TEST_F(AlphaBetaFailSoft, Two_empty_0) { TestAlgorithm(alg, Two_empty_0); }
TEST_F(AlphaBetaFailSoft, Two_empty_1) { TestAlgorithm(alg, Two_empty_1); }
TEST_F(AlphaBetaFailSoft, Two_empty_2) { TestAlgorithm(alg, Two_empty_2); }
TEST_F(AlphaBetaFailSoft, Two_empty_3) { TestAlgorithm(alg, Two_empty_3); }
TEST_F(AlphaBetaFailSoft, Three_empty_0) { TestAlgorithm(alg, Three_empty_0); }
TEST_F(AlphaBetaFailSoft, Three_empty_1) { TestAlgorithm(alg, Three_empty_1); }
TEST_F(AlphaBetaFailSoft, Three_empty_2) { TestAlgorithm(alg, Three_empty_2); }
TEST_F(AlphaBetaFailSoft, Three_empty_3) { TestAlgorithm(alg, Three_empty_3); }
TEST_F(AlphaBetaFailSoft, Four_empty_0) { TestAlgorithm(alg, Four_empty_0); }
TEST_F(AlphaBetaFailSoft, Four_empty_1) { TestAlgorithm(alg, Four_empty_1); }
TEST_F(AlphaBetaFailSoft, Four_empty_2) { TestAlgorithm(alg, Four_empty_2); }
TEST_F(AlphaBetaFailSoft, Four_empty_3) { TestAlgorithm(alg, Four_empty_3); }
TEST_F(AlphaBetaFailSoft, FForum_1) { TestAlgorithm(alg, FForum[1]); }
TEST_F(AlphaBetaFailSoft, FForum_2) { TestAlgorithm(alg, FForum[2]); }
TEST_F(AlphaBetaFailSoft, FForum_3) { TestAlgorithm(alg, FForum[3]); }
TEST_F(AlphaBetaFailSoft, FForum_4) { TestAlgorithm(alg, FForum[4]); }
TEST_F(AlphaBetaFailSoft, FForum_5) { TestAlgorithm(alg, FForum[5]); }
TEST_F(AlphaBetaFailSoft, FForum_6) { TestAlgorithm(alg, FForum[6]); }
TEST_F(AlphaBetaFailSoft, FForum_7) { TestAlgorithm(alg, FForum[7]); }
TEST_F(AlphaBetaFailSoft, FForum_8) { TestAlgorithm(alg, FForum[8]); }
TEST_F(AlphaBetaFailSoft, FForum_9) { TestAlgorithm(alg, FForum[9]); }
TEST_F(AlphaBetaFailSoft, FForum_10) { TestAlgorithm(alg, FForum[10]); }