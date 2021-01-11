#include "ruutu.h"

std::wostream& operator<<(std::wostream& os, const Ruutu& ruutu) {
	os << (char)('a' + ruutu._sarake) << ruutu._rivi + 1;
	return os;
}

bool operator==(const Ruutu& a, const Ruutu& b)
{
	return a._rivi == b._rivi && a._sarake == b._sarake;
}