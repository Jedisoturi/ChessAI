#include "Siirto.h"

Siirto::Siirto() {
	_alku_ruutu = Ruutu(0, 0);
	_loppu_ruutu = Ruutu(0, 0);
}

Siirto::Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu)
{
	_alku_ruutu = alku_ruutu;
	_loppu_ruutu = loppu_ruutu;
}

Siirto::Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu, bool kaksois_askel)
{
	_alku_ruutu = alku_ruutu;
	_loppu_ruutu = loppu_ruutu;
	_kaksois_askel = kaksois_askel;
}

Siirto::Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu, bool kaksois_askel, bool ohestalyonti)
{
	_alku_ruutu = alku_ruutu;
	_loppu_ruutu = loppu_ruutu;
	_kaksois_askel = kaksois_askel;
	_ohestalyonti = ohestalyonti;
}


Siirto::Siirto(bool lyhyt_linna, bool pitka_linna)
{
	_lyhyt_linna = lyhyt_linna;
	_pitka_linna = pitka_linna;
}

Siirto::Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu, Tyyppi miksi_korotetaan)
{
	_alku_ruutu = alku_ruutu;
	_loppu_ruutu = loppu_ruutu;
	_miksi_korotetaan = miksi_korotetaan;
}

bool operator==(const Siirto& siirto1, const Siirto& siirto2)
{
	if (siirto1._alku_ruutu == siirto2._alku_ruutu &&
		siirto1._loppu_ruutu == siirto2._loppu_ruutu) {
		if (siirto1._lyhyt_linna && siirto2._lyhyt_linna
			|| siirto1._pitka_linna && siirto2._pitka_linna) {
			return true;
		}
		if (siirto1._miksi_korotetaan == siirto2._miksi_korotetaan) {
			return true;
		}
	}
	return false;
}

std::wostream& operator<<(std::wostream& os, const Siirto& siirto) {
	if (siirto._lyhyt_linna) {
		os << "Lyhyt linna\n";
	}
	else if (siirto._pitka_linna) {
		os << "Pitka linna\n";
	}
	else {
		os << siirto._alku_ruutu << "-" << siirto._loppu_ruutu;
	}
	
	return os;
}