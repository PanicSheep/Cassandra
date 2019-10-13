#include "BitBoard.h"
#include "Machine.h"

std::size_t BitBoard::PopCount() const noexcept
{
	return ::PopCount(b);
}

void BitBoard::RemoveLSB() noexcept
{
	::RemoveLSB(b);
}

Field BitBoard::BitScanLSB() const noexcept
{
	return static_cast<Field>(::BitScanLSB(b));
}

void BitBoard::FlipCodiagonal() noexcept
{
	// 9 x XOR, 6 x SHIFT, 3 x AND
	// 18 OPs

	// # # # # # # # /
	// # # # # # # / #
	// # # # # # / # #
	// # # # # / # # #
	// # # # / # # # #
	// # # / # # # # #
	// # / # # # # # #
	// / # # # # # # #<-LSB
	uint64_t
	t  =  b ^ (b << 36);
	b ^= (t ^ (b >> 36)) & 0xF0F0F0F00F0F0F0Fui64;
	t  = (b ^ (b << 18)) & 0xCCCC0000CCCC0000ui64;
	b ^=  t ^ (t >> 18);
	t  = (b ^ (b <<  9)) & 0xAA00AA00AA00AA00ui64;
	b ^=  t ^ (t >>  9);
}

void BitBoard::FlipDiagonal() noexcept
{
	// 9 x XOR, 6 x SHIFT, 3 x AND
	// 18 OPs

	// \ # # # # # # #
	// # \ # # # # # #
	// # # \ # # # # #
	// # # # \ # # # #
	// # # # # \ # # #
	// # # # # # \ # #
	// # # # # # # \ #
	// # # # # # # # \<-LSB
	uint64_t 
	t  = (b ^ (b >>  7)) & 0x00AA00AA00AA00AAui64;
	b ^=  t ^ (t <<  7);
	t  = (b ^ (b >> 14)) & 0x0000CCCC0000CCCCui64;
	b ^=  t ^ (t << 14);
	t  = (b ^ (b >> 28)) & 0x00000000F0F0F0F0ui64;
	b ^=  t ^ (t << 28);
}

void BitBoard::FlipHorizontal() noexcept
{
	// 6 x SHIFT, 6 x AND, 3 x OR
	// 15 OPs

	// # # # #|# # # #
	// # # # #|# # # #
	// # # # #|# # # #
	// # # # #|# # # #
	// # # # #|# # # #
	// # # # #|# # # #
	// # # # #|# # # #
	// # # # #|# # # #<-LSB
	b = ((b >> 1) & 0x5555555555555555ui64) | ((b << 1) & 0xAAAAAAAAAAAAAAAAui64);
	b = ((b >> 2) & 0x3333333333333333ui64) | ((b << 2) & 0xCCCCCCCCCCCCCCCCui64);
	b = ((b >> 4) & 0x0F0F0F0F0F0F0F0Fui64) | ((b << 4) & 0xF0F0F0F0F0F0F0F0ui64);
}

void BitBoard::FlipVertical() noexcept
{
	// 1 x BSwap
	// 1 OPs

	// # # # # # # # #
	// # # # # # # # #
	// # # # # # # # #
	// # # # # # # # #
	// ---------------
	// # # # # # # # #
	// # # # # # # # #
	// # # # # # # # #
	// # # # # # # # #<-LSB
	b = BSwap(b);
	//b = ((b >>  8) & 0x00FF00FF00FF00FFui64) | ((b <<  8) & 0xFF00FF00FF00FF00ui64);
	//b = ((b >> 16) & 0x0000FFFF0000FFFFui64) | ((b << 16) & 0xFFFF0000FFFF0000ui64);
	//b = ((b >> 32) & 0x00000000FFFFFFFFui64) | ((b << 32) & 0xFFFFFFFF00000000ui64);
	//return b;
}

BitBoard FlipCodiagonal(BitBoard bb) noexcept
{
	bb.FlipCodiagonal();
	return bb;
}

BitBoard FlipDiagonal(BitBoard bb) noexcept
{
	bb.FlipDiagonal();
	return bb;
}

BitBoard FlipHorizontal(BitBoard bb) noexcept
{
	bb.FlipHorizontal();
	return bb;
}

BitBoard FlipVertical(BitBoard bb) noexcept
{
	bb.FlipVertical();
	return bb;
}