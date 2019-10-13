#include "Main.h"
#include "Core/Machine.h"
#include "Core/BitBoard.h"
#include <array>
#include <sstream>

static const std::array<std::wstring, 65> field_names = {
	L"A1", L"B1", L"C1", L"D1", L"E1", L"F1", L"G1", L"H1",
	L"A2", L"B2", L"C2", L"D2", L"E2", L"F2", L"G2", L"H2",
	L"A3", L"B3", L"C3", L"D3", L"E3", L"F3", L"G3", L"H3",
	L"A4", L"B4", L"C4", L"D4", L"E4", L"F4", L"G4", L"H4",
	L"A5", L"B5", L"C5", L"D5", L"E5", L"F5", L"G5", L"H5",
	L"A6", L"B6", L"C6", L"D6", L"E6", L"F6", L"G6", L"H6",
	L"A7", L"B7", L"C7", L"D7", L"E7", L"F7", L"G7", L"H7",
	L"A8", L"B8", L"C8", L"D8", L"E8", L"F8", L"G8", L"H8", L"--"
};

std::wstring to_wstring(Field field)
{
	return field_names[static_cast<uint8_t>(field)];
}

Field ParseField(const std::wstring& str)
{
	const auto it = std::find(field_names.begin(), field_names.end(), str);
	const auto index = std::distance(field_names.begin(), it);
	return static_cast<Field>(index);
}

std::wstring SingleLine(Position pos)
{
	std::wstring puzzle = L"---------------------------------------------------------------- X";
	for (int i = 0; i < 64; i++)
	{
		const bool P_bit = pos.GetP()[63ui64 - i];
		const bool O_bit = pos.GetO()[63ui64 - i];

		if (P_bit)
			puzzle[i] = L'X';
		else if (O_bit)
			puzzle[i] = L'O';
	}
	return puzzle;
}

Board ParseBoard_SingleLine(const std::wstring& str)
{
	BitBoard P{ 0 }, O{ 0 };

	for (int i = 0; i < 64; i++)
	{
		P[63 - i] = (str[i] == L'X');
		O[63 - i] = (str[i] == L'O');
	}

	if (str[65] == L'X')
		return { P, O };
	if (str[65] == L'O')
		return { O, P };
	throw std::runtime_error("Unexpected input");
}

std::wstring MultiLine(Position pos)
{
	const Moves moves = PossibleMoves(pos);
	std::wstring puzzle =
		L"  H G F E D C B A  \n"
		L"8 - - - - - - - - 8\n"
		L"7 - - - - - - - - 7\n"
		L"6 - - - - - - - - 6\n"
		L"5 - - - - - - - - 5\n"
		L"4 - - - - - - - - 4\n"
		L"3 - - - - - - - - 3\n"
		L"2 - - - - - - - - 2\n"
		L"1 - - - - - - - - 1\n"
		L"  H G F E D C B A  ";

	for (unsigned int i = 0; i < 64; i++)
	{
		auto& field = puzzle[22 + 2 * i + 4 * (i / 8)];

		if (pos.GetP()[63 - i])
			field = 'X';
		else if (pos.GetO()[63 - i])
			field = 'O';
		else if (moves.contains(static_cast<Field>(63 - i)))
			field = '+';
	}
	return puzzle;
}

std::wstring SignedInt(const Score score)
{
	const std::wstring Sign = (score >= 0) ? L"+" : L"-";
	const std::wstring Number = std::to_wstring(std::abs(score));
	return Sign + Number;
}

std::wstring DoubleDigitSignedInt(const Score score)
{
	const std::wstring Sign = (score >= 0) ? L"+" : L"-";
	const std::wstring FillingZero = (std::abs(score) < 10) ? L"0" : L"";
	const std::wstring Number = std::to_wstring(std::abs(score));
	return Sign + FillingZero + Number;
}

std::size_t ParseBytes(const std::wstring& bytes)
{
	if (bytes.find(L"EB") != std::wstring::npos) return std::stoll(bytes) * 1024 * 1024 * 1024 * 1024 * 1024 * 1024;
	if (bytes.find(L"PB") != std::wstring::npos) return std::stoll(bytes) * 1024 * 1024 * 1024 * 1024 * 1024;
	if (bytes.find(L"TB") != std::wstring::npos) return std::stoll(bytes) * 1024 * 1024 * 1024 * 1024;
	if (bytes.find(L"GB") != std::wstring::npos) return std::stoll(bytes) * 1024 * 1024 * 1024;
	if (bytes.find(L"MB") != std::wstring::npos) return std::stoll(bytes) * 1024 * 1024;
	if (bytes.find(L"kB") != std::wstring::npos) return std::stoll(bytes) * 1024;
	if (bytes.find(L'B') != std::wstring::npos) return std::stoll(bytes);
	return 0;
}

wchar_t MetricPrefix(int magnitude_base_1000)
{
	switch (magnitude_base_1000)
	{
		case -8: return L'y';
		case -7: return L'z';
		case -6: return L'a';
		case -5: return L'f';
		case -4: return L'p';
		case -3: return L'n';
		case -2: return L'u';
		case -1: return L'm';
		case  0: return L' ';
		case +1: return L'k';
		case +2: return L'M';
		case +3: return L'G';
		case +4: return L'T';
		case +5: return L'P';
		case +6: return L'E';
		case +7: return L'Z';
		case +8: return L'Y';
		default: throw;
	}
}

// Format: "ddd:hh:mm:ss.ccc"
std::wstring time_format(const std::chrono::milliseconds duration)
{
	using namespace std;
	using days_t = chrono::duration<int, ratio<24 * 3600>>;

	const auto milli_seconds = duration.count() % 1000;
	const auto seconds = chrono::duration_cast<chrono::seconds>(duration).count() % 60;
	const auto minutes = chrono::duration_cast<chrono::minutes>(duration).count() % 60;
	const auto hours = chrono::duration_cast<chrono::hours>(duration).count() % 24;
	const auto days = chrono::duration_cast<days_t>(duration).count();

	wostringstream oss;
	oss << setfill(L' ');

	if (days)
		oss << setw(3) << days << L':'<< setfill(L'0');
	else
		oss << L"    ";

	if (days || hours)
		oss << setw(2) << hours << L':'<< setfill(L'0');
	else
		oss << L"   ";

	if (days || hours || minutes)
		oss << setw(2) << minutes << L':'<< setfill(L'0');
	else
		oss << L"   ";

	oss << setw(2) << seconds << L'.' << setfill(L'0') << setw(3) << milli_seconds;

	return oss.str();
}

std::wstring short_time_format(std::chrono::duration<double> duration)
{
	using namespace std;

	const auto seconds = duration.count();
	const int magnitude_base_1000 = static_cast<int>(floor(log10(abs(seconds)) / 3));
	const double normalized = seconds * pow(1000.0, -magnitude_base_1000);

	wostringstream oss;
	oss.precision(2 - floor(log10(abs(normalized))));
	oss << fixed << setw(4) << setfill(L' ') << normalized << MetricPrefix(magnitude_base_1000) << L's';
	return oss.str();
}
