#pragma once

#include <list>
#include <string>
#include "asema.h"
#include <vector>

// Yliluokka shakkinappuloille.
class Nappula {
protected:
	std::wstring	_unicode;	// nappulaa vastaava unicode-merkki
	Vari			_vari;		// valkea = 0, musta = 1
	Tyyppi			_tyyppi;		// VT, VR, MT tms.
	Laji			_laji;

public:
	Nappula(std::wstring unicode, Vari vari, Tyyppi tyyppi, Laji laji)
	{
		_unicode = unicode;
		_vari = vari;
		_tyyppi = tyyppi;
		_laji = laji;
	}

	const std::wstring& unicode() const { return _unicode; }
	Vari vari() const { return _vari; }
	Tyyppi tyyppi() const { return _tyyppi; }
	Laji laji() const { return _laji; }
	virtual void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*) = 0;
	virtual ~Nappula(){}
};

class Sotilas : public Nappula
{
	using Nappula::Nappula;
	void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*);
};

class Torni : public Nappula
{
	using Nappula::Nappula;
	void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*);
};

class Lahetti : public Nappula
{
	using Nappula::Nappula;
	void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*);
};

class Ratsu : public Nappula
{
	using Nappula::Nappula;
	void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*);
};

class Daami : public Nappula
{
	using Nappula::Nappula;
	void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*);
};

class Kuningas : public Nappula
{
	using Nappula::Nappula;
	void AnnaSiirrot(std::vector<Siirto>& lista, Ruutu*, const Asema*);
};