#include <Windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>
#include "kayttoliittyma.h"

using namespace std;

bool OnLaudanSisalla(int arvo);


void Kayttoliittyma::PiirraLauta() {
	// Saa unicode shakkinappulat toimimaan cout:n kanssa:
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Aloita taulukon piirtäminen ylä vasemmalta
	for (int row = kLautaKoko - 1; 0 <= row; --row) {
		// Tulosta rivi numero
		std::wcout << row + 1;
		// Käy läpi rivin sarakkeet
		for (int col = 0; col < kLautaKoko; ++col) {
			// Joka toinen tausta valkoinen
			if ((row + col) % 2 == 0) {
				// Harmaa
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | 0);
			}
			else {
				// Valkoinen
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED |
										BACKGROUND_GREEN | BACKGROUND_BLUE);
			}

			Nappula* nappula = _asema->_lauta[row][col];

			// Kohdassa on nappula
			if (nappula != nullptr) {
				std::wcout << nappula->unicode() << "";
			}
			// Tyhjä ruutu
			else {
				std::wcout << "  ";
			}
		}
		// Resetoi tausta mustaksi
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | 0);
		std::wcout << "\n";
	}
	// Tulosta sarakkeiden kirjaimet
	std::wcout << "  a b c d e f g h\n";
}

Tyyppi Kayttoliittyma::AnnaKorotusTyyppi() {
	std::wstring korotus;
	std::wcout << "Miksi korotetaan: ";
	std::getline(std::wcin, korotus);

	switch (_asema->siirtovuoro()) {
	case Vari::kValkea:
		if (korotus.compare(L"R") == 0) {
			return Tyyppi::VR;
		}
		else if (korotus.compare(L"D") == 0) {
			return Tyyppi::VD;
		}
		else if (korotus.compare(L"L") == 0) {
			return Tyyppi::VL;
		}
		else if (korotus.compare(L"T") == 0) {
			return Tyyppi::VT;
		}
		break;
	case Vari::kMusta:
		if (korotus.compare(L"R") == 0) {
			return Tyyppi::MR;
		}
		else if (korotus.compare(L"D") == 0) {
			return Tyyppi::MD;
		}
		else if (korotus.compare(L"L") == 0) {
			return Tyyppi::ML;
		}
		else if (korotus.compare(L"T") == 0) {
			return Tyyppi::MT;
		}
		break;
	}
}


Siirto Kayttoliittyma::AnnaVastustajanSiirto() {
	while (true) {
		// Kerro kumman vuoro
		if (_asema->siirtovuoro() == Vari::kValkea) {
			std::wcout << "Valkoisen ";
		}
		else {
			std::wcout << "Mustan ";
		}
		std::wcout << "siirto: ";

		// Ota siirto komento
		std::wstring siirto_komento;
		std::getline(std::wcin, siirto_komento);

		// Poista tyyppi merkki alusta, jos syötetty (esim. R, K, D jne.)
		if (siirto_komento.size() == 6) {
			siirto_komento.erase(0, 1);
		}
		// Siirto olio
		Siirto uusi_siirto;

		// Linnoitus komentojen muoto
		const std::wstring lyhyt_linna_komento = L"O-O";
		const std::wstring pitka_linna_komento = L"O-O-O";

		// Pitkä linna
		if (siirto_komento.compare(pitka_linna_komento) == 0) {
			uusi_siirto = Siirto(false, true);
		}
		// Lyhyt linna
		else if (siirto_komento.compare(lyhyt_linna_komento) == 0) {
			uusi_siirto = Siirto(true, false);
		}
		// Normaali siirto (ei linnoitus)
		else {
			int alku_sarake = std::tolower(siirto_komento[0]) - 'a';
			int alku_rivi = siirto_komento[1] - '1';
			int loppu_sarake = std::tolower(siirto_komento[3]) - 'a';
			int loppu_rivi = siirto_komento[4] - '1';
			
			// Tarkista onko syötetyt sarakkeet ja rivit laudan sisällä. Muuten kaatuu 
			if (!OnLaudanSisalla(alku_rivi)
				|| !OnLaudanSisalla(alku_sarake)
				|| !OnLaudanSisalla(loppu_rivi)
				|| !OnLaudanSisalla(loppu_sarake)
				|| !_asema->_lauta[alku_rivi][alku_sarake]) {
				continue;
			}

			Nappula* nappula = _asema->_lauta[alku_rivi][alku_sarake];

			switch (nappula->tyyppi()) {
			case Tyyppi::VS:
				break;
			case Tyyppi::MS:
				break;
			}

			Tyyppi korotus_tyyppi = Tyyppi::EiKorotus;
			if (_asema->_lauta[alku_rivi][alku_sarake]->laji() == Laji::Sotilas &&
				((_asema->siirtovuoro() == Vari::kValkea && loppu_rivi == kLautaKoko - 1)
				 || (_asema->siirtovuoro() == Vari::kMusta && loppu_rivi == 0))) {
				korotus_tyyppi = AnnaKorotusTyyppi();
			}
			uusi_siirto = Siirto(Ruutu(alku_rivi, alku_sarake), Ruutu(loppu_rivi, loppu_sarake), korotus_tyyppi);
		}

		// Hae kaikki lailliset siirrot ja katso onko uusi siirto yksi niistä
		std::vector<Siirto> siirrot;
		_asema->AnnaLaillisetSiirrot(siirrot, _asema->siirtovuoro());

		for (Siirto s : siirrot) {
			if (uusi_siirto == s)
				return uusi_siirto;
		}
	}
}

bool OnLaudanSisalla(int arvo) {
	return 0 <= arvo && arvo < kLautaKoko;
}