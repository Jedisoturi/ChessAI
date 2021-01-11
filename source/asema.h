#pragma once

#include <list>
#include <string>
#include "vakiot.h"
#include "siirto.h"
#include <vector>
#include <iostream>
#include <cstdint>
#include <array>
#include <limits>
#include <random>
#include <functional>
#include <unordered_map>
#include <chrono>

#define tt
#define tt2
// 178492 (norm)
// 
// 1914222665402444309 ei tt (10 asema, 6 syvyys)
// 1914222665402444309 tt (10 asema, 6 syvyys)

// Ns. "forward eclaration". Nyt Asema-luokassa voidaa esitell‰ Nappula-osoittimia ilman,
// ett‰ nappula.h -tiedostoa t‰ytyy includoida.
class Nappula;

struct MateriaaliArvot {
	double materiaali = 0;
	int valkea_torni_siirrot = 0;
	int musta_torni_siirrot = 0;
	int valkea_lahetti_siirrot = 0;
	int musta_lahetti_siirrot = 0;
	int valkea_daami_siirrot = 0;
	int musta_daami_siirrot = 0;
};

class MinMaxPaluu
{
public:
	int _evaluointi;
	Siirto _parasSiirto;
	bool _aika_loppu = false;
};

struct SiirtovaihtoArvot {
	uint64_t _hash;
	int _evaluointi;
	bool _hyodyllinen = true;
	uint8_t _ika = 0;
	uint8_t _syvyys = 0;
	Siirto _paras_siirto;
};

// Asema sis‰lt‰‰ kaiken tarvittavan informaation pelitilanteen kuvaamiseksi
// (nappuloiden sijainti, siirtovuoro, linnoitusoikeudet jne.).
class Asema
{
public:
	// Pelilauta sis‰lt‰‰ osoittimet kunkin ruudun nappula-olioon (nullptr/NULL/0 jos ruutu on tyhj‰).
	// Public-m‰‰reell‰, koska t‰t‰ k‰ytet‰‰n paljon muualla.
	Nappula* _lauta[8][8];

	// Nappula-oliot. Huomaa, ett‰ samaa nappulaa voidaan k‰ytt‰‰ useissa eri ruuduissa.
	// M‰‰ritelty static-m‰‰reell‰, joten nappulat ovat kaikkien lauta-olioiden "yhteisk‰ytˆss‰"
	// (suorituskyvyn vuoksi).
	static Nappula* vk, * vd, * vt, * vl, * vr, * vs;	// Valkeat nappulat.
	static Nappula* mk, * md, * mt, * ml, * mr, * ms;	// Mustat nappulat.

	static std::array<uint64_t, 781> _zobrist_satunnais_luvut;

	// Ohestalyˆnti‰ varten (kEiKaksoisaskel = sotilaan kaksoisaskelta ei tapahtunut edellisell‰ siirrolla).
	int _kaksoisaskel_sarakkeella = kEiKaksoisaskel;

	Asema(); // Asettaa alkuaseman.

	void PaivitaAsema(const Siirto* siirto);

	void AnnaLaillisetSiirrot(std::vector<Siirto>& lista, Vari vari) const;
	//void AnnaMahdollisetSiirrot(std::vector<Siirto>& mahdolliset_siirrot, Vari vari) const;

	MinMaxPaluu AlphaBeta(int alpha, int beta, int syvyys_jaljella, SiirtovaihtoArvot** siirtovaihto_taulu, std::chrono::high_resolution_clock::time_point alku);

	uint64_t AnnaZorbaLuku() const;

	Vari siirtovuoro() const { return _siirtovuoro; }
	void SetSiirtovuoro(Vari vari) { _siirtovuoro = vari; }
	bool onkoValkeaKuningasLiikkunut() const { return _onko_valkea_kuningas_liikkunut; }
	bool onkoMustaKuningasLiikkunut() const { return _onko_musta_kuningas_liikkunut; }
	bool onkoValkeaDTliikkunut() const { return _onko_valkea_dt_liikkunut; }
	bool onkoValkeaKTliikkunut() const { return _onko_valkea_kt_liikkunut; }
	bool onkoMustaDTliikkunut() const { return _onko_musta_dt_liikkunut; }
	bool onkoMustaKTliikkunut() const { return _onko_musta_kt_liikkunut; }

	bool OnkoKuningasUhattu(const Vari vari) const;

private:
	Vari _siirtovuoro;
	bool _onko_valkea_kuningas_liikkunut = false;
	bool _onko_musta_kuningas_liikkunut = false;
	bool _onko_valkea_dt_liikkunut = false;
	bool _onko_valkea_kt_liikkunut = false;
	bool _onko_musta_dt_liikkunut = false;
	bool _onko_musta_kt_liikkunut = false;
	Ruutu _valkea_kuningas_ruutu;
	Ruutu _musta_kuningas_ruutu;

	void TeeLyhytLinna();
	void TeePitkaLinna();
	void TeeSiirto(const Siirto* siirto);
	//void AnnaMahdollisetLinnoitusSiirrot(std::vector<Siirto>& mahdolliset_siirrot, const Vari vari) const;
	//void AnnaMahdollisetNormaaliSiirrot(std::vector<Siirto>& mahdolliset_siirrot, const Vari vari) const;
	
	

	Nappula* TyyppiNappulaksi(Tyyppi tyyppi);

	int EvaluoiVanha() const;
	int EvaluoiUusi(const std::vector<Siirto> siirrot) const;
};

void LuoSatunnaisLuvut();

SiirtovaihtoArvot* AnnaSiirtovaihtoArvot(const uint64_t zobrist_luku, bool& loytyi, SiirtovaihtoArvot** siirtovaihto_taulu);

void SyotaSiirtovaihtoArvot(const uint64_t zobrist_luku, SiirtovaihtoArvot* arvot, SiirtovaihtoArvot** siirtovaihto_taulu);
