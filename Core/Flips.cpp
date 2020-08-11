#include "Position.h"
#include "Bit.h"
#include <array>

alignas(64) static const std::array<int64, 1024> masks = {
	0x00000000000000fei64, 0x0101010101010100i64, 0x8040201008040200i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x00000000000000fci64, 0x0202020202020200i64, 0x0080402010080400i64, 0x0000000000000100i64, 0x0000000000000001i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x00000000000000f8i64, 0x0404040404040400i64, 0x0000804020100800i64, 0x0000000000010200i64, 0x0000000000000003i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x00000000000000f0i64, 0x0808080808080800i64, 0x0000008040201000i64, 0x0000000001020400i64, 0x0000000000000007i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x00000000000000e0i64, 0x1010101010101000i64, 0x0000000080402000i64, 0x0000000102040800i64, 0x000000000000000fi64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x00000000000000c0i64, 0x2020202020202000i64, 0x0000000000804000i64, 0x0000010204081000i64, 0x000000000000001fi64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x0000000000000080i64, 0x4040404040404000i64, 0x0000000000008000i64, 0x0001020408102000i64, 0x000000000000003fi64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x0000000000000000i64, 0x8080808080808000i64, 0x0000000000000000i64, 0x0102040810204000i64, 0x000000000000007fi64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64,
	0x000000000000fe00i64, 0x0101010101010000i64, 0x4020100804020000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000001i64, 0x0000000000000000i64, 0x0000000000000002i64,
	0x000000000000fc00i64, 0x0202020202020000i64, 0x8040201008040000i64, 0x0000000000010000i64, 0x0000000000000100i64, 0x0000000000000002i64, 0x0000000000000001i64, 0x0000000000000004i64,
	0x000000000000f800i64, 0x0404040404040000i64, 0x0080402010080000i64, 0x0000000001020000i64, 0x0000000000000300i64, 0x0000000000000004i64, 0x0000000000000002i64, 0x0000000000000008i64,
	0x000000000000f000i64, 0x0808080808080000i64, 0x0000804020100000i64, 0x0000000102040000i64, 0x0000000000000700i64, 0x0000000000000008i64, 0x0000000000000004i64, 0x0000000000000010i64,
	0x000000000000e000i64, 0x1010101010100000i64, 0x0000008040200000i64, 0x0000010204080000i64, 0x0000000000000f00i64, 0x0000000000000010i64, 0x0000000000000008i64, 0x0000000000000020i64,
	0x000000000000c000i64, 0x2020202020200000i64, 0x0000000080400000i64, 0x0001020408100000i64, 0x0000000000001f00i64, 0x0000000000000020i64, 0x0000000000000010i64, 0x0000000000000040i64,
	0x0000000000008000i64, 0x4040404040400000i64, 0x0000000000800000i64, 0x0102040810200000i64, 0x0000000000003f00i64, 0x0000000000000040i64, 0x0000000000000020i64, 0x0000000000000080i64,
	0x0000000000000000i64, 0x8080808080800000i64, 0x0000000000000000i64, 0x0204081020400000i64, 0x0000000000007f00i64, 0x0000000000000080i64, 0x0000000000000040i64, 0x0000000000000000i64,
	0x0000000000fe0000i64, 0x0101010101000000i64, 0x2010080402000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000101i64, 0x0000000000000000i64, 0x0000000000000204i64,
	0x0000000000fc0000i64, 0x0202020202000000i64, 0x4020100804000000i64, 0x0000000001000000i64, 0x0000000000010000i64, 0x0000000000000202i64, 0x0000000000000100i64, 0x0000000000000408i64,
	0x0000000000f80000i64, 0x0404040404000000i64, 0x8040201008000000i64, 0x0000000102000000i64, 0x0000000000030000i64, 0x0000000000000404i64, 0x0000000000000201i64, 0x0000000000000810i64,
	0x0000000000f00000i64, 0x0808080808000000i64, 0x0080402010000000i64, 0x0000010204000000i64, 0x0000000000070000i64, 0x0000000000000808i64, 0x0000000000000402i64, 0x0000000000001020i64,
	0x0000000000e00000i64, 0x1010101010000000i64, 0x0000804020000000i64, 0x0001020408000000i64, 0x00000000000f0000i64, 0x0000000000001010i64, 0x0000000000000804i64, 0x0000000000002040i64,
	0x0000000000c00000i64, 0x2020202020000000i64, 0x0000008040000000i64, 0x0102040810000000i64, 0x00000000001f0000i64, 0x0000000000002020i64, 0x0000000000001008i64, 0x0000000000004080i64,
	0x0000000000800000i64, 0x4040404040000000i64, 0x0000000080000000i64, 0x0204081020000000i64, 0x00000000003f0000i64, 0x0000000000004040i64, 0x0000000000002010i64, 0x0000000000008000i64,
	0x0000000000000000i64, 0x8080808080000000i64, 0x0000000000000000i64, 0x0408102040000000i64, 0x00000000007f0000i64, 0x0000000000008080i64, 0x0000000000004020i64, 0x0000000000000000i64,
	0x00000000fe000000i64, 0x0101010100000000i64, 0x1008040200000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000010101i64, 0x0000000000000000i64, 0x0000000000020408i64,
	0x00000000fc000000i64, 0x0202020200000000i64, 0x2010080400000000i64, 0x0000000100000000i64, 0x0000000001000000i64, 0x0000000000020202i64, 0x0000000000010000i64, 0x0000000000040810i64,
	0x00000000f8000000i64, 0x0404040400000000i64, 0x4020100800000000i64, 0x0000010200000000i64, 0x0000000003000000i64, 0x0000000000040404i64, 0x0000000000020100i64, 0x0000000000081020i64,
	0x00000000f0000000i64, 0x0808080800000000i64, 0x8040201000000000i64, 0x0001020400000000i64, 0x0000000007000000i64, 0x0000000000080808i64, 0x0000000000040201i64, 0x0000000000102040i64,
	0x00000000e0000000i64, 0x1010101000000000i64, 0x0080402000000000i64, 0x0102040800000000i64, 0x000000000f000000i64, 0x0000000000101010i64, 0x0000000000080402i64, 0x0000000000204080i64,
	0x00000000c0000000i64, 0x2020202000000000i64, 0x0000804000000000i64, 0x0204081000000000i64, 0x000000001f000000i64, 0x0000000000202020i64, 0x0000000000100804i64, 0x0000000000408000i64,
	0x0000000080000000i64, 0x4040404000000000i64, 0x0000008000000000i64, 0x0408102000000000i64, 0x000000003f000000i64, 0x0000000000404040i64, 0x0000000000201008i64, 0x0000000000800000i64,
	0x0000000000000000i64, 0x8080808000000000i64, 0x0000000000000000i64, 0x0810204000000000i64, 0x000000007f000000i64, 0x0000000000808080i64, 0x0000000000402010i64, 0x0000000000000000i64,
	0x000000fe00000000i64, 0x0101010000000000i64, 0x0804020000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000001010101i64, 0x0000000000000000i64, 0x0000000002040810i64,
	0x000000fc00000000i64, 0x0202020000000000i64, 0x1008040000000000i64, 0x0000010000000000i64, 0x0000000100000000i64, 0x0000000002020202i64, 0x0000000001000000i64, 0x0000000004081020i64,
	0x000000f800000000i64, 0x0404040000000000i64, 0x2010080000000000i64, 0x0001020000000000i64, 0x0000000300000000i64, 0x0000000004040404i64, 0x0000000002010000i64, 0x0000000008102040i64,
	0x000000f000000000i64, 0x0808080000000000i64, 0x4020100000000000i64, 0x0102040000000000i64, 0x0000000700000000i64, 0x0000000008080808i64, 0x0000000004020100i64, 0x0000000010204080i64,
	0x000000e000000000i64, 0x1010100000000000i64, 0x8040200000000000i64, 0x0204080000000000i64, 0x0000000f00000000i64, 0x0000000010101010i64, 0x0000000008040201i64, 0x0000000020408000i64,
	0x000000c000000000i64, 0x2020200000000000i64, 0x0080400000000000i64, 0x0408100000000000i64, 0x0000001f00000000i64, 0x0000000020202020i64, 0x0000000010080402i64, 0x0000000040800000i64,
	0x0000008000000000i64, 0x4040400000000000i64, 0x0000800000000000i64, 0x0810200000000000i64, 0x0000003f00000000i64, 0x0000000040404040i64, 0x0000000020100804i64, 0x0000000080000000i64,
	0x0000000000000000i64, 0x8080800000000000i64, 0x0000000000000000i64, 0x1020400000000000i64, 0x0000007f00000000i64, 0x0000000080808080i64, 0x0000000040201008i64, 0x0000000000000000i64,
	0x0000fe0000000000i64, 0x0101000000000000i64, 0x0402000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000101010101i64, 0x0000000000000000i64, 0x0000000204081020i64,
	0x0000fc0000000000i64, 0x0202000000000000i64, 0x0804000000000000i64, 0x0001000000000000i64, 0x0000010000000000i64, 0x0000000202020202i64, 0x0000000100000000i64, 0x0000000408102040i64,
	0x0000f80000000000i64, 0x0404000000000000i64, 0x1008000000000000i64, 0x0102000000000000i64, 0x0000030000000000i64, 0x0000000404040404i64, 0x0000000201000000i64, 0x0000000810204080i64,
	0x0000f00000000000i64, 0x0808000000000000i64, 0x2010000000000000i64, 0x0204000000000000i64, 0x0000070000000000i64, 0x0000000808080808i64, 0x0000000402010000i64, 0x0000001020408000i64,
	0x0000e00000000000i64, 0x1010000000000000i64, 0x4020000000000000i64, 0x0408000000000000i64, 0x00000f0000000000i64, 0x0000001010101010i64, 0x0000000804020100i64, 0x0000002040800000i64,
	0x0000c00000000000i64, 0x2020000000000000i64, 0x8040000000000000i64, 0x0810000000000000i64, 0x00001f0000000000i64, 0x0000002020202020i64, 0x0000001008040201i64, 0x0000004080000000i64,
	0x0000800000000000i64, 0x4040000000000000i64, 0x0080000000000000i64, 0x1020000000000000i64, 0x00003f0000000000i64, 0x0000004040404040i64, 0x0000002010080402i64, 0x0000008000000000i64,
	0x0000000000000000i64, 0x8080000000000000i64, 0x0000000000000000i64, 0x2040000000000000i64, 0x00007f0000000000i64, 0x0000008080808080i64, 0x0000004020100804i64, 0x0000000000000000i64,
	0x00fe000000000000i64, 0x0100000000000000i64, 0x0200000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000010101010101i64, 0x0000000000000000i64, 0x0000020408102040i64,
	0x00fc000000000000i64, 0x0200000000000000i64, 0x0400000000000000i64, 0x0100000000000000i64, 0x0001000000000000i64, 0x0000020202020202i64, 0x0000010000000000i64, 0x0000040810204080i64,
	0x00f8000000000000i64, 0x0400000000000000i64, 0x0800000000000000i64, 0x0200000000000000i64, 0x0003000000000000i64, 0x0000040404040404i64, 0x0000020100000000i64, 0x0000081020408000i64,
	0x00f0000000000000i64, 0x0800000000000000i64, 0x1000000000000000i64, 0x0400000000000000i64, 0x0007000000000000i64, 0x0000080808080808i64, 0x0000040201000000i64, 0x0000102040800000i64,
	0x00e0000000000000i64, 0x1000000000000000i64, 0x2000000000000000i64, 0x0800000000000000i64, 0x000f000000000000i64, 0x0000101010101010i64, 0x0000080402010000i64, 0x0000204080000000i64,
	0x00c0000000000000i64, 0x2000000000000000i64, 0x4000000000000000i64, 0x1000000000000000i64, 0x001f000000000000i64, 0x0000202020202020i64, 0x0000100804020100i64, 0x0000408000000000i64,
	0x0080000000000000i64, 0x4000000000000000i64, 0x8000000000000000i64, 0x2000000000000000i64, 0x003f000000000000i64, 0x0000404040404040i64, 0x0000201008040201i64, 0x0000800000000000i64,
	0x0000000000000000i64, 0x8000000000000000i64, 0x0000000000000000i64, 0x4000000000000000i64, 0x007f000000000000i64, 0x0000808080808080i64, 0x0000402010080402i64, 0x0000000000000000i64,
	0xfe00000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0001010101010101i64, 0x0000000000000000i64, 0x0002040810204080i64,
	0xfc00000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0100000000000000i64, 0x0002020202020202i64, 0x0001000000000000i64, 0x0004081020408000i64,
	0xf800000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0300000000000000i64, 0x0004040404040404i64, 0x0002010000000000i64, 0x0008102040800000i64,
	0xf000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0700000000000000i64, 0x0008080808080808i64, 0x0004020100000000i64, 0x0010204080000000i64,
	0xe000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0f00000000000000i64, 0x0010101010101010i64, 0x0008040201000000i64, 0x0020408000000000i64,
	0xc000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x1f00000000000000i64, 0x0020202020202020i64, 0x0010080402010000i64, 0x0040800000000000i64,
	0x8000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x3f00000000000000i64, 0x0040404040404040i64, 0x0020100804020100i64, 0x0080000000000000i64,
	0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x0000000000000000i64, 0x7f00000000000000i64, 0x0080808080808080i64, 0x0040201008040201i64, 0x0000000000000000i64,
};

BitBoard Flips(const Position& pos, Field move) noexcept
{
	const int64x4 P(pos.Player());
	const int64x4 O(pos.Opponent());
	const int64x4 mask1(_mm256_load_si256(reinterpret_cast<const __m256i*>(masks.data() + static_cast<uint64>(move) * 8 + 0)));
	const int64x4 mask2(_mm256_load_si256(reinterpret_cast<const __m256i*>(masks.data() + static_cast<uint64>(move) * 8 + 4)));

	int64x4 outflank1 = andnot(O, mask1);
	// look for non-opponent LS1B
	outflank1 &= -outflank1;
	outflank1 &= P;
	outflank1 += (outflank1 != int64x4{});
	const int64x4 flip1 = outflank1 & mask1;

	// isolate non-opponent MS1B by clearing lower bits
	int64x4 outflank2 = (P & mask2) << int64x4(7, 9, 8, 1);
	int64x4 eraser = andnot(O, mask2);
	eraser |= eraser >> int64x4(7, 9, 8, 1);
	eraser |= eraser >> int64x4(14, 18, 16, 2);
	eraser |= eraser >> int64x4(28, 36, 32, 4);

	// set mask bits higher than outflank
	const int64x4 flip2 = -andnot(eraser, outflank2) & mask2;

	return reduce_or(flip1 | flip2);
}