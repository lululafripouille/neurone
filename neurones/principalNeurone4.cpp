#include <iostream>
#include "Reseau.hpp"

int main () {
	double Iext (0);
	int pasCourant (0);
	bool poisson (true);
	Reseau res;
	
	res.evolue(pasCourant, Iext, poisson);
	return 0;
}
