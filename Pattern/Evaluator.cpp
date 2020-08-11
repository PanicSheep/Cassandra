#include "Evaluator.h"
#include "Helpers.h"
#include "ConfigIndexer.h"
#include <cassert>
#include <iterator>

using namespace Pattern;

class HorizontalSymmetricEvaluator final : public Evaluator
{
	const BitBoard m_pattern_C, m_pattern_D, m_pattern_V;
	Weights m_w0, m_w1, m_w2, m_w3;
public:
	HorizontalSymmetricEvaluator(BitBoard pattern, std::vector<Weights> weights)
		: Evaluator(pattern)
		, m_pattern_C(FlipCodiagonal(pattern))
		, m_pattern_D(FlipDiagonal(pattern))
		, m_pattern_V(FlipVertical(pattern))
		, m_w0(std::move(weights[0]))
		, m_w1(std::move(weights[1]))
		, m_w2(std::move(weights[2]))
		, m_w3(std::move(weights[3]))
	{
		assert(pattern == FlipHorizontal(pattern));
	}

	float Eval(const Position& pos) const final
	{
		return m_w0[Index(pos, Pattern)]
			+ m_w1[Index(pos, m_pattern_C)]
			+ m_w2[Index(pos, m_pattern_D)]
			+ m_w3[Index(pos, m_pattern_V)];
	}
};

class DiagonalSymmetricEvaluator final : public Evaluator
{
	const BitBoard m_pattern_C, m_pattern_H, m_pattern_V;
	Weights m_w0, m_w1, m_w2, m_w3;
public:
	DiagonalSymmetricEvaluator(BitBoard pattern, std::vector<Weights> weights)
		: Evaluator(pattern)
		, m_pattern_C(FlipCodiagonal(pattern))
		, m_pattern_H(FlipHorizontal(pattern))
		, m_pattern_V(FlipVertical(pattern))
		, m_w0(std::move(weights[0]))
		, m_w1(std::move(weights[1]))
		, m_w2(std::move(weights[2]))
		, m_w3(std::move(weights[3]))
	{
		assert(pattern == FlipDiagonal(pattern));
	}

	float Eval(const Position& pos) const final
	{
		return m_w0[Index(pos, Pattern)]
			+ m_w1[Index(pos, m_pattern_C)]
			+ m_w2[Index(pos, m_pattern_H)]
			+ m_w3[Index(pos, m_pattern_V)];
	}
};

class AsymmetricEvaluator final : public Evaluator
{
	const BitBoard m_pattern_C, m_pattern_D, m_pattern_H, m_pattern_V, m_patternHC, m_patternHD, m_patternHV;
	Weights m_w0, m_w1, m_w2, m_w3, m_w4, m_w5, m_w6, m_w7;
public:
	AsymmetricEvaluator(BitBoard pattern, std::vector<Weights> weights)
		: Evaluator(pattern)
		, m_pattern_C(FlipCodiagonal(pattern))
		, m_pattern_D(FlipDiagonal(pattern))
		, m_pattern_H(FlipHorizontal(pattern))
		, m_pattern_V(FlipVertical(pattern))
		, m_patternHC(FlipCodiagonal(FlipHorizontal(pattern)))
		, m_patternHD(FlipDiagonal(FlipHorizontal(pattern)))
		, m_patternHV(FlipVertical(FlipHorizontal(pattern)))
		, m_w0(std::move(weights[0]))
		, m_w1(std::move(weights[1]))
		, m_w2(std::move(weights[2]))
		, m_w3(std::move(weights[3]))
		, m_w4(std::move(weights[4]))
		, m_w5(std::move(weights[5]))
		, m_w6(std::move(weights[6]))
		, m_w7(std::move(weights[7]))
	{}

	float Eval(const Position& pos) const final
	{
		return m_w0[Index(pos, Pattern)]
			+ m_w1[Index(pos, m_pattern_C)]
			+ m_w2[Index(pos, m_pattern_D)]
			+ m_w3[Index(pos, m_pattern_H)]
			+ m_w4[Index(pos, m_pattern_V)]
			+ m_w5[Index(pos, m_patternHC)]
			+ m_w6[Index(pos, m_patternHD)]
			+ m_w7[Index(pos, m_patternHV)];
	}
};

std::unique_ptr<Evaluator> Pattern::CreateEvaluator(const BitBoard pattern, std::vector<Weights> weights)
{
	if (pattern == FlipHorizontal(pattern))
		return std::make_unique<HorizontalSymmetricEvaluator>(pattern, std::move(weights));
	if (pattern == FlipDiagonal(pattern))
		return std::make_unique<DiagonalSymmetricEvaluator>(pattern, std::move(weights));
	return std::make_unique<AsymmetricEvaluator>(pattern, std::move(weights));
}

std::unique_ptr<Evaluator> Pattern::CreateEvaluator(const BitBoard pattern, const Weights& compressed)
{
	const auto config_indexer = CreateConfigIndexer(pattern);
	const auto multiplicity = config_indexer->group_order;
	const std::size_t full_size = Pow_int(3, popcount(pattern));
	const auto patterns = config_indexer->Patterns();

	// Reserve memory for weights
	std::vector<Weights> weights(multiplicity);
	for (auto& w : weights)
		w.resize(full_size);

	// Decompress weights
	for (std::size_t i = 0; i < multiplicity; i++)
		for (const auto& config : Configurations(patterns[i]))
		{
			std::vector<int> indices;
			indices.reserve(multiplicity);

			config_indexer->generate(std::back_inserter(indices), config);

			weights[i][Index(config, patterns[i])] = compressed[indices[i]];
		}

	return CreateEvaluator(pattern, std::move(weights));
}
