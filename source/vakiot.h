#pragma once
#include <array>
#include <cstdint>
#include "Ruutu.h"

constexpr int kSiirtoVaihtoTauluKoko = 0x7ffffff;
constexpr int kMaxSiirtoMaara = 218;
constexpr int kLautaKoko = 8;
constexpr int kEiKaksoisaskel = -10;
constexpr int kValkoistenSotilaidenRivi = 1;
constexpr int kMustienSotilaidenRivi = 6;
extern double kEtsimisAika;

enum class Vari {
	kValkea,
	kMusta
};

enum class Laji {
	Kuningas,
	Daami,
	Torni,
	Lahetti,
	Ratsu,
	Sotilas
};

enum class Tyyppi {
	VT, VR, VL, VD, VK, VS,
	MT, MR, ML, MD, MK, MS, 
	EiKorotus
};

const std::array<Ruutu, 8> kRatsuMahdollisetSiirrot {
	Ruutu(2,-1),
	Ruutu(2, 1),
	Ruutu(1, 2),
	Ruutu(-1, 2),
	Ruutu(-2, 1),
	Ruutu(-2, -1),
	Ruutu(-1, -2),
	Ruutu(1, -2)
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaDaamiRuutuTaulu{
	-20,-10,-10, -5, -5,-10,-10,-20,	// 1
	-10,  0,  0,  0,  0,  0,  0,-10,	// 2
	-10,  0,  5,  5,  5,  5,  0,-10,	// 3
	 -5,  0,  5,  5,  5,  5,  0, -5,	// 4
	 0,  0,  5,  5,  5,  5,  0, -5,		// 5
	-10,  5,  5,  5,  5,  5,  0,-10,	// 6
	-10,  0,  5,  0,  0,  0,  0,-10,	// 7
	-20,-10,-10, -5, -5,-10,-10,-20		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaDaamiRuutuTaulu{
	-20,-10,-10, -5, -5,-10,-10,-20,	// 1
	-10,  0,  5,  0,  0,  0,  0,-10,	// 2
	-10,  5,  5,  5,  5,  5,  0,-10,	// 3
	  0,  0,  5,  5,  5,  5,  0, -5,	// 4
	 -5,  0,  5,  5,  5,  5,  0, -5,	// 5
	-10,  0,  5,  5,  5,  5,  0,-10,	// 6
	-10,  0,  0,  0,  0,  0,  0,-10,	// 7
	-20,-10,-10, -5, -5,-10,-10,-20		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaTorniRuutuTaulu{
	0,  0,  0,  0,  0,  0,  0,  0,	// 1
    5, 10, 10, 10, 10, 10, 10,  5,	// 2
   -5,  0,  0,  0,  0,  0,  0, -5,	// 3
   -5,  0,  0,  0,  0,  0,  0, -5,	// 4
   -5,  0,  0,  0,  0,  0,  0, -5,	// 5
   -5,  0,  0,  0,  0,  0,  0, -5,	// 6
   -5,  0,  0,  0,  0,  0,  0, -5,	// 7
    0,  0,  0,  5,  5,  0,  0,  0	// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaTorniRuutuTaulu{
	 0,  0,  0,  5,  5,  0,  0,  0,	// 1
	-5,  0,  0,  0,  0,  0,  0, -5,	// 2
	-5,  0,  0,  0,  0,  0,  0, -5,	// 3
	-5,  0,  0,  0,  0,  0,  0, -5,	// 4
	-5,  0,  0,  0,  0,  0,  0, -5,	// 5
	-5,  0,  0,  0,  0,  0,  0, -5,	// 6
	 5, 10, 10, 10, 10, 10, 10,  5,	// 7
	 0,  0,  0,  0,  0,  0,  0,  0	// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaSotilasRuutuTaulu {
	0, 0, 0, 0, 0, 0, 0, 0,				// 1
	5, 10, 10, -20, -20, 10, 10, 5,		// 2
	5, -5, -10, 0, 0, -10, -5, 5,		// 3
	0, 0, 0, 20, 20, 0, 0, 0,			// 4
	5, 5, 10, 25, 25, 10, 5, 5,			// 5
	10, 10, 20, 30, 30, 20, 10, 10,		// 6
	50, 50, 50, 50, 50, 50, 50, 50,		// 7
	0, 0, 0, 0, 0, 0, 0, 0				// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaSotilasRuutuTaulu {
	0, 0, 0, 0, 0, 0, 0, 0,				// 1
	50, 50, 50, 50, 50, 50, 50, 50,		// 2
	10, 10, 20, 30, 30, 20, 10, 10,		// 3
	5, 5, 10, 25, 25, 10, 5, 5,			// 4
	0, 0, 0, 20, 20, 0, 0, 0,			// 5
	5, -5, -10, 0, 0, -10, -5, 5,		// 6
	5, 10, 10, -20, -20, 10, 10, 5,		// 7
	0, 0, 0, 0, 0, 0, 0, 0				// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaRatsuRuutuTaulu {
	-50,-40,-30,-30,-30,-30,-40,-50,	// 1
	-40,-20,  0,  0,  0,  0,-20,-40,	// 2
	-30,  0, 10, 15, 15, 10,  0,-30,	// 3
	-30,  5, 15, 20, 20, 15,  5,-30,	// 4
	-30,  0, 15, 20, 20, 15,  0,-30,	// 5
	-30,  5, 10, 15, 15, 10,  5,-30,	// 6
	-40,-20,  0,  5,  5,  0,-20,-40,	// 7
	-50,-40,-30,-30,-30,-30,-40,-50		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaRatsuRuutuTaulu{
	-50,-40,-30,-30,-30,-30,-40,-50,	// 1
	-40,-20,  0,  5,  5,  0,-20,-40,	// 2
	-30,  5, 10, 15, 15, 10,  5,-30,	// 3
	-30,  0, 15, 20, 20, 15,  0,-30,	// 4
	-30,  5, 15, 20, 20, 15,  5,-30,	// 5
	-30,  0, 10, 15, 15, 10,  0,-30,	// 6
	-40,-20,  0,  0,  0,  0,-20,-40,	// 7
	-50,-40,-30,-30,-30,-30,-40,-50		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaLahettiRuutuTaulu{
	-20,-10,-10,-10,-10,-10,-10,-20,	// 1
	-10,  0,  0,  0,  0,  0,  0,-10,	// 2
	-10,  0,  5, 10, 10,  5,  0,-10,	// 3
	-10,  5,  5, 10, 10,  5,  5,-10,	// 4
	-10,  0, 10, 10, 10, 10,  0,-10,	// 5
	-10, 10, 10, 10, 10, 10, 10,-10,	// 6
	-10,  5,  0,  0,  0,  0,  5,-10,	// 7
	-20,-10,-10,-10,-10,-10,-10,-20		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaLahettiRuutuTaulu{
	-20,-10,-10,-10,-10,-10,-10,-20,	// 1
	-10,  5,  0,  0,  0,  0,  5,-10,	// 2
	-10, 10, 10, 10, 10, 10, 10,-10,	// 3
	-10,  0, 10, 10, 10, 10,  0,-10,	// 4
	-10,  5,  5, 10, 10,  5,  5,-10,	// 5
	-10,  0,  5, 10, 10,  5,  0,-10,	// 6
	-10,  0,  0,  0,  0,  0,  0,-10,	// 7
	-20,-10,-10,-10,-10,-10,-10,-20		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaKuningasKeskiRuutuTaulu{
	-30,-40,-40,-50,-50,-40,-40,-30,	// 1
	-30,-40,-40,-50,-50,-40,-40,-30,	// 2
	-30,-40,-40,-50,-50,-40,-40,-30,	// 3
	-30,-40,-40,-50,-50,-40,-40,-30,	// 4
	-20,-30,-30,-40,-40,-30,-30,-20,	// 5
	-10,-20,-20,-20,-20,-20,-20,-10,	// 6
	 20, 20,  0,  0,  0,  0, 20, 20,	// 7
	 20, 30, 10,  0,  0, 10, 30, 20		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaKuningasKeskiRuutuTaulu{
	20, 30, 10,  0,  0, 10, 30, 20,		// 1
	20, 20,  0,  0,  0,  0, 20, 20,		// 2
	-10,-20,-20,-20,-20,-20,-20,-10,	// 3
	-20,-30,-30,-40,-40,-30,-30,-20,	// 4
	-30,-40,-40,-50,-50,-40,-40,-30,	// 5
	-30,-40,-40,-50,-50,-40,-40,-30,	// 6'
	-30,-40,-40,-50,-50,-40,-40,-30,	// 7
	-30,-40,-40,-50,-50,-40,-40,-30		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kMustaKuningasLoppuRuutuTaulu{
	-50,-40,-30,-20,-20,-30,-40,-50,	// 1
	-30,-20,-10,  0,  0,-10,-20,-30,	// 2
	 30,-10, 20, 30, 30, 20,-10,-30,	// 3
	-30,-10, 30, 40, 40, 30,-10,-30,	// 4
	-30,-10, 30, 40, 40, 30,-10,-30,	// 5
	-30,-10, 20, 30, 30, 20,-10,-30,	// 6
	-30,-30,  0,  0,  0,  0,-30,-30,	// 7
	-50,-30,-30,-30,-30,-30,-30,-50		// 8
};

const std::array<const std::array<int, kLautaKoko>, kLautaKoko> kValkeaKuningasLoppuRuutuTaulu{
	-50,-30,-30,-30,-30,-30,-30,-50,	// 1
	-30,-30,  0,  0,  0,  0,-30,-30,	// 2
	-30,-10, 20, 30, 30, 20,-10,-30,	// 3
	-30,-10, 30, 40, 40, 30,-10,-30,	// 4
	-30,-10, 30, 40, 40, 30,-10,-30,	// 5
	 30,-10, 20, 30, 30, 20,-10,-30,	// 6
	-30,-20,-10,  0,  0,-10,-20,-30,	// 7
	-50,-40,-30,-20,-20,-30,-40,-50		// 8
};

const std::array<double, 4> kRatsuAsemaTyyppiKerroin{
	1.1, 1.1, 0.9, 0.85
};

const std::array<double, 4> kLahettiAsemaTyyppiKerroin{
	1.0, 1.05, 1.15, 1.2
};

const std::array<double, 4> kTorniAsemaTyyppiKerroin{
	0.85, 0.9, 1.1, 1.1
};

const std::array<double, 4> kDaamiAsemaTyyppiKerroin{
	0.9, 0.95, 1.2, 1.3
};

const std::array<double, 4> kSotilasArvoKerroin{
	1.0, 1.05, 1.1, 1.15
};

const std::array<double, kLautaKoko> kEtenemisArvo{
	-1.5, 1.5, 3, 4.5, 6, 7.5, 6, 3
};

const std::array<double, kLautaKoko> kSarakeArvo{
	0, 1.5, 3, 5, 5, 3, 1.5, 0
};

const std::array<const std::array<double, kLautaKoko>, kLautaKoko> kKeskustanHallintaArvo{
	2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5,	// 1
	2.5,  5,  5,  5,  5,  5,  5,2.5,	// 2
	2.5,  5,7.5,7.5,7.5,7.5,  5,2.5,	// 3
	2.5,  5,7.5, 10, 10,7.5,  5,2.5,	// 4
	2.5,  5,7.5, 10, 10,7.5,  5,2.5,	// 5
	2.5,  5,7.5,7.5,7.5,7.5,  5,2.5,	// 6
	2.5,  5,  5,  5,  5,  5,  5,2.5,	// 7
	2.5,2.5,2.5,2.5,2.5,2.5,2.5,2.5		// 8
};