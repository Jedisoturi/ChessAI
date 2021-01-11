#include <list>
#include <string>
#include "asema.h"
#include "nappula.h"
#include <vector>
#include <array>

void Sotilas::AnnaSiirrot(std::vector<Siirto>& siirrot, Ruutu* ruutu, const Asema* asema) {
	if (_vari == Vari::kValkea) {
		// Ei päädyssä
		if (ruutu->rivi() + 1 < kLautaKoko) {
			// Eteenpäin liikkuminen
			if (ruutu->rivi() + 1 < kLautaKoko && asema->_lauta[ruutu->rivi() + 1][ruutu->sarake()] == nullptr) {
				// Korotus mahdollisuus
				if (ruutu->rivi() + 1 == kLautaKoko - 1) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake()), Tyyppi::VD));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake()), Tyyppi::VT));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake()), Tyyppi::VL));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake()), Tyyppi::VR));
				}
				// Ei korotus mahdollisuutta
				else {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake())));
				}

				// Kaksoisaskel
				if (ruutu->rivi() == 1 && asema->_lauta[3][ruutu->sarake()] == nullptr) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(3, ruutu->sarake()), true));
				}


			}

			// Oikealta syöminen
			if (ruutu->sarake() + 1 < kLautaKoko && asema->_lauta[ruutu->rivi() + 1][ruutu->sarake() + 1] && asema->_lauta[ruutu->rivi() + 1][ruutu->sarake() + 1]->vari() == Vari::kMusta) {
				// Korotus mahdollisuus
				if (ruutu->rivi() + 1 == kLautaKoko - 1) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() + 1), Tyyppi::VD));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() + 1), Tyyppi::VT));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() + 1), Tyyppi::VL));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() + 1), Tyyppi::VR));
				}
				// Ei korotus mahdollisuutta
				else {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() + 1)));
				}
			}

			// Vasemmalta syöminen
			if (0 <= ruutu->sarake() - 1 && asema->_lauta[ruutu->rivi() + 1][ruutu->sarake() - 1] && asema->_lauta[ruutu->rivi() + 1][ruutu->sarake() - 1]->vari() == Vari::kMusta) {
				// Korotus mahdollisuus
				if (ruutu->rivi() + 1 == kLautaKoko - 1) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() - 1), Tyyppi::VD));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() - 1), Tyyppi::VT));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() - 1), Tyyppi::VL));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() - 1), Tyyppi::VR));
				}
				// Ei korotus mahdollisuutta
				else {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() - 1)));
				}
			}

			// Ohestalyönti
			if (ruutu->rivi() == 4) {
				if (ruutu->sarake() + 1 == asema->_kaksoisaskel_sarakkeella) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() + 1), false, true));
				}
				else if (ruutu->sarake() - 1 == asema->_kaksoisaskel_sarakkeella) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() + 1, ruutu->sarake() - 1), false, true));
				}
			}

		}
	}
	else if (_vari == Vari::kMusta) {
		// Ei päädyssä
		if (0 <= ruutu->rivi() - 1) {
			// Eteenpäin liikkuminen
			if (asema->_lauta[ruutu->rivi() - 1][ruutu->sarake()] == nullptr) {
				// Korotus mahdollisuus
				if (ruutu->rivi() - 1 == 0) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake()), Tyyppi::MD));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake()), Tyyppi::MT));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake()), Tyyppi::ML));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake()), Tyyppi::MR));
				}
				// Ei korotus mahdollisuutta
				else {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake())));
				}

				// Kaksoisaskel
				if (ruutu->rivi() == 6 && asema->_lauta[4][ruutu->sarake()] == nullptr) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(4, ruutu->sarake()), true));
				}
			}

			// Oikealta syöminen
			if (0 <= ruutu->sarake() - 1 && asema->_lauta[ruutu->rivi() - 1][ruutu->sarake() - 1] && asema->_lauta[ruutu->rivi() - 1][ruutu->sarake() - 1]->vari() == Vari::kValkea) {
				// Korotus mahdollisuus
				if (ruutu->rivi() - 1 == 0) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() - 1), Tyyppi::MD));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() - 1), Tyyppi::MT));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() - 1), Tyyppi::ML));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() - 1), Tyyppi::MR));
				}
				// Ei korotus mahdollisuutta
				else {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() - 1)));
				}

			}

			// Vasemmalta syöminen
			if (ruutu->sarake() + 1 < kLautaKoko && asema->_lauta[ruutu->rivi() - 1][ruutu->sarake() + 1] && asema->_lauta[ruutu->rivi() - 1][ruutu->sarake() + 1]->vari() == Vari::kValkea) {
				// Korotus mahdollisuus
				if (ruutu->rivi() - 1 == 0) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() + 1), Tyyppi::MD));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() + 1), Tyyppi::MT));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() + 1), Tyyppi::ML));
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() + 1), Tyyppi::MR));
				}
				// Ei korotus mahdollisuutta
				else {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() + 1)));
				}
			}

			// Ohestalyönti
			if (ruutu->rivi() == 3) {
				if (ruutu->sarake() + 1 == asema->_kaksoisaskel_sarakkeella) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() + 1), false, true));
				}
				else if (ruutu->sarake() - 1 == asema->_kaksoisaskel_sarakkeella) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi() - 1, ruutu->sarake() - 1), false, true));
				}
			}
		}
	}
}


void Torni::AnnaSiirrot(std::vector<Siirto>& siirrot, Ruutu* ruutu, const Asema* asema) {
	// Ylös
	for (int rivi = ruutu->rivi() + 1; rivi < kLautaKoko; rivi++) {
		if (asema->_lauta[rivi][ruutu->sarake()]) {
			if (asema->_lauta[rivi][ruutu->sarake()]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, ruutu->sarake())));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, ruutu->sarake())));
		}
	}

	// Alas
	for (int rivi = ruutu->rivi() - 1; rivi >= 0; rivi--) {
		if (asema->_lauta[rivi][ruutu->sarake()]) {
			if (asema->_lauta[rivi][ruutu->sarake()]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, ruutu->sarake())));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, ruutu->sarake())));
		}
	}

	// Oikealle
	for (int sarake = ruutu->sarake() + 1; sarake < kLautaKoko; sarake++) {
		if (asema->_lauta[ruutu->rivi()][sarake]) {
			if (asema->_lauta[ruutu->rivi()][sarake]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi(), sarake)));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi(), sarake)));
		}
	}

	// Vasemmalle
	for (int sarake = ruutu->sarake() - 1; sarake >= 0; sarake--) {
		if (asema->_lauta[ruutu->rivi()][sarake]) {
			if (asema->_lauta[ruutu->rivi()][sarake]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi(), sarake)));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(ruutu->rivi(), sarake)));
		}
	}
}

void Lahetti::AnnaSiirrot(std::vector<Siirto>& siirrot, Ruutu* ruutu, const Asema* asema) {
	// Ylä oikea
	for (int rivi = ruutu->rivi() + 1, sarake = ruutu->sarake() + 1; rivi < kLautaKoko && sarake < kLautaKoko; rivi++, sarake++) {
		if (asema->_lauta[rivi][sarake]) {
			if (asema->_lauta[rivi][sarake]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
		}
	}

	// Ylä vasen
	for (int rivi = ruutu->rivi() + 1, sarake = ruutu->sarake() - 1; rivi < kLautaKoko && sarake >= 0; rivi++, sarake--) {
		if (asema->_lauta[rivi][sarake]) {
			if (asema->_lauta[rivi][sarake]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
		}
	}

	// Ala oikea
	for (int rivi = ruutu->rivi() - 1, sarake = ruutu->sarake() + 1; rivi >= 0 && sarake < kLautaKoko; rivi--, sarake++) {
		if (asema->_lauta[rivi][sarake]) {
			if (asema->_lauta[rivi][sarake]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
		}
	}

	// Ala vasen
	for (int rivi = ruutu->rivi() - 1, sarake = ruutu->sarake() - 1; rivi >= 0 && sarake >= 0; rivi--, sarake--) {
		if (asema->_lauta[rivi][sarake]) {
			if (asema->_lauta[rivi][sarake]->vari() != _vari) {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
			}

			break;
		}
		else {
			siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
		}
	}
}

void Ratsu::AnnaSiirrot(std::vector<Siirto>& siirrot, Ruutu* ruutu, const Asema* asema) {
	for (int i = 0; i < 8; i++) {
		int rivi = kRatsuMahdollisetSiirrot[i].rivi() + ruutu->rivi();
		int sarake = kRatsuMahdollisetSiirrot[i].sarake() + ruutu->sarake();

		// Pysytään laudalla
		if (rivi >= 0 && rivi < kLautaKoko && sarake >= 0 && sarake < kLautaKoko) {
			// Loppuruudussa on nappula
			if (asema->_lauta[rivi][sarake]) {
				// Nappula on vastustajan
				if (asema->_lauta[rivi][sarake]->vari() != _vari) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
				}
			}
			else {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
			}
		}
	}
}

void Daami::AnnaSiirrot(std::vector<Siirto>& siirrot, Ruutu* ruutu, const Asema* asema) {
	if (_vari == Vari::kValkea) {
		Asema::vt->AnnaSiirrot(siirrot, ruutu, asema);
		Asema::vl->AnnaSiirrot(siirrot, ruutu, asema);
	}
	else {
		Asema::mt->AnnaSiirrot(siirrot, ruutu, asema);
		Asema::ml->AnnaSiirrot(siirrot, ruutu, asema);
	}
}

void Kuningas::AnnaSiirrot(std::vector<Siirto>& siirrot, Ruutu* ruutu, const Asema* asema) {
	const Ruutu mahdolliset_siirrot[] = {
	Ruutu(1, 0),
	Ruutu(1, 1),
	Ruutu(0, 1),
	Ruutu(-1, 1),
	Ruutu(-1, 0),
	Ruutu(-1, -1),
	Ruutu(0, -1),
	Ruutu(1, -1)
	};

	for (int i = 0; i < 8; i++) {
		int rivi = mahdolliset_siirrot[i].rivi() + ruutu->rivi();
		int sarake = mahdolliset_siirrot[i].sarake() + ruutu->sarake();

		// Pysytään laudalla
		if (rivi >= 0 && rivi < kLautaKoko && sarake >= 0 && sarake < kLautaKoko) {
			// Loppuruudussa on nappula
			if (asema->_lauta[rivi][sarake]) {
				// Nappula on vastustajan
				if (asema->_lauta[rivi][sarake]->vari() != _vari) {
					siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
				}
			}
			else {
				siirrot.emplace_back(Siirto(*ruutu, Ruutu(rivi, sarake)));
			}
		}
	}
}