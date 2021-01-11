#include <iostream>
#include "asema.h"
#include "nappula.h"

std::array<uint64_t, 781> Asema::_zobrist_satunnais_luvut;

#pragma region Nappula Oliot
// Luo kaikkien nappula tyyppien oliot
Nappula* Asema::vk = new Kuningas(L"\u2654", Vari::kValkea, Tyyppi::VK, Laji::Kuningas);
Nappula* Asema::vd = new Daami(L"\u2655", Vari::kValkea, Tyyppi::VD, Laji::Daami);
Nappula* Asema::vt = new Torni(L"\u2656", Vari::kValkea, Tyyppi::VT, Laji::Torni);
Nappula* Asema::vl = new Lahetti(L"\u2657", Vari::kValkea, Tyyppi::VL, Laji::Lahetti);
Nappula* Asema::vr = new Ratsu(L"\u2658", Vari::kValkea, Tyyppi::VR, Laji::Ratsu);
Nappula* Asema::vs = new Sotilas(L"\u2659", Vari::kValkea, Tyyppi::VS, Laji::Sotilas);

Nappula* Asema::mk = new Kuningas(L"\u265A", Vari::kMusta, Tyyppi::MK, Laji::Kuningas);
Nappula* Asema::md = new Daami(L"\u265B", Vari::kMusta, Tyyppi::MD, Laji::Daami);
Nappula* Asema::mt = new Torni(L"\u265C", Vari::kMusta, Tyyppi::MT, Laji::Torni);
Nappula* Asema::ml = new Lahetti(L"\u265D", Vari::kMusta, Tyyppi::ML, Laji::Lahetti);
Nappula* Asema::mr = new Ratsu(L"\u265E", Vari::kMusta, Tyyppi::MR, Laji::Ratsu);
Nappula* Asema::ms = new Sotilas(L"\u265F", Vari::kMusta, Tyyppi::MS, Laji::Sotilas);
#pragma endregion

#pragma region Konstruktorit
// Luo asema, jossa nappulot ovat niiden alkuasemissa
Asema::Asema() {
	// Ensin alustetaan kaikki laudan ruudut nullpointterilla, 
	// koska muuten tyhjissä ruuduissa satunnaista tauhkaa
	for (int rivi = 0; rivi < kLautaKoko; ++rivi) {
		for (int sarake = 0; sarake < kLautaKoko; ++sarake) {
			_lauta[rivi][sarake] = nullptr;
		}
	}

	// Valkoisten sotilaiden alustus
	for (int sarake = 0; sarake < kLautaKoko; ++sarake) {
		_lauta[kValkoistenSotilaidenRivi][sarake] = vs;
	}

	// Mustien sotilaiden alustus
	for (int sarake = 0; sarake < kLautaKoko; ++sarake) {
		_lauta[kMustienSotilaidenRivi][sarake] = ms;
	}

	// Alusta valkoisen muut nappulat
	_lauta[0][0] = vt;
	_lauta[0][1] = vr;
	_lauta[0][2] = vl;
	_lauta[0][3] = vd;
	_lauta[0][4] = vk;
	_lauta[0][5] = vl;
	_lauta[0][6] = vr;
	_lauta[0][7] = vt;

	// Alusta mustien muut nappulat
	_lauta[kLautaKoko - 1][0] = mt;
	_lauta[kLautaKoko - 1][1] = mr;
	_lauta[kLautaKoko - 1][2] = ml;
	_lauta[kLautaKoko - 1][3] = md;
	_lauta[kLautaKoko - 1][4] = mk;
	_lauta[kLautaKoko - 1][5] = ml;
	_lauta[kLautaKoko - 1][6] = mr;
	_lauta[kLautaKoko - 1][7] = mt;

	// Alusta kuninkaiden sijainti
	_valkea_kuningas_ruutu = Ruutu(0, 4);
	_musta_kuningas_ruutu = Ruutu(7, 4);

#pragma region testit
	//Null move check
	//_lauta[0][0] = nullptr;

	// Tornitus testi
	/*_lauta[1][6] = vl;
	_lauta[6][1] = nullptr;
	_lauta[7][1] = nullptr;
	_lauta[7][2] = nullptr;
	_lauta[7][3] = nullptr;*/
#pragma endregion

	// Valkoinen aloittaa
	_siirtovuoro = Vari::kValkea;
}
#pragma endregion

#pragma region Paivita Asema
// Päivitä asema siirron perusteella
void Asema::PaivitaAsema(const Siirto* siirto) {
	// Nollaa kaksoisaskel sarake
	_kaksoisaskel_sarakkeella = kEiKaksoisaskel;

	// Tee siirto
	if (siirto->lyhytLinna()) {
		TeeLyhytLinna();
	}
	else if (siirto->pitkaLinna()) {
		TeePitkaLinna();
	}
	else {
		// Normaali siirto (ei linnoitus)
		TeeSiirto(siirto);
	}

	// Vaihda siirtovuoro
	_siirtovuoro = _siirtovuoro == Vari::kMusta ? Vari::kValkea : Vari::kMusta;
}

// Tekee lyhyen linnoituksen
void Asema::TeeLyhytLinna() {
	if (_siirtovuoro == Vari::kValkea) {
		_lauta[0][4] = nullptr;  // Kuningas
		_lauta[0][7] = nullptr;  // Torni
		_lauta[0][6] = vk;
		_lauta[0][5] = vt;

		_onko_valkea_kuningas_liikkunut = true;
		_onko_valkea_kt_liikkunut = true;

		_valkea_kuningas_ruutu = Ruutu(0, 6);
	}
	else {
		_lauta[7][4] = nullptr;  // Kuningas
		_lauta[7][7] = nullptr;  // Torni
		_lauta[7][6] = mk;
		_lauta[7][5] = mt;

		_onko_musta_kuningas_liikkunut = true;
		_onko_musta_kt_liikkunut = true;

		_musta_kuningas_ruutu = Ruutu(7, 6);
	}
}

// Tekee pitkän linnoituksen
void Asema::TeePitkaLinna() {
	if (_siirtovuoro == Vari::kValkea) {
		_lauta[0][4] = nullptr;  // Kuningas
		_lauta[0][0] = nullptr;  // Torni
		_lauta[0][2] = vk;
		_lauta[0][3] = vt;

		_onko_valkea_kuningas_liikkunut = true;
		_onko_valkea_dt_liikkunut = true;

		_valkea_kuningas_ruutu = Ruutu(0, 2);
	}
	else {
		_lauta[7][4] = nullptr;  // Kuningas
		_lauta[7][0] = nullptr;  // Torni
		_lauta[7][2] = mk;
		_lauta[7][3] = mt;

		_onko_musta_kuningas_liikkunut = true;
		_onko_musta_dt_liikkunut = true;

		_musta_kuningas_ruutu = Ruutu(7, 2);
	}
}

// Tekee muun kuin linnoitus siirron
void Asema::TeeSiirto(const Siirto* siirto) {
	Ruutu alku_ruutu = siirto->alkuRuutu();
	Ruutu loppu_ruutu = siirto->loppuRuutu();
	Nappula* nappula = _lauta[alku_ruutu.rivi()][alku_ruutu.sarake()];

	// Poista nappula aloitus ruudusta
	_lauta[alku_ruutu.rivi()][alku_ruutu.sarake()] = nullptr;

	switch (nappula->tyyppi()) {
	case Tyyppi::VS:
	case Tyyppi::MS:
		switch (loppu_ruutu.rivi()) {
		case 0:
		case 7:
			nappula = TyyppiNappulaksi(siirto->miksiKorotetaan());
			break;
		case 3:
		case 4:
			if (siirto->kaksoisAskel()) {
				_kaksoisaskel_sarakkeella = alku_ruutu.sarake();
			}
		case 2:
		case 5:
			if (siirto->ohestaLyonti()) {
				_lauta[alku_ruutu.rivi()][loppu_ruutu.sarake()] = nullptr;  // Poista ohestalyöty
			}
		}
		break;
	case Tyyppi::VK:
		_valkea_kuningas_ruutu = loppu_ruutu;
		_onko_valkea_kuningas_liikkunut = true;
		break;
	case Tyyppi::MK:
		_musta_kuningas_ruutu = loppu_ruutu;
		_onko_musta_kuningas_liikkunut = true;
		break;
	case Tyyppi::VT:
		if (!_onko_valkea_dt_liikkunut && alku_ruutu == kValkeaDTRuutu) {
			_onko_valkea_dt_liikkunut = true;
		}
		else if (!_onko_valkea_kt_liikkunut && alku_ruutu == kValkeaKTRuutu) {
			_onko_valkea_kt_liikkunut = true;
		}
		break;
	case Tyyppi::MT:
		if (!_onko_musta_dt_liikkunut && alku_ruutu == kMustaDTRuutu) {
			_onko_musta_dt_liikkunut = true;
		}
		else if (!_onko_musta_kt_liikkunut && alku_ruutu == kValkeaKTRuutu) {
			_onko_musta_kt_liikkunut = true;
		}
		break;
	}

	// Siirrä nappula loppu ruutuun
	_lauta[loppu_ruutu.rivi()][loppu_ruutu.sarake()] = nappula;
}
#pragma endregion

#pragma region Anna Siirrot
void Asema::AnnaLaillisetSiirrot(std::vector<Siirto>& siirrot, const Vari vari) const {
	//std::vector<Siirto> parhaat_siirrot;
	//std::vector<Siirto> keskiverto_siirrot;
	//std::vector<Siirto> huonot_siirrot;
	//parhaat_siirrot.reserve(218);
	//keskiverto_siirrot.reserve(218);
	//huonot_siirrot.reserve(218);

	switch (vari) {
	case Vari::kValkea:
		if (!_onko_valkea_kuningas_liikkunut) {
			// Pitkä linnoitus
			if (!_onko_valkea_dt_liikkunut
				&& _lauta[0][1] == nullptr
				&& _lauta[0][2] == nullptr
				&& _lauta[0][3] == nullptr
				&& _lauta[0][0] == vt) {
				siirrot.emplace_back(Siirto(false, true));
			}
			// Lyhyt linnoitus
			if (!_onko_valkea_kt_liikkunut
				&& _lauta[0][6] == nullptr
				&& _lauta[0][5] == nullptr
				&& _lauta[0][7] == vt) {
				siirrot.emplace_back(Siirto(true, false));
			}
		}
		break;
	case Vari::kMusta:
		if (!_onko_musta_kuningas_liikkunut) {
			// Pitkä linnoitus
			if (!_onko_musta_dt_liikkunut
				&& _lauta[7][1] == nullptr
				&& _lauta[7][2] == nullptr
				&& _lauta[7][3] == nullptr
				&& _lauta[7][0] == mt) {
				siirrot.emplace_back(Siirto(false, true));
			}
			// Lyhyt linnoitus
			if (!_onko_musta_kt_liikkunut
				&& _lauta[7][6] == nullptr
				&& _lauta[7][5] == nullptr
				&& _lauta[7][7] == mt) {
				siirrot.emplace_back(Siirto(true, false));
			}
		}
		break;
	}

	for (int rivi = 0; rivi < kLautaKoko; rivi++) {
		for (int sarake = 0; sarake < kLautaKoko; sarake++) {
			if (_lauta[rivi][sarake] && _lauta[rivi][sarake]->vari() == vari) {
				_lauta[rivi][sarake]->AnnaSiirrot(siirrot, &Ruutu(rivi, sarake), this);
			}
		}
	}
}

#pragma endregion

#pragma region Evaluointi

int Asema::EvaluoiUusi(const std::vector<Siirto> siirrot) const {
	std::vector<Siirto> vastustajan_siirrot;
	vastustajan_siirrot.reserve(218);
	AnnaLaillisetSiirrot(vastustajan_siirrot, _siirtovuoro == Vari::kMusta ? Vari::kValkea : Vari::kMusta);

	enum class AsemaTyyppi {
		kSuljettu,
		kSemiSuljettu,
		kSemiAvoin,
		kAvoin
	};

	enum class PeliVaihe {
		kAvaus,
		kKeski,
		kVarhainenLoppu,
		kMyohainenLoppu
	};


	int upseerit = 0;
	int sotilaat = 0;

	for (int rivi = 0; rivi < kLautaKoko; ++rivi) {
		for (int sarake = 0; sarake < kLautaKoko; ++sarake) {
			Nappula* nappula = _lauta[rivi][sarake];
			if (nappula) {
				switch (nappula->tyyppi()) {
				case Tyyppi::VD:
				case Tyyppi::MD:
				case Tyyppi::VT:
				case Tyyppi::MT:
				case Tyyppi::VL:
				case Tyyppi::ML:
				case Tyyppi::VR:
				case Tyyppi::MR:
					++upseerit;
					break;
				case Tyyppi::VS:
				case Tyyppi::MS:
					++sotilaat;
					break;
				default:
					break;
				}
			}
		}
	}

	AsemaTyyppi asema_tyyppi;


	if (sotilaat <= 4) {
		asema_tyyppi = AsemaTyyppi::kAvoin;
	}
	else if (sotilaat <= 8) {
		asema_tyyppi = AsemaTyyppi::kSemiAvoin;
	}
	else if (sotilaat <= 12) {
		asema_tyyppi = AsemaTyyppi::kSemiSuljettu;
	}
	else {
		asema_tyyppi = AsemaTyyppi::kSuljettu;
	}

	int upseerien_summa = 0;

	double valkea_sotilaat_summa = 0;
	double musta_sotilaat_summa = 0;

	int evaluointi = 0;
	for (int rivi = 0; rivi < kLautaKoko; ++rivi) {
		for (int sarake = 0; sarake < kLautaKoko; ++sarake) {
			Nappula* nappula = _lauta[rivi][sarake];
			if (nappula) {
				double arvo = 0;
				
				switch (nappula->tyyppi()) {
				case Tyyppi::VD:
					arvo += 900.0 * kDaamiAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaDaamiRuutuTaulu[rivi][sarake];
					upseerien_summa += arvo;
					break;
				case Tyyppi::MD:
					arvo -= 900.0 * kDaamiAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaDaamiRuutuTaulu[rivi][sarake];
					upseerien_summa -= arvo;
					break;
				case Tyyppi::VT:
					arvo += 500.0 * kTorniAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaTorniRuutuTaulu[rivi][sarake];
					upseerien_summa += arvo;
					break;
				case Tyyppi::MT:
					arvo -= 500.0 * kTorniAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaTorniRuutuTaulu[rivi][sarake];
					upseerien_summa -= arvo;
					break;
				case Tyyppi::VL:
					arvo += 335.0 * kLahettiAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaLahettiRuutuTaulu[rivi][sarake];
					upseerien_summa += arvo;
					break;
				case Tyyppi::ML:
					arvo -= 335.0 * kLahettiAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaLahettiRuutuTaulu[rivi][sarake];
					upseerien_summa -= arvo;
					break;
				case Tyyppi::VR:
					arvo += 315.0 * kRatsuAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaRatsuRuutuTaulu[rivi][sarake];
					upseerien_summa += arvo;
					break;
				case Tyyppi::MR:
					arvo -= 315.0 * kRatsuAsemaTyyppiKerroin[static_cast<int>(asema_tyyppi)] + kMustaRatsuRuutuTaulu[rivi][sarake];
					upseerien_summa -= arvo;
					break;
				case Tyyppi::VS:
					valkea_sotilaat_summa += 100.0;
					arvo += kValkeaSotilasRuutuTaulu[rivi][sarake];
					break;
				case Tyyppi::MS:
					musta_sotilaat_summa += 100.0;
					arvo -= kMustaSotilasRuutuTaulu[rivi][sarake];
					break;
				case Tyyppi::VK:
					arvo = 20000.0;
					break;
				case Tyyppi::MK:
					arvo = -20000.0;
					break;
				}
				evaluointi += arvo;
			}
		}
	}


	PeliVaihe pelivaihe;
	if (upseerien_summa <= 1500) {
		pelivaihe = PeliVaihe::kMyohainenLoppu;
	}
	else if (upseerien_summa <= 3000) {
		pelivaihe = PeliVaihe::kVarhainenLoppu;
	}
	else if (upseerien_summa <= 4500) {
		pelivaihe = PeliVaihe::kKeski;
	}
	else {
		pelivaihe = PeliVaihe::kAvaus;
	}

	switch (pelivaihe) {
	case PeliVaihe::kAvaus:
	case PeliVaihe::kKeski:
	case PeliVaihe::kVarhainenLoppu:
		evaluointi += kValkeaKuningasKeskiRuutuTaulu[_valkea_kuningas_ruutu.rivi()][_valkea_kuningas_ruutu.sarake()];
		evaluointi -= kMustaKuningasKeskiRuutuTaulu[_musta_kuningas_ruutu.rivi()][_musta_kuningas_ruutu.sarake()];
		break;
	case PeliVaihe::kMyohainenLoppu:
		evaluointi += kValkeaKuningasLoppuRuutuTaulu[_valkea_kuningas_ruutu.rivi()][_valkea_kuningas_ruutu.sarake()];
		evaluointi -= kMustaKuningasLoppuRuutuTaulu[_musta_kuningas_ruutu.rivi()][_musta_kuningas_ruutu.sarake()];
		break;
	}

	// Mobiliteetti
	if (pelivaihe != PeliVaihe::kAvaus) {
		for (Siirto s : siirrot) {
			if (!s.lyhytLinna() && !s.pitkaLinna()) {
				switch (_lauta[s.alkuRuutu().rivi()][s.alkuRuutu().sarake()]->tyyppi()) {
				case Tyyppi::MD:
				case Tyyppi::ML:
				case Tyyppi::MR:
				case Tyyppi::MT:
					evaluointi += 10;
					break;
				case Tyyppi::VD:
				case Tyyppi::VL:
				case Tyyppi::VR:
				case Tyyppi::VT:
					evaluointi += 10;
					break;
				}
			}
		}
		for (Siirto s : vastustajan_siirrot) {
			if (!s.lyhytLinna() && !s.pitkaLinna()) {
				switch (_lauta[s.alkuRuutu().rivi()][s.alkuRuutu().sarake()]->tyyppi()) {
				case Tyyppi::MD:
				case Tyyppi::MR:
					evaluointi -= 15;
					break;
				case Tyyppi::ML:
				case Tyyppi::MT:
					evaluointi -= 10;
					break;
				case Tyyppi::VD:
				case Tyyppi::VR:
					evaluointi += 15;
					break;
				case Tyyppi::VL:
				case Tyyppi::VT:
					evaluointi += 10;
					break;
				case Tyyppi::VS:
					evaluointi += 5;
					break;
				case Tyyppi::MS:
					evaluointi -= 5;
					break;
				}
			}
		}
	}

	// Keskustan hallinta
	if (pelivaihe == PeliVaihe::kAvaus || pelivaihe == PeliVaihe::kKeski) {
		// Keskus
		for (Ruutu r : kKeskusRuudut) {
			if (_lauta[r.rivi()][r.sarake()]) {
				switch (_lauta[r.rivi()][r.sarake()]->tyyppi()) {
				case Tyyppi::VS:
					evaluointi += 40;
					break;
				case Tyyppi::MS:
					evaluointi -= 40;
					break;
				case Tyyppi::VL:
				case Tyyppi::VT:
				case Tyyppi::VR:
					evaluointi += 20;
					break;
				case Tyyppi::ML:
				case Tyyppi::MT:
				case Tyyppi::MR:
					evaluointi -= 20;
					break;
				case Tyyppi::VD:
					evaluointi += 30;
					break;
				case Tyyppi::MD:
					evaluointi -= 30;
					break;
				}
			}
		}
		// Laajempi keskus
		for (Ruutu r : kLaajempiKeskusRuudut) {
			if (_lauta[r.rivi()][r.sarake()]) {
				switch (_lauta[r.rivi()][r.sarake()]->tyyppi()) {
				case Tyyppi::VL:
				case Tyyppi::VT:
				case Tyyppi::VR:
				case Tyyppi::VD:
					evaluointi += 10;
					break;
				case Tyyppi::ML:
				case Tyyppi::MT:
				case Tyyppi::MR:
				case Tyyppi::MD:
					evaluointi -= 10;
					break;
				}
			}
		}
	}

	evaluointi += kSotilasArvoKerroin[static_cast<int>(pelivaihe)] * valkea_sotilaat_summa;
	evaluointi -= kSotilasArvoKerroin[static_cast<int>(pelivaihe)] * musta_sotilaat_summa;
	
	return evaluointi;
}

int Asema::EvaluoiVanha() const {
	int evaluointi = 0;
	for (int rivi = 0; rivi < kLautaKoko; ++rivi) {
		for (int sarake = 0; sarake < kLautaKoko; ++sarake) {
			Nappula* nappula = _lauta[rivi][sarake];
			if (nappula) {
				double arvo = 0;
				switch (nappula->tyyppi()) {
				case Tyyppi::VD:
					arvo += (900.0 + kMustaDaamiRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::MD:
					arvo -= (900.0 + kMustaDaamiRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::VT:
					arvo += (500.0 + kMustaTorniRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::MT:
					arvo -= (500.0 + kMustaTorniRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::VL:
					arvo += (330.0 + kMustaLahettiRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::ML:
					arvo -= (330.0 + kMustaLahettiRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::VR:
					arvo += (320.0 + kMustaRatsuRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::MR:
					arvo -= (320.0 + kMustaRatsuRuutuTaulu[rivi][sarake]);
					break;
				case Tyyppi::VS:
					arvo += 100.0 + kValkeaSotilasRuutuTaulu[rivi][sarake];
					break;
				case Tyyppi::MS:
					arvo -= 100.0 + kMustaSotilasRuutuTaulu[rivi][sarake];
					break;
				case Tyyppi::VK:
					arvo += 20000.0 + kValkeaKuningasKeskiRuutuTaulu[rivi][sarake];
					break;
				case Tyyppi::MK:
					arvo -= 20000.0 + kMustaKuningasKeskiRuutuTaulu[rivi][sarake];
					break;
				}
				evaluointi += arvo;
			}
		}
	}

	return evaluointi;
}

#pragma endregion

#pragma region Pelipuu
MinMaxPaluu Asema::AlphaBeta(int alpha, int beta, int syvyys_jaljella, SiirtovaihtoArvot** siirtovaihto_taulu, std::chrono::high_resolution_clock::time_point alku) {
	MinMaxPaluu paluuarvo;
#ifdef tt
	uint64_t zorba_luku = AnnaZorbaLuku();
	bool loytyi = false;
	SiirtovaihtoArvot* siirtovaihto_arvot = AnnaSiirtovaihtoArvot(zorba_luku, loytyi, siirtovaihto_taulu);
	if (loytyi) {
		siirtovaihto_arvot->_hyodyllinen = true;
	}
	if (loytyi && syvyys_jaljella <= siirtovaihto_arvot->_syvyys) {
		paluuarvo._evaluointi = siirtovaihto_arvot->_evaluointi;
		paluuarvo._parasSiirto = siirtovaihto_arvot->_paras_siirto;
		return paluuarvo;
	}
#endif

	std::vector<Siirto> siirrot;
	siirrot.reserve(218);
	AnnaLaillisetSiirrot(siirrot, _siirtovuoro);
	
#ifdef tt2
	if (loytyi &&
		(siirtovaihto_arvot->_paras_siirto.lyhytLinna() || siirtovaihto_arvot->_paras_siirto.pitkaLinna() ||
		!(siirtovaihto_arvot->_paras_siirto.alkuRuutu() == Ruutu(0, 0) && 
			siirtovaihto_arvot->_paras_siirto.loppuRuutu() == Ruutu(0, 0)))) {
		for (int i = 0; i < siirrot.size(); ++i) {
			if (siirrot[i] == siirtovaihto_arvot->_paras_siirto) {
				Siirto temp = siirrot[0];
				siirrot[0] = siirrot[i];
				siirrot[i] = temp;
			}
		}
	}
#endif

	if (syvyys_jaljella == 0) {
		paluuarvo._evaluointi = EvaluoiVanha();
		/*if (10000 < paluuarvo._evaluointi) {
			std::wcout << paluuarvo._evaluointi << "\n";
		}*/
		auto nyt = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = nyt - alku;
		if (kEtsimisAika < diff.count()) {
			paluuarvo._aika_loppu = true;
			return paluuarvo;
		}
	}
	else if (_siirtovuoro == Vari::kValkea) {
		paluuarvo._evaluointi = std::numeric_limits<int>::min();
		int non_legal_moves = 0;
		for (auto s : siirrot) {

			auto uusi_asema = *this;
			uusi_asema.PaivitaAsema(&s);

			if (uusi_asema.OnkoKuningasUhattu(_siirtovuoro)) {
				++non_legal_moves;
				continue;
			}

			MinMaxPaluu siirron_paluuarvo = uusi_asema.AlphaBeta(alpha, beta, syvyys_jaljella - 1, siirtovaihto_taulu, alku);

			/*if (siirron_paluuarvo._evaluointi > paluuarvo._evaluointi) {
				paluuarvo._evaluointi = siirron_paluuarvo._evaluointi;
				paluuarvo._parasSiirto = s;
			}*/

			if (siirron_paluuarvo._aika_loppu) {
				paluuarvo._aika_loppu = true;
				return paluuarvo;
			}

			if (siirron_paluuarvo._evaluointi >= beta) {
				paluuarvo._evaluointi = beta;
				break;
			}

			if (siirron_paluuarvo._evaluointi > alpha) {
				alpha = siirron_paluuarvo._evaluointi;
				paluuarvo._evaluointi = alpha;
				paluuarvo._parasSiirto = s;
			}
		}
		if (non_legal_moves == siirrot.size()) {
			if (OnkoKuningasUhattu(_siirtovuoro)) {
				paluuarvo._evaluointi = _siirtovuoro == Vari::kMusta ? 100000 : -100000;
			}
			else {
				paluuarvo._evaluointi = 0;
			}
		}
	}
	else {
		paluuarvo._evaluointi = std::numeric_limits<int>::max();
		int non_legal_moves = 0;
		for (auto s : siirrot) {
			auto uusi_asema = *this;
			uusi_asema.PaivitaAsema(&s);

			if (uusi_asema.OnkoKuningasUhattu(_siirtovuoro)) {
				++non_legal_moves;
				continue;
			}

			MinMaxPaluu siirron_paluuarvo = uusi_asema.AlphaBeta(alpha, beta, syvyys_jaljella - 1, siirtovaihto_taulu, alku);

			/*if (siirron_paluuarvo._evaluointi < paluuarvo._evaluointi) {
				paluuarvo._evaluointi = siirron_paluuarvo._evaluointi;
				paluuarvo._parasSiirto = s;
			}*/

			if (siirron_paluuarvo._aika_loppu) {
				paluuarvo._aika_loppu = true;
				return paluuarvo;
			}

			if (siirron_paluuarvo._evaluointi <= alpha) {
				paluuarvo._evaluointi = alpha;
				break;
			}

			if (siirron_paluuarvo._evaluointi < beta) {
				beta = siirron_paluuarvo._evaluointi;
				paluuarvo._evaluointi = beta;
				paluuarvo._parasSiirto = s;
			}
		}
		if (non_legal_moves == siirrot.size()) {
			if (OnkoKuningasUhattu(_siirtovuoro)) {
				paluuarvo._evaluointi = _siirtovuoro == Vari::kMusta ? 100000 : -100000;
			}
			else {
				paluuarvo._evaluointi = 0;
			}
		}
	}
#ifdef tt
	if (!loytyi) {
		delete siirtovaihto_taulu[zorba_luku % kSiirtoVaihtoTauluKoko];
		SiirtovaihtoArvot* uusi_siirtovaihto_arvot = new SiirtovaihtoArvot();
		uusi_siirtovaihto_arvot->_syvyys = syvyys_jaljella;
		uusi_siirtovaihto_arvot->_evaluointi = paluuarvo._evaluointi;
		uusi_siirtovaihto_arvot->_paras_siirto = paluuarvo._parasSiirto;
		SyotaSiirtovaihtoArvot(zorba_luku, uusi_siirtovaihto_arvot, siirtovaihto_taulu);
	}
	else if (siirtovaihto_arvot->_syvyys <= syvyys_jaljella) {
		siirtovaihto_arvot->_syvyys = syvyys_jaljella;
		siirtovaihto_arvot->_evaluointi = paluuarvo._evaluointi;
		siirtovaihto_arvot->_paras_siirto = paluuarvo._parasSiirto;
	}
#endif
	return paluuarvo;
}
#pragma endregion

#pragma region Siirtovaihtotaulu
void LuoSatunnaisLuvut() {
	// 12 * 64 (jokainen nappula, jokainen ruutu)
	// 1 (musta)
	// 4 (linnoitus oikeudet)
	// 8 (ohestalyönti)

	std::random_device rd;
	std::mt19937_64 gen(20);
	std::uniform_int_distribution<uint64_t> dis;
	//(std::llround(std::pow(2, 61)), std::llround(std::pow(2, 62)))

	/* A few random numbers: */
	for (int n = 0; n < 781; ++n) {
		Asema::_zobrist_satunnais_luvut[n] = dis(gen);
	}
}

SiirtovaihtoArvot* AnnaSiirtovaihtoArvot(const uint64_t zobrist_luku, bool& loytyi, SiirtovaihtoArvot** siirtovaihto_taulu) {
	SiirtovaihtoArvot* siirtovaihto_arvot = siirtovaihto_taulu[zobrist_luku % kSiirtoVaihtoTauluKoko];
	siirtovaihto_arvot && siirtovaihto_arvot->_hash == zobrist_luku ? loytyi = true : loytyi = false;
	return siirtovaihto_taulu[zobrist_luku % kSiirtoVaihtoTauluKoko];
}

void SyotaSiirtovaihtoArvot(const uint64_t zobrist_luku, SiirtovaihtoArvot* arvot, SiirtovaihtoArvot** siirtovaihto_taulu) {
	arvot->_hash = zobrist_luku;
	siirtovaihto_taulu[zobrist_luku % kSiirtoVaihtoTauluKoko] = arvot;
}

uint64_t Asema::AnnaZorbaLuku() const {
	uint64_t zobrinen_luku = 0;
	for (int ruutu = 0; ruutu < kLautaKoko * kLautaKoko; ++ruutu) {
		Nappula* nappula = _lauta[0][ruutu];
		if (nappula) {
			switch (nappula->tyyppi()) {
			case Tyyppi::VS:
				zobrinen_luku ^= _zobrist_satunnais_luvut[ruutu];
				break;
			case Tyyppi::MS:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 + ruutu];
				break;
			case Tyyppi::VT:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 2 + ruutu];
				break;
			case Tyyppi::MT:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 3 + ruutu];
				break;
			case Tyyppi::VR:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 4 + ruutu];
				break;
			case Tyyppi::MR:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 5 + ruutu];
				break;
			case Tyyppi::VL:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 6 + ruutu];
				break;
			case Tyyppi::ML:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 7 + ruutu];
				break;
			case Tyyppi::VD:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 8 + ruutu];
				break;
			case Tyyppi::MD:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 9 + ruutu];
				break;
			case Tyyppi::VK:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 10 + ruutu];
				break;
			case Tyyppi::MK:
				zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 11 + ruutu];
				break;
			}
		}
	}
	if (_siirtovuoro == Vari::kMusta) {
		zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 12];
	}

	if (!_onko_valkea_kuningas_liikkunut) {
		if (!_onko_valkea_kt_liikkunut) {
			zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 12 + 1];
		}
		if (!_onko_valkea_dt_liikkunut) {
			zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 12 + 2];
		}
	}
	else if (!_onko_musta_kuningas_liikkunut) {
		if (!_onko_musta_kt_liikkunut) {
			zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 12 + 3];
		}
		if (!_onko_musta_dt_liikkunut) {
			zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 12 + 4];
		}
	}

	if (_kaksoisaskel_sarakkeella != kEiKaksoisaskel) {
		zobrinen_luku ^= _zobrist_satunnais_luvut[64 * 12 + 5 + _kaksoisaskel_sarakkeella];
	}

	return zobrinen_luku;
}
#pragma endregion

#pragma region Apu funktiot
// Palauttaa tietyn tyypin nappula olion
Nappula* Asema::TyyppiNappulaksi(const Tyyppi tyyppi) {
	switch (tyyppi) {
	case Tyyppi::VD:
		return vd;
	case Tyyppi::VT:
		return vt;
	case Tyyppi::VR:
		return vr;
	case Tyyppi::VL:
		return vl;
	case Tyyppi::MD:
		return md;
	case Tyyppi::MT:
		return mt;
	case Tyyppi::ML:
		return ml;
	case Tyyppi::MR:
		return mr;
	default:
		return nullptr;
	}
}

enum {
	kYlaVasen,
	kYla,
	kYlaOikea,
	kOikea,
	kAlaOikea,
	kAla,
	kAlaVasen,
	kVasen,
	kSuuntienMaara
};

bool Asema::OnkoKuningasUhattu(const Vari vari) const {
	Ruutu kuninkaan_ruutu = vari == Vari::kValkea ? _valkea_kuningas_ruutu : _musta_kuningas_ruutu;
	int kuninkaan_rivi = kuninkaan_ruutu.rivi();
	int kuninkaan_sarake = kuninkaan_ruutu.sarake();

	for (int i = 0; i < kRatsuMahdollisetSiirrot.size(); ++i) {
		int rivi = kuninkaan_rivi + kRatsuMahdollisetSiirrot[i].rivi();
		int sarake = kuninkaan_sarake + kRatsuMahdollisetSiirrot[i].sarake();

		if (0 <= rivi && rivi < kLautaKoko && 0 <= sarake && sarake < kLautaKoko) {
			Nappula* nappula = _lauta[rivi][sarake];
			if (nappula && nappula->laji() == Laji::Ratsu && nappula->vari() != vari) {
				return true;
			}
		}
	}

	for (int suunta = 0; suunta < kSuuntienMaara; ++suunta) {
		int rivi_muutos;
		int sarake_muutos;

		switch (suunta) {
		case kYlaVasen:
			rivi_muutos = 1;
			sarake_muutos = -1;
			break;
		case kYla:
			rivi_muutos = 1;
			sarake_muutos = 0;
			break;
		case kYlaOikea:
			rivi_muutos = 1;
			sarake_muutos = 1;
			break;
		case kOikea:
			rivi_muutos = 0;
			sarake_muutos = 1;
			break;
		case kAlaOikea:
			rivi_muutos = -1;
			sarake_muutos = 1;
			break;
		case kAla:
			rivi_muutos = -1;
			sarake_muutos = 0;
			break;
		case kAlaVasen:
			rivi_muutos = -1;
			sarake_muutos = -1;
			break;
		case kVasen:
			rivi_muutos = 0;
			sarake_muutos = -1;
			break;
		}

		bool tormatty_vastustajan_nappulaan = false;
		int rivi = kuninkaan_rivi + rivi_muutos;
		int sarake = kuninkaan_sarake + sarake_muutos;
		int iteration = 0;
		for (; 0 <= rivi && rivi < kLautaKoko && 0 <= sarake && sarake < kLautaKoko;
			rivi += rivi_muutos, sarake += sarake_muutos, ++iteration) {
			if (_lauta[rivi][sarake]) {
				if (_lauta[rivi][sarake]->vari() == vari) {
					break;
				}
				else {
					tormatty_vastustajan_nappulaan = true;
					break;
				}
			}
		}

		if (tormatty_vastustajan_nappulaan) {
			bool vaaralliset_lajit[] = { false, false, false, false, false, false };
			vaaralliset_lajit[static_cast<int>(Laji::Daami)] = true;

			switch (suunta) {
			case kOikea:
			case kVasen:
			case kYla:
			case kAla:
				vaaralliset_lajit[static_cast<int>(Laji::Torni)] = true;
				break;
			case kYlaOikea:
			case kYlaVasen:
			case kAlaVasen:
			case kAlaOikea:
				vaaralliset_lajit[static_cast<int>(Laji::Lahetti)] = true;
				break;
			}

			if (iteration == 0) {
				vaaralliset_lajit[static_cast<int>(Laji::Kuningas)] = true;
				switch (suunta) {
				case kYlaOikea:
				case kYlaVasen:
					if (vari == Vari::kValkea) {
						vaaralliset_lajit[static_cast<int>(Laji::Sotilas)] = true;
					}
					break;
				case kAlaVasen:
				case kAlaOikea:
					if (vari == Vari::kMusta) {
						vaaralliset_lajit[static_cast<int>(Laji::Sotilas)] = true;
					}
					break;
				}
			}

			if (vaaralliset_lajit[static_cast<int>(_lauta[rivi][sarake]->laji())]) {
				return true;
			}
		}
	}


	return false;
}
#pragma endregion

