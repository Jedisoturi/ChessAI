#pragma once
#include "asema.h"
#include "nappula.h"
#include "vakiot.h"
#include "siirto.h"

// Shakkiohjelman käyttöliittymä, joka osaa visualisoida nykyisen aseman
// ja lukea käyttäjän syöttämät siirrot.
class Kayttoliittyma {
public:
	Kayttoliittyma(const Asema* asema) { _asema = asema; }
	void PiirraLauta();
	Siirto AnnaVastustajanSiirto();
private:
	const Asema* _asema;

	Tyyppi AnnaKorotusTyyppi();
};