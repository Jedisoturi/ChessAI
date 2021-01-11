#include <iostream>
#include <string>
#include "kayttoliittyma.h"
#include "asema.h"
#include <vector>
#include <limits>
#include "vakiot.h"
#include "siirtovaihto.h"
#include <chrono>


using namespace std;
double kEtsimisAika = 3.0;

int main()
{
	typedef std::chrono::high_resolution_clock clock;


	LuoSatunnaisLuvut();
	SiirtovaihtoArvot** siirtovaihto_taulu = new SiirtovaihtoArvot * [kSiirtoVaihtoTauluKoko];
	for (int i = 0; i < kSiirtoVaihtoTauluKoko; ++i) {
		siirtovaihto_taulu[i] = nullptr;
	}
	
	//for (int n = 0; n < 781; ++n)
	//	std::wcout << Asema::_zobrist_satunnais_luvut[n] << '\n';

	std::wcout << sizeof(SiirtovaihtoArvot) << "\n";

	Asema asema;
	Kayttoliittyma ui(&asema);
	ui.PiirraLauta();

	int ply = 1;
	while (true)
	{
		std::vector<Siirto> siirrot;
		siirrot.reserve(218);
		asema.AnnaLaillisetSiirrot(siirrot, asema.siirtovuoro());

		int non_legal_moves = 0;
		for (Siirto s : siirrot) {
			auto uusi_asema = asema;
			uusi_asema.PaivitaAsema(&s);

			if (uusi_asema.OnkoKuningasUhattu(asema.siirtovuoro())) {
				++non_legal_moves;
			}
		}
		if (non_legal_moves == siirrot.size()) {
			std::wcout << "Peli on päättynyt\n";
			break;
		}

		MinMaxPaluu paluuarvo;
		MinMaxPaluu uusi_paluuarvo;
		Siirto siirto;
		auto start = clock::now();
		auto current = clock::now();
		std::chrono::duration<double> diff = current - start;
		switch (asema.siirtovuoro()) {
		case Vari::kValkea:
			//paluuarvo._parasSiirto = ui.AnnaVastustajanSiirto();
			start = clock::now();
			for (int i = 1; ; ++i) {
				if (i % 2 == 0) {
					uusi_paluuarvo = asema.AlphaBeta(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), i, siirtovaihto_taulu, start);
					if (!uusi_paluuarvo._aika_loppu) {
						paluuarvo = uusi_paluuarvo;
					}
				}
				else {
					uusi_paluuarvo = asema.AlphaBeta(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), i, siirtovaihto_taulu, start);
				}
				current = clock::now();
				diff = current - start;
				std::wcout << i << " " << diff.count() << "\n";
				if (uusi_paluuarvo._aika_loppu) {
					break;
				}
			}
			break;
		case Vari::kMusta:
			start = clock::now();
			for (int i = 1; ; ++i) {
				if (i % 2 == 0) {
					uusi_paluuarvo = asema.AlphaBeta(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), i, siirtovaihto_taulu, start);
					if (!uusi_paluuarvo._aika_loppu) {
						paluuarvo = uusi_paluuarvo;
					}
				}
				else {
					uusi_paluuarvo = asema.AlphaBeta(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), i, siirtovaihto_taulu, start);
				}
				current = clock::now();
				diff = current - start;
				std::wcout << i << " " << diff.count() << "\n";
				if (uusi_paluuarvo._aika_loppu) {
					break;
				}
			}
			break;
		}

#ifdef tt
		int count = 0;
		std::wcout << L"Deleting\n";
		for (int i = 0; i < kSiirtoVaihtoTauluKoko; ++i) {
			if (siirtovaihto_taulu[i]) {
				if (siirtovaihto_taulu[i]->_hyodyllinen) {
					siirtovaihto_taulu[i]->_hyodyllinen = false;
					siirtovaihto_taulu[i]->_ika = 0;
				}
				else if (siirtovaihto_taulu[i]->_ika < 3) {
					++siirtovaihto_taulu[i]->_ika;
				}
				else {
					++count;
					delete siirtovaihto_taulu[i];
					siirtovaihto_taulu[i] = nullptr;
				}
			}
		}
		std::wcout << "Deleted: " << count << "\n";
#endif

		asema.PaivitaAsema(&paluuarvo._parasSiirto);
		ui.PiirraLauta();

		std::wcout << ply << ": " << asema.AnnaZorbaLuku() << "\n";
		++ply;

		if (ply >= 60)
		{
			kEtsimisAika = 15.0;
		}
	}
	
	return 0;
}
