#include "Core/Core.h"
#include "Search/Search.h"
#include "IO/IO.h"
#include "Pattern/DenseIndexer.h"
#include "Pattern/Evaluator.h"
#include "Math/Matrix.h"
#include "Math/MatrixCSR.h"
#include "Math/Vector.h"
#include "Math/Solver.h"
#include "Math/Statistics.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <omp.h>
#include <string>
#include <chrono>
#include <random>
#include <map>

constexpr BitBoard L02X = 0x00000000000042FFULL;
constexpr BitBoard L0 = 0x00000000000000FFULL;
constexpr BitBoard L1 = 0x000000000000FF00ULL;
constexpr BitBoard L2 = 0x0000000000FF0000ULL;
constexpr BitBoard L3 = 0x00000000FF000000ULL;
constexpr BitBoard D2 = 0x0000000000000102ULL;
constexpr BitBoard D3 = 0x0000000000010204ULL;
constexpr BitBoard D4 = 0x0000000001020408ULL;
constexpr BitBoard D5 = 0x0000000102040810ULL;
constexpr BitBoard D6 = 0x0000010204081020ULL;
constexpr BitBoard D7 = 0x0001020408102040ULL;
constexpr BitBoard D8 = 0x0102040810204080ULL;
constexpr BitBoard C8 = 0x8040201008040201ULL;
constexpr BitBoard B4 = 0x0000000000000F0FULL;
constexpr BitBoard B5 = 0x0000000000001F1FULL;
constexpr BitBoard B6 = 0x0000000000003F3FULL;
constexpr BitBoard Q0 = 0x0000000000070707ULL;
constexpr BitBoard Q1 = 0x0000000000070707ULL << 9;
constexpr BitBoard Q2 = 0x0000000000070707ULL << 18;
constexpr BitBoard Ep = 0x0000000000003CBDULL;
constexpr BitBoard Epp = 0x0000000000003CFFULL;
constexpr BitBoard C3 = 0x0000000000010307ULL;
constexpr BitBoard C4 = 0x000000000103070FULL;
constexpr BitBoard C4p = 0x000000000107070FULL;
constexpr BitBoard C3p1 = 0x000000000101030FULL;
constexpr BitBoard C3p2 = 0x000000010101031FULL;
constexpr BitBoard C3p3 = 0x000001010101033FULL;
constexpr BitBoard C4p1 = 0x000000010103071FULL;
constexpr BitBoard Comet = 0x8040201008040303ULL;
constexpr BitBoard Cometp = 0xC0C0201008040303ULL;
constexpr BitBoard C3pp = 0x81010000000103C7ULL;
constexpr BitBoard C3ppp = 0x81410000000103C7ULL;

constexpr BitBoard C4pp = C4 | C3pp;
constexpr BitBoard AA = 0x000000010105031FULL;

auto CreateMatrix(const DenseIndexer& indexer, const std::vector<Position>& pos)
{
    const auto row_size = indexer.variations;
    const auto cols = indexer.reduced_size;
    const auto rows = pos.size();
    MatrixCSR<uint32_t> mat(row_size, cols, rows);

    const int64_t size = pos.size();
    #pragma omp parallel for schedule(dynamic, 64)
    for (int64_t i = 0; i < size; i++)
        for (int j = 0; j < indexer.variations; j++)
            mat.begin(i)[j] = indexer.DenseIndex(pos[i], j);
    return mat;
}

Vector FittedWeights(const std::vector<BitBoard>& patterns, const std::vector<Position>& pos, const Vector& score)
{
    auto indexer = CreateDenseIndexer(patterns);
    auto matrix = CreateMatrix(*indexer, pos);
    Vector weights(indexer->reduced_size, 0);
    DiagonalPreconditioner P(matrix.JacobiPreconditionerSquare(1000));
    PCG solver(transposed(matrix) * matrix, P, weights, transposed(matrix) * score);
    solver.Iterate(10);
    return solver.GetX();
}

Vector EvalWeights(const Vector& weights, const std::vector<BitBoard>& patterns, const std::vector<Position>& pos, const Vector& score)
{
    auto indexer = CreateDenseIndexer(patterns);
    auto matrix = CreateMatrix(*indexer, pos);
    return score - matrix * weights;
}

//auto FittedEvaluator(const std::vector<BitBoard>& patterns, const std::vector<Position>& pos, const Vector& score)
//{
//    Vector weights = FittedWeights(patterns, pos, score);
//    return Pattern::CreateEvaluator(patterns, Pattern::Weights{weights.begin(), weights.end()});
//}


auto Split(const std::vector<PosScore>& pos_score, int test_size, 
           std::vector<Position>& test_pos, Vector& test_score,
           std::vector<Position>& train_pos, Vector& train_score)
{
    for (int i = 0; i < test_size; i++)
    {
        test_pos.push_back(pos_score[i].pos);
        test_score.push_back(pos_score[i].score);
    }
    for (int i = test_size; i < pos_score.size(); i++)
    {
        train_pos.push_back(pos_score[i].pos);
        train_score.push_back(pos_score[i].score);
    }
}

struct dDE
{
    int d, D, E;
    auto operator<=>(const dDE&) const noexcept = default;

    std::string to_string() const { return "(" + std::to_string(d) + "," + std::to_string(D) + "," + std::to_string(E) + ")"; }
};

std::string to_string(const dDE& o)
{
    return o.to_string();
}

std::ostream& operator<<(std::ostream& os, const dDE& o)
{
    return os << to_string(o);
}

float MagicFormula(const dDE& arg, const std::vector<float>& param)
{
    return (std::expf(param[0] * arg.d) + param[1]) * std::powf(arg.D - arg.d, param[2]) * (param[3] * arg.E + param[4]);
    float s = param[0] * arg.d + param[1] * arg.D + param[2] * arg.E;
    return param[3] * s * s + param[4] * s + param[5];
}

void MagicFormulaFit()
{
    const int max_empty_count = 24;
    const int size = 500;

    std::mt19937_64 rnd_engine;
    std::uniform_real_distribution<float> dst{-1, 1};

    std::map<dDE, float> SD;

    std::vector<int> score = Load<int>(R"(G:\Reversi\weights\dDE.w)");
    for (int E = 1; E <= max_empty_count; E++)
    {
        for (int D = 0; D <= E; D++)
        {
            for (int d = 0; d < D; d++)
            {
                std::vector<int> diff;
                for (int i = 0; i < size; i++)
                {
                    int j = (max_empty_count + 1) * ((E - 1) * size + i);
                    assert(score[j + d] != undefined_score);
                    assert(score[j + D] != undefined_score);
                    diff.push_back(score[j + d] - score[j + D]);
                }
                SD[{d,D,E}] = StandardDeviation(diff);
            }
        }
    }
    for (auto& sd : SD)
        std::cout << sd.first << ": " << sd.second << "\n";

    float best_value = 1'000'000'000;
    std::vector<float> best_param{-0.25, 1.5, 0.25, 1, 1, 1};

    float mean = 0;
    for (const auto& sd : SD)
        mean += sd.second;
    mean /= SD.size();

    float SS_tot = 0;
    for (const auto& sd : SD)
    {
        float diff = sd.second - mean;
        SS_tot += diff * diff;
    }

    float factor = 0.1;
    for (int i = 0; i < 1'000'000'000; i++)
    {
        std::vector<float> param;
        for (int i = 0; i < best_param.size(); i++)
            param.push_back(best_param[i] + dst(rnd_engine) * factor);

        float SS_res = 0;
        for (const auto& sd : SD)
        {
            float mf = MagicFormula(sd.first, param);
            float diff = mf - sd.second;
            SS_res += diff * diff;
        }
        float R_sq = 1.0f - SS_res / SS_tot;
        if (SS_res < best_value)
        {
            best_value = SS_res;
            best_param = param;
            std::cout << R_sq << ": ";
            for (auto p : best_param)
                std::cout << p << ","; 
            std::cout << std::endl;
        }
    }
}

void TestSD(const std::vector<Position>& pos)
{
    PatternEval pattern_eval = DefaultPatternEval();
    HashTablePVS tt{ 10'000'000 };
    std::vector<int> diff;
    for (int i = 0; i < pos.size(); i++)
        diff.push_back(PVS{ tt, pattern_eval }.Score(pos[i]) - PVS{ tt, pattern_eval }.Score(pos[i], 0));
    std::cout << StandardDeviation(diff) << std::endl;
}

int main()
{
    MagicFormulaFit();
    return 0;
    // 
    // Tested on e22 - e24
    //std::vector<BitBoard> patterns{Q0, C3p2, L02X, Ep, L1, L2, L3, D8, D7, D6, D5, D4}; // 12 Pattern => edax 3.85
    //std::vector<BitBoard> patterns{Q0, B5, L02X, L1, L2, L3, D8, D7, D6, D5, D4}; // 11 Pattern => Logistello 7.55 from https://skatgame.net/mburo/ps/improve.pdf
    //std::vector<BitBoard> patterns{L0, L1, L2, L3, D5, D6, D7, Comet, B5, C4, Q1, Q2}; // 12 Pattern => 3.92
    //std::vector<BitBoard> patterns{L0, L1, L2, L3, D5, D6, D7, Comet, B5, Q0, Q1, Q2}; // 12 Pattern => 3.93
    //std::vector<BitBoard> patterns{L02X, L1, L2, L3, D5, D6, D7, Comet, B5, C3p2, Q0}; // 11 Pattern => 3.73
    //std::vector<BitBoard> patterns{L0, L1, L2, L3, D5, D6, D7, Comet, B5, C4}; // 10 Pattern => 3.96
    std::vector<BitBoard> patterns{B5, C4, L02X, // 7 Pattern => 3.73, 4 Pattern => 3.88
        "# - - - - - - #"
        "# # - - - - # #"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- # - - - - # -"
        "- - - - - - - -"_BitBoard
        ,
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- # # - - # # -"
        "# # - - - - # #"_BitBoard
        ,
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - # # # # - -"
        "- - - # # - - -"
        "- - - # # - - -"_BitBoard
        ,
        "# # - - - - - -"
        "# # # - - - - -"
        "- # # # - - - -"
        "- - # # - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"
        "- - - - - - - -"_BitBoard
    };
    Save(R"(G:\Reversi\weights\pattern.w)", patterns);

    const int test_size = 50'000;

    auto indexer = CreateDenseIndexer(patterns);
    std::cout << "Weights to fit: " << indexer->reduced_size << std::endl;

    for (int block = 0; block < 8; block++)
    {
        std::vector<Position> test_pos, train_pos;
        Vector test_score, train_score;
        for (int e = block * 3 + 1; e < block * 3 + 4; e++)
        {
            if (e >= 0 && e < 25)
            {
                auto data = Load<PosScore>(R"(G:\Reversi\rnd\e)" + std::to_string(e) + ".psc");
                Split(data, test_size, test_pos, test_score, train_pos, train_score);
            }
        }
        for (auto& ele : test_score)
            ele /= 2;
        for (auto& ele : train_score)
            ele /= 2;

        const auto start = std::chrono::high_resolution_clock::now();
        auto matrix = CreateMatrix(*indexer, train_pos);
        Vector weights(indexer->reduced_size, 0);
        DiagonalPreconditioner P(matrix.JacobiPreconditionerSquare(1000));
        PCG solver(transposed(matrix) * matrix, P, weights, transposed(matrix) * train_score);
        solver.Iterate(10);
        weights = FittedWeights(patterns, train_pos, train_score);
        const auto stop = std::chrono::high_resolution_clock::now();

        Save(R"(G:\Reversi\weights\block)" + std::to_string(block) + ".w", weights);

        auto test_matrix = CreateMatrix(*indexer, test_pos);
        auto train_error = matrix * weights - train_score;
        auto test_error = test_matrix * weights - test_score;

        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start)
            << "\tTrainAvgAbsError: " << Avg(train_error, [](double x){ return std::abs(x); })
    	    << "\t TestAvgAbsError: " << Avg(test_error, [](double x){ return std::abs(x); })
            << "\tTrainSD: " << StandardDeviation(train_error)
            << "\t TestSD: " << StandardDeviation(test_error)
            << std::endl;
    }

    PatternEval pattern_eval = DefaultPatternEval();
    HashTablePVS tt{ 100'000'000 };
    const int size = 500;
    const int max_empty_count = 24;

    std::vector<Position> pos;
    for (int empty_count = 1; empty_count <= max_empty_count; empty_count++)
        std::generate_n(
            std::back_inserter(pos),
            size,
            PosGen::RandomPlayed(empty_count)
        );

    std::vector<int> score(pos.size() * (max_empty_count + 1), undefined_score);

    #pragma omp parallel for schedule(dynamic,1)
    for (int i = 0; i < pos.size(); i++)
    {
        int j = i * (max_empty_count + 1);
        for (int d = 0; d <= pos[i].EmptyCount(); d++)
            score[j + d] = PVS{ tt, pattern_eval }.Score(pos[i], d);

        #pragma omp critical
        {
            std::cout << "e" << pos[i].EmptyCount() << "{";
            for (int d = 0; d <= pos[i].EmptyCount(); d++)
                std::cout << score[j + d] << ",";
            std::cout << "}" << std::endl;
        }
    }
    Save(R"(G:\Reversi\weights\dDE.w)", score);

    MagicFormulaFit();
    return 0;
}
