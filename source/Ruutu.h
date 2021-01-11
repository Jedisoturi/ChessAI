#pragma once
#include <iostream>
#include <array>

class Ruutu {
public:
	Ruutu(int rivi, int sarake) : _rivi(rivi), _sarake(sarake) {}
	Ruutu() : _rivi(0), _sarake(0) {}
	int rivi() const { return _rivi; }
	int sarake() const { return _sarake; }

	friend std::wostream& operator<<(std::wostream& os, const Ruutu& ruutu);
	friend bool operator==(const Ruutu& a, const Ruutu& b);
private:
	int _sarake;
	int _rivi;
};

const auto kValkeaKuningasRuutu = Ruutu(0, 4);
const auto kValkeaDTRuutu = Ruutu(0, 0);
const auto kValkeaKTRuutu = Ruutu(0, 7);

const auto kMustaKuningasRuutu = Ruutu(7, 4);
const auto kMustaDTRuutu = Ruutu(7, 0);
const auto kMustaKTRuutu = Ruutu(7, 7);

const std::array<Ruutu, 4> kKeskusRuudut = { 
	Ruutu(4, 3), Ruutu(4, 4),
	Ruutu(3, 3), Ruutu(3, 4)  
};
const std::array<Ruutu, 12> kLaajempiKeskusRuudut = { 
	Ruutu(2, 2), Ruutu(2, 3), Ruutu(2, 4), Ruutu(2, 5),
	Ruutu(3, 2), Ruutu(3, 5),
	Ruutu(4, 2), Ruutu(4, 5),
	Ruutu(5, 2), Ruutu(5, 3), Ruutu(5, 4), Ruutu(5, 5)
};
