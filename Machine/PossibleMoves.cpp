#include "PossibleMoves.h"
#include "Machine/BitTwiddling.h"

uint64_t PossibleMoves(const uint64_t P, const uint64_t O)
{
	#if defined(HAS_AVX512)
		return PossibleMoves_AVX512(P, O);
	#elif defined(HAS_AVX2)
		return PossibleMoves_AVX2(P, O);
	#elif defined(HAS_SSE2)
		return PossibleMoves_SSE2(P, O);
	#else
		return PossibleMoves_x64(P, O);
	#endif
}

#if defined(HAS_AVX512)
uint64_t PossibleMoves_AVX512(const uint64_t P, const uint64_t O)
{
	// 6 x SHIFT, 7 x AND, 5 x OR, 1 x NOT
	// = 19 OPs

	// 1 x AND
	const __m512i PP = _mm512_set1_epi64(P);
	const __m512i maskO = _mm512_set1_epi64(O) & _mm512_set_epi64(0x7E7E7E7E7E7E7E7Eui64, 0x00FFFFFFFFFFFF00ui64, 0x007E7E7E7E7E7E00ui64, 0x007E7E7E7E7E7E00ui64, 0x7E7E7E7E7E7E7E7Eui64, 0x00FFFFFFFFFFFF00ui64, 0x007E7E7E7E7E7E00ui64, 0x007E7E7E7E7E7E00ui64);
	const __m512i shift1 = _mm512_set_epi64(1, 8, 7, 9, -1, -8, -7, -9);
	const __m512i shift2 = shift1 + shift1;
	__m512i mask;
	__m512i flip;

	// 6 x SHIFT, 5 x AND, 3 x OR
	flip = maskO & _mm512_rolv_epi64(PP, shift1);
	flip |= maskO & _mm512_rolv_epi64(flip, shift1);
	mask = maskO & _mm512_rolv_epi64(maskO, shift1);
	flip |= mask & _mm512_rolv_epi64(flip, shift2);
	flip |= mask & _mm512_rolv_epi64(flip, shift2);
	flip = _mm512_rolv_epi64(flip, shift1);

	// 1 x NOT, 2 x OR, 1 x AND
	return ~(P | O) & _mm512_reduce_or_epi64(flip);
}
#endif

#if defined(HAS_AVX2)
uint64_t PossibleMoves_AVX2(const uint64_t P, const uint64_t O)
{
	// 10 x SHIFT, 11 x AND, 10 x OR, 1 x NOT
	// = 32 OPs

	// 1 x AND
	const __m256i PP = _mm256_set1_epi64x(P);
	const __m256i maskO = _mm256_set1_epi64x(O) & _mm256_set_epi64x(0x7E7E7E7E7E7E7E7Eui64, 0x00FFFFFFFFFFFF00ui64, 0x007E7E7E7E7E7E00ui64, 0x007E7E7E7E7E7E00ui64);
	const __m256i shift1 = _mm256_set_epi64x(1, 8, 7, 9);
	const __m256i shift2 = shift1 + shift1;
	__m256i mask1, mask2;
	__m256i flip1, flip2;

	// 2 x SHIFT, 2 x AND
	flip1 = maskO & _mm256_sllv_epi64(PP, shift1);
	flip2 = maskO & _mm256_srlv_epi64(PP, shift1);

	// 2 x SHIFT, 2 x AND, 2 x OR
	flip1 |= maskO & _mm256_sllv_epi64(flip1, shift1);
	flip2 |= maskO & _mm256_srlv_epi64(flip2, shift1);

	// 2 x SHIFT, 1 x AND
	mask1 = maskO & _mm256_sllv_epi64(maskO, shift1);
	mask2 = _mm256_srlv_epi64(mask1, shift1);

	// 2 x SHIFT, 2 x AND, 2 x OR
	flip1 |= mask1 & _mm256_sllv_epi64(flip1, shift2);
	flip2 |= mask2 & _mm256_srlv_epi64(flip2, shift2);

	// 2 x SHIFT, 2 x AND, 2 x OR
	flip1 |= mask1 & _mm256_sllv_epi64(flip1, shift2);
	flip2 |= mask2 & _mm256_srlv_epi64(flip2, shift2);

	// 2 x SHIFT
	flip1 = _mm256_sllv_epi64(flip1, shift1);
	flip2 = _mm256_srlv_epi64(flip2, shift1);

	// 2 x OR
	flip1 |= flip2;
	__m128i flip = _mm256_castsi256_si128(flip1) | _mm256_extracti128_si256(flip1, 1);

	// 1 x NOT, 2 x OR, 1 x AND
	return ~(P | O) & (_mm_extract_epi64(flip, 0) | _mm_extract_epi64(flip, 1));
}
#endif

#if defined(HAS_SSE2)
uint64_t PossibleMoves_SSE2(const uint64_t P, const uint64_t O)
{
	// 30 x SHIFT, 28 x AND, 21 x OR, 1 x NOT, 2 x BSWAP
	// = 82 OPs
	uint64_t mask1, mask2, mask6, mask7, mask8;
	uint64_t flip1, flip2, flip6, flip7, flip8;
	__m128i mask3, mask4, mask5;
	__m128i flip3, flip4, flip5;

	// 2 x MOV, 2 x BSWAP
	const __m128i PP = _mm_set_epi64x(BSwap(P), P);
	const __m128i OO = _mm_set_epi64x(BSwap(O), O);

	// 2 x AND
	const uint64_t maskO = O & 0x7E7E7E7E7E7E7E7Eui64;
	const __m128i  maskOO = OO & _mm_set1_epi64x(0x7E7E7E7E7E7E7E7Eui64);

	// 5 x SHIFT, 5 x AND
	flip1 = maskO & (P << 1);
	flip2 = maskO & (P >> 1);
	flip3 = OO & _mm_slli_epi64(PP, 8);
	flip4 = maskOO & _mm_slli_epi64(PP, 7);
	flip5 = maskOO & _mm_srli_epi64(PP, 7);

	// 5 x SHIFT, 5 x AND, 5 x OR
	flip1 |= maskO & (flip1 << 1);
	flip2 |= maskO & (flip2 >> 1);
	flip3 |= OO & _mm_slli_epi64(flip3, 8);
	flip4 |= maskOO & _mm_slli_epi64(flip4, 7);
	flip5 |= maskOO & _mm_srli_epi64(flip5, 7);

	// 5 x SHIFT, 5 x AND
	mask1 = maskO & (maskO << 1);              mask2 = (mask1 >> 1);
	mask3 = OO & _mm_slli_epi64(OO, 8);
	mask4 = maskOO & _mm_slli_epi64(maskOO, 7); mask5 = _mm_srli_epi64(mask4, 7);

	// 5 x SHIFT, 5 x AND, 5 x OR
	flip1 |= mask1 & (flip1 << 2);
	flip2 |= mask2 & (flip2 >> 2);
	flip3 |= mask3 & _mm_slli_epi64(flip3, 16);
	flip4 |= mask4 & _mm_slli_epi64(flip4, 14);
	flip5 |= mask5 & _mm_srli_epi64(flip5, 14);

	// 5 x SHIFT, 5 x AND, 5 x OR
	flip1 |= mask1 & (flip1 << 2);
	flip2 |= mask2 & (flip2 >> 2);
	flip3 |= mask3 & _mm_slli_epi64(flip3, 16);
	flip4 |= mask4 & _mm_slli_epi64(flip4, 14);
	flip5 |= mask5 & _mm_srli_epi64(flip5, 14);

	// 5 x SHIFT
	flip1 <<= 1;
	flip2 >>= 1;
	flip3 = _mm_slli_epi64(flip3, 8);
	flip4 = _mm_slli_epi64(flip4, 7);
	flip5 = _mm_srli_epi64(flip5, 7);

	// 2 x OR
	flip3 |= flip4 | flip5;

	// 1 x AND, 4 x OR, 1 x NOT
	return ~(P | O) & (flip1 | flip2 | BSwap(_mm_extract_epi64(flip3, 1)) | _mm_extract_epi64(flip3, 0));
}
#endif

uint64_t PossibleMoves_x64(const uint64_t P, const uint64_t O)
{
	// 48 x SHIFT, 42 x AND, 32 x OR, 1 x NOT
	// = 123 OPs

	uint64_t mask1, mask2, mask3, mask4, mask5, mask6, mask7, mask8;
	uint64_t flip1, flip2, flip3, flip4, flip5, flip6, flip7, flip8;

	// 1 x AND
	const uint64_t maskO = O & 0x7E7E7E7E7E7E7E7Eui64;

	// 8 x SHIFT, 8 x AND
	flip1 = maskO & (P << 1);
	flip2 = maskO & (P >> 1);
	flip3 = O & (P << 8);
	flip4 = O & (P >> 8);
	flip5 = maskO & (P << 7);
	flip6 = maskO & (P >> 7);
	flip7 = maskO & (P << 9);
	flip8 = maskO & (P >> 9);

	// 8 x SHIFT, 8 x AND, 8 x OR
	flip1 |= maskO & (flip1 << 1);
	flip2 |= maskO & (flip2 >> 1);
	flip3 |= O & (flip3 << 8);
	flip4 |= O & (flip4 >> 8);
	flip5 |= maskO & (flip5 << 7);
	flip6 |= maskO & (flip6 >> 7);
	flip7 |= maskO & (flip7 << 9);
	flip8 |= maskO & (flip8 >> 9);

	// 8 x SHIFT, 8 x AND
	mask1 = maskO & (maskO << 1); mask2 = mask1 >> 1;
	mask3 = O & (O << 8); mask4 = mask3 >> 8;
	mask5 = maskO & (maskO << 7); mask6 = mask5 >> 7;
	mask7 = maskO & (maskO << 9); mask8 = mask7 >> 9;

	// 8 x SHIFT, 8 x AND, 8 x OR
	flip1 |= mask1 & (flip1 << 2);
	flip2 |= mask2 & (flip2 >> 2);
	flip3 |= mask3 & (flip3 << 16);
	flip4 |= mask4 & (flip4 >> 16);
	flip5 |= mask5 & (flip5 << 14);
	flip6 |= mask6 & (flip6 >> 14);
	flip7 |= mask7 & (flip7 << 18);
	flip8 |= mask8 & (flip8 >> 18);

	// 8 x SHIFT, 8 x AND, 8 x OR
	flip1 |= mask1 & (flip1 << 2);
	flip2 |= mask2 & (flip2 >> 2);
	flip3 |= mask3 & (flip3 << 16);
	flip4 |= mask4 & (flip4 >> 16);
	flip5 |= mask5 & (flip5 << 14);
	flip6 |= mask6 & (flip6 >> 14);
	flip7 |= mask7 & (flip7 << 18);
	flip8 |= mask8 & (flip8 >> 18);

	// 8 x SHIFT
	flip1 <<= 1;
	flip2 >>= 1;
	flip3 <<= 8;
	flip4 >>= 8;
	flip5 <<= 7;
	flip6 >>= 7;
	flip7 <<= 9;
	flip8 >>= 9;

	// 1 x AND, 8 x OR, 1 x NOT
	return ~(P | O) & (flip1 | flip2 | flip3 | flip4 | flip5 | flip6 | flip7 | flip8);
}