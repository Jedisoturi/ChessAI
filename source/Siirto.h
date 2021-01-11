#pragma once
#include <iostream>
#include "ruutu.h"
#include "vakiot.h"

// Ns. "forward declaration". Nyt Asema-luokassa voidaa esitellä Nappula-osoittimia ilman,
// että nappula.h -tiedostoa täytyy includoida.
class Nappula;

// Siirto kuvaa nappulan siirtymisen ruudusta toiseen, mukaanlukien erikoissiirrot
// (linnoitus ja ohestalyönti).
class Siirto {
public:
	Siirto();
	Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu);
	Siirto(bool lyhyt_linna, bool pitka_linna);  // Poikkeussiirto linnoitusta varten
	Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu, bool kaksois_askel);  // Poikkeussiirto kaksoisaskelta varten
	Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu, bool kaksois_askel, bool ohestalyonti);  // Poikkeussiirto ohestalyontia varten
	Siirto(Ruutu alku_ruutu, Ruutu loppu_ruutu, Tyyppi miksi_korotetaan);  // Poikkeussiirto korotusta varten
	
	const Ruutu& alkuRuutu() const { return _alku_ruutu; }
	const Ruutu& loppuRuutu() const { return _loppu_ruutu; }
	Tyyppi miksiKorotetaan() const { return _miksi_korotetaan; }
	bool lyhytLinna() const { return _lyhyt_linna; }
	bool pitkaLinna() const { return _pitka_linna; }
	bool kaksoisAskel() const { return _kaksois_askel; }
	bool ohestaLyonti() const { return _ohestalyonti; }

	friend bool operator==(const Siirto& a, const Siirto& b);
	friend std::wostream& operator<<(std::wostream& os, const Siirto& siirto);
private:
	Ruutu _alku_ruutu;
	Ruutu _loppu_ruutu;
	Tyyppi _miksi_korotetaan = Tyyppi::EiKorotus;
	bool _lyhyt_linna = false;
	bool _pitka_linna = false;
	bool _kaksois_askel = false;
	bool _ohestalyonti = false;
};


