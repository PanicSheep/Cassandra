#include "Position.h"
#include "Bit.h"
#include "MoreTypes.h"
#include <array>

#ifdef __CUDA_ARCH__
	__constant__ static const uint64 masks[1024] = {
#else
	static const std::array<int64, 1024> masks = {
#endif

	0x00000000000000feI64, 0x0101010101010100I64, 0x8040201008040200I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x00000000000000fcI64, 0x0202020202020200I64, 0x0080402010080400I64, 0x0000000000000100I64, 0x0000000000000001I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x00000000000000f8I64, 0x0404040404040400I64, 0x0000804020100800I64, 0x0000000000010200I64, 0x0000000000000003I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x00000000000000f0I64, 0x0808080808080800I64, 0x0000008040201000I64, 0x0000000001020400I64, 0x0000000000000007I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x00000000000000e0I64, 0x1010101010101000I64, 0x0000000080402000I64, 0x0000000102040800I64, 0x000000000000000fI64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x00000000000000c0I64, 0x2020202020202000I64, 0x0000000000804000I64, 0x0000010204081000I64, 0x000000000000001fI64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x0000000000000080I64, 0x4040404040404000I64, 0x0000000000008000I64, 0x0001020408102000I64, 0x000000000000003fI64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x0000000000000000I64, 0x8080808080808000I64, 0x0000000000000000I64, 0x0102040810204000I64, 0x000000000000007fI64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64,
	0x000000000000fe00I64, 0x0101010101010000I64, 0x4020100804020000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000001I64, 0x0000000000000000I64, 0x0000000000000002I64,
	0x000000000000fc00I64, 0x0202020202020000I64, 0x8040201008040000I64, 0x0000000000010000I64, 0x0000000000000100I64, 0x0000000000000002I64, 0x0000000000000001I64, 0x0000000000000004I64,
	0x000000000000f800I64, 0x0404040404040000I64, 0x0080402010080000I64, 0x0000000001020000I64, 0x0000000000000300I64, 0x0000000000000004I64, 0x0000000000000002I64, 0x0000000000000008I64,
	0x000000000000f000I64, 0x0808080808080000I64, 0x0000804020100000I64, 0x0000000102040000I64, 0x0000000000000700I64, 0x0000000000000008I64, 0x0000000000000004I64, 0x0000000000000010I64,
	0x000000000000e000I64, 0x1010101010100000I64, 0x0000008040200000I64, 0x0000010204080000I64, 0x0000000000000f00I64, 0x0000000000000010I64, 0x0000000000000008I64, 0x0000000000000020I64,
	0x000000000000c000I64, 0x2020202020200000I64, 0x0000000080400000I64, 0x0001020408100000I64, 0x0000000000001f00I64, 0x0000000000000020I64, 0x0000000000000010I64, 0x0000000000000040I64,
	0x0000000000008000I64, 0x4040404040400000I64, 0x0000000000800000I64, 0x0102040810200000I64, 0x0000000000003f00I64, 0x0000000000000040I64, 0x0000000000000020I64, 0x0000000000000080I64,
	0x0000000000000000I64, 0x8080808080800000I64, 0x0000000000000000I64, 0x0204081020400000I64, 0x0000000000007f00I64, 0x0000000000000080I64, 0x0000000000000040I64, 0x0000000000000000I64,
	0x0000000000fe0000I64, 0x0101010101000000I64, 0x2010080402000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000101I64, 0x0000000000000000I64, 0x0000000000000204I64,
	0x0000000000fc0000I64, 0x0202020202000000I64, 0x4020100804000000I64, 0x0000000001000000I64, 0x0000000000010000I64, 0x0000000000000202I64, 0x0000000000000100I64, 0x0000000000000408I64,
	0x0000000000f80000I64, 0x0404040404000000I64, 0x8040201008000000I64, 0x0000000102000000I64, 0x0000000000030000I64, 0x0000000000000404I64, 0x0000000000000201I64, 0x0000000000000810I64,
	0x0000000000f00000I64, 0x0808080808000000I64, 0x0080402010000000I64, 0x0000010204000000I64, 0x0000000000070000I64, 0x0000000000000808I64, 0x0000000000000402I64, 0x0000000000001020I64,
	0x0000000000e00000I64, 0x1010101010000000I64, 0x0000804020000000I64, 0x0001020408000000I64, 0x00000000000f0000I64, 0x0000000000001010I64, 0x0000000000000804I64, 0x0000000000002040I64,
	0x0000000000c00000I64, 0x2020202020000000I64, 0x0000008040000000I64, 0x0102040810000000I64, 0x00000000001f0000I64, 0x0000000000002020I64, 0x0000000000001008I64, 0x0000000000004080I64,
	0x0000000000800000I64, 0x4040404040000000I64, 0x0000000080000000I64, 0x0204081020000000I64, 0x00000000003f0000I64, 0x0000000000004040I64, 0x0000000000002010I64, 0x0000000000008000I64,
	0x0000000000000000I64, 0x8080808080000000I64, 0x0000000000000000I64, 0x0408102040000000I64, 0x00000000007f0000I64, 0x0000000000008080I64, 0x0000000000004020I64, 0x0000000000000000I64,
	0x00000000fe000000I64, 0x0101010100000000I64, 0x1008040200000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000010101I64, 0x0000000000000000I64, 0x0000000000020408I64,
	0x00000000fc000000I64, 0x0202020200000000I64, 0x2010080400000000I64, 0x0000000100000000I64, 0x0000000001000000I64, 0x0000000000020202I64, 0x0000000000010000I64, 0x0000000000040810I64,
	0x00000000f8000000I64, 0x0404040400000000I64, 0x4020100800000000I64, 0x0000010200000000I64, 0x0000000003000000I64, 0x0000000000040404I64, 0x0000000000020100I64, 0x0000000000081020I64,
	0x00000000f0000000I64, 0x0808080800000000I64, 0x8040201000000000I64, 0x0001020400000000I64, 0x0000000007000000I64, 0x0000000000080808I64, 0x0000000000040201I64, 0x0000000000102040I64,
	0x00000000e0000000I64, 0x1010101000000000I64, 0x0080402000000000I64, 0x0102040800000000I64, 0x000000000f000000I64, 0x0000000000101010I64, 0x0000000000080402I64, 0x0000000000204080I64,
	0x00000000c0000000I64, 0x2020202000000000I64, 0x0000804000000000I64, 0x0204081000000000I64, 0x000000001f000000I64, 0x0000000000202020I64, 0x0000000000100804I64, 0x0000000000408000I64,
	0x0000000080000000I64, 0x4040404000000000I64, 0x0000008000000000I64, 0x0408102000000000I64, 0x000000003f000000I64, 0x0000000000404040I64, 0x0000000000201008I64, 0x0000000000800000I64,
	0x0000000000000000I64, 0x8080808000000000I64, 0x0000000000000000I64, 0x0810204000000000I64, 0x000000007f000000I64, 0x0000000000808080I64, 0x0000000000402010I64, 0x0000000000000000I64,
	0x000000fe00000000I64, 0x0101010000000000I64, 0x0804020000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000001010101I64, 0x0000000000000000I64, 0x0000000002040810I64,
	0x000000fc00000000I64, 0x0202020000000000I64, 0x1008040000000000I64, 0x0000010000000000I64, 0x0000000100000000I64, 0x0000000002020202I64, 0x0000000001000000I64, 0x0000000004081020I64,
	0x000000f800000000I64, 0x0404040000000000I64, 0x2010080000000000I64, 0x0001020000000000I64, 0x0000000300000000I64, 0x0000000004040404I64, 0x0000000002010000I64, 0x0000000008102040I64,
	0x000000f000000000I64, 0x0808080000000000I64, 0x4020100000000000I64, 0x0102040000000000I64, 0x0000000700000000I64, 0x0000000008080808I64, 0x0000000004020100I64, 0x0000000010204080I64,
	0x000000e000000000I64, 0x1010100000000000I64, 0x8040200000000000I64, 0x0204080000000000I64, 0x0000000f00000000I64, 0x0000000010101010I64, 0x0000000008040201I64, 0x0000000020408000I64,
	0x000000c000000000I64, 0x2020200000000000I64, 0x0080400000000000I64, 0x0408100000000000I64, 0x0000001f00000000I64, 0x0000000020202020I64, 0x0000000010080402I64, 0x0000000040800000I64,
	0x0000008000000000I64, 0x4040400000000000I64, 0x0000800000000000I64, 0x0810200000000000I64, 0x0000003f00000000I64, 0x0000000040404040I64, 0x0000000020100804I64, 0x0000000080000000I64,
	0x0000000000000000I64, 0x8080800000000000I64, 0x0000000000000000I64, 0x1020400000000000I64, 0x0000007f00000000I64, 0x0000000080808080I64, 0x0000000040201008I64, 0x0000000000000000I64,
	0x0000fe0000000000I64, 0x0101000000000000I64, 0x0402000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000101010101I64, 0x0000000000000000I64, 0x0000000204081020I64,
	0x0000fc0000000000I64, 0x0202000000000000I64, 0x0804000000000000I64, 0x0001000000000000I64, 0x0000010000000000I64, 0x0000000202020202I64, 0x0000000100000000I64, 0x0000000408102040I64,
	0x0000f80000000000I64, 0x0404000000000000I64, 0x1008000000000000I64, 0x0102000000000000I64, 0x0000030000000000I64, 0x0000000404040404I64, 0x0000000201000000I64, 0x0000000810204080I64,
	0x0000f00000000000I64, 0x0808000000000000I64, 0x2010000000000000I64, 0x0204000000000000I64, 0x0000070000000000I64, 0x0000000808080808I64, 0x0000000402010000I64, 0x0000001020408000I64,
	0x0000e00000000000I64, 0x1010000000000000I64, 0x4020000000000000I64, 0x0408000000000000I64, 0x00000f0000000000I64, 0x0000001010101010I64, 0x0000000804020100I64, 0x0000002040800000I64,
	0x0000c00000000000I64, 0x2020000000000000I64, 0x8040000000000000I64, 0x0810000000000000I64, 0x00001f0000000000I64, 0x0000002020202020I64, 0x0000001008040201I64, 0x0000004080000000I64,
	0x0000800000000000I64, 0x4040000000000000I64, 0x0080000000000000I64, 0x1020000000000000I64, 0x00003f0000000000I64, 0x0000004040404040I64, 0x0000002010080402I64, 0x0000008000000000I64,
	0x0000000000000000I64, 0x8080000000000000I64, 0x0000000000000000I64, 0x2040000000000000I64, 0x00007f0000000000I64, 0x0000008080808080I64, 0x0000004020100804I64, 0x0000000000000000I64,
	0x00fe000000000000I64, 0x0100000000000000I64, 0x0200000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000010101010101I64, 0x0000000000000000I64, 0x0000020408102040I64,
	0x00fc000000000000I64, 0x0200000000000000I64, 0x0400000000000000I64, 0x0100000000000000I64, 0x0001000000000000I64, 0x0000020202020202I64, 0x0000010000000000I64, 0x0000040810204080I64,
	0x00f8000000000000I64, 0x0400000000000000I64, 0x0800000000000000I64, 0x0200000000000000I64, 0x0003000000000000I64, 0x0000040404040404I64, 0x0000020100000000I64, 0x0000081020408000I64,
	0x00f0000000000000I64, 0x0800000000000000I64, 0x1000000000000000I64, 0x0400000000000000I64, 0x0007000000000000I64, 0x0000080808080808I64, 0x0000040201000000I64, 0x0000102040800000I64,
	0x00e0000000000000I64, 0x1000000000000000I64, 0x2000000000000000I64, 0x0800000000000000I64, 0x000f000000000000I64, 0x0000101010101010I64, 0x0000080402010000I64, 0x0000204080000000I64,
	0x00c0000000000000I64, 0x2000000000000000I64, 0x4000000000000000I64, 0x1000000000000000I64, 0x001f000000000000I64, 0x0000202020202020I64, 0x0000100804020100I64, 0x0000408000000000I64,
	0x0080000000000000I64, 0x4000000000000000I64, 0x8000000000000000I64, 0x2000000000000000I64, 0x003f000000000000I64, 0x0000404040404040I64, 0x0000201008040201I64, 0x0000800000000000I64,
	0x0000000000000000I64, 0x8000000000000000I64, 0x0000000000000000I64, 0x4000000000000000I64, 0x007f000000000000I64, 0x0000808080808080I64, 0x0000402010080402I64, 0x0000000000000000I64,
	0xfe00000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0001010101010101I64, 0x0000000000000000I64, 0x0002040810204080I64,
	0xfc00000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0100000000000000I64, 0x0002020202020202I64, 0x0001000000000000I64, 0x0004081020408000I64,
	0xf800000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0300000000000000I64, 0x0004040404040404I64, 0x0002010000000000I64, 0x0008102040800000I64,
	0xf000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0700000000000000I64, 0x0008080808080808I64, 0x0004020100000000I64, 0x0010204080000000I64,
	0xe000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0f00000000000000I64, 0x0010101010101010I64, 0x0008040201000000I64, 0x0020408000000000I64,
	0xc000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x1f00000000000000I64, 0x0020202020202020I64, 0x0010080402010000I64, 0x0040800000000000I64,
	0x8000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x3f00000000000000I64, 0x0040404040404040I64, 0x0020100804020100I64, 0x0080000000000000I64,
	0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x0000000000000000I64, 0x7f00000000000000I64, 0x0080808080808080I64, 0x0040201008040201I64, 0x0000000000000000I64,
};


#ifdef __AVX2__

CUDA_CALLABLE BitBoard Flips(const Position& pos, Field move) noexcept
{
	const int64x4 P(pos.Player());
	const int64x4 O(pos.Opponent());
	const int64x4 mask1(masks.data() + static_cast<uint64>(move) * 8 + 0);
	const int64x4 mask2(masks.data() + static_cast<uint64>(move) * 8 + 4);

	int64x4 outflank1 = andnot(O, mask1);
	// look for non-opponent LS1B
	outflank1 &= -outflank1;
	outflank1 &= P;
	outflank1 += ~cmpeq(outflank1, int64x4{});
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

#else

CUDA_CALLABLE BitBoard Flips(const Position& pos, Field move) noexcept
{
	const uint64 P = pos.Player();
	const uint64 O = pos.Opponent();
	const uint64 m = static_cast<uint64>(move);

	uint64 outflank0 = ~O & masks[m * 8 + 0];
	uint64 outflank1 = ~O & masks[m * 8 + 1];
	uint64 outflank2 = ~O & masks[m * 8 + 2];
	uint64 outflank3 = ~O & masks[m * 8 + 3];

	// look for non-opponent LS1B
	outflank0 &= -outflank0;
	outflank1 &= -outflank1;
	outflank2 &= -outflank2;
	outflank3 &= -outflank3;

	outflank0 &= P;
	outflank1 &= P;
	outflank2 &= P;
	outflank3 &= P;

	outflank0 -= static_cast<uint64_t>(outflank0 != 0);
	outflank1 -= static_cast<uint64_t>(outflank1 != 0);
	outflank2 -= static_cast<uint64_t>(outflank2 != 0);
	outflank3 -= static_cast<uint64_t>(outflank3 != 0);

	uint64 flip = outflank0 & masks[m * 8 + 0]
				| outflank1 & masks[m * 8 + 1]
				| outflank2 & masks[m * 8 + 2]
				| outflank3 & masks[m * 8 + 3];

	// isolate non-opponent MS1B by clearing lower bits
	uint64 outflank4 = (P & masks[m * 8 + 4]) << 1;
	uint64 outflank5 = (P & masks[m * 8 + 5]) << 8;
	uint64 outflank6 = (P & masks[m * 8 + 6]) << 9;
	uint64 outflank7 = (P & masks[m * 8 + 7]) << 7;

	uint64 eraser4 = ~O & masks[m * 8 + 4];
	uint64 eraser5 = ~O & masks[m * 8 + 5];
	uint64 eraser6 = ~O & masks[m * 8 + 6];
	uint64 eraser7 = ~O & masks[m * 8 + 7];

	eraser4 |= eraser4 >> 1;
	eraser5 |= eraser5 >> 8;
	eraser6 |= eraser6 >> 9;
	eraser7 |= eraser7 >> 7;

	eraser4 |= eraser4 >> 2;
	eraser5 |= eraser5 >> 16;
	eraser6 |= eraser6 >> 18;
	eraser7 |= eraser7 >> 14;

	eraser4 |= eraser4 >> 4;
	eraser5 |= eraser5 >> 32;
	eraser6 |= eraser6 >> 36;
	eraser7 |= eraser7 >> 28;

	// set mask bits higher than outflank
	return flip | -(~eraser4 & outflank4) & masks[m * 8 + 4]
				| -(~eraser5 & outflank5) & masks[m * 8 + 5]
				| -(~eraser6 & outflank6) & masks[m * 8 + 6]
				| -(~eraser7 & outflank7) & masks[m * 8 + 7];
}
#endif