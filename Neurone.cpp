#include "Neurone.hpp"
#include <cmath>
#include <cassert>


Neurone::Neurone(Nature n) {
	//double tau = capacite*resistance;
	//double c1 = exp(-(h/10)/tau);
	//double c2 = 1 - exp(-(h/10)/tau);
	potMemb = 0.0;
	nature = n;
	while(!pics.empty()) {
		pics.pop_back();
	}
	/*for (auto J : tampon) {
		J = 0;
	}*/
	refractaire = false;
}

Neurone::Neurone(std::vector<Neurone*> charge) {
	Neurone();
	chargeables = charge;
}

Neurone::~Neurone() {
	while(!pics.empty()) {
		pics.pop_back();
	}
}


size_t Neurone::accesNbPics() {
	return pics.size();
}

double Neurone::accesPotMemb() {
	return potMemb;
}

std::vector<double> Neurone::accesPasTempsPics() {
	return pics;
}

std::vector<Neurone*> Neurone::accesChargeables() {
	return chargeables;
}

void Neurone::modifieChargeables(std::vector<Neurone*> nouvCharg){
	chargeables = nouvCharg;
}

bool Neurone::evolue(int h, int pasGlobal, double Iext) {
	pasCourant = pasGlobal;
	if (refractaire){
		refractaire = false;
		//std::cout << "dehors";
	}
	if (potMemb >= seuil) {
		pics.push_back(pasCourant);
		refractaire = true;
		potMemb = 0;
	}
	//double tau = capacite*resistance;
	double J (gestionTampon());
	if (tau > 0. and !refractaire) {
		potMemb = potMemb * c1 + Iext * resistance * c2 + J;
	}
	if (potMemb >= seuil) {
		return true;
	}
	return false;
}

double Neurone::gestionTampon() {
	double J (0);
	assert(tampon.size() > 0);											//inutile pour l'instant car il s'agit d'un array et non d'un vector, mais lors d'un changement de conception il pourrait s'avérer utile
	if (tampon[0] > 1e-15) {
		J = tampon[0];
	}
	for (size_t i (1); i < tampon.size() ; ++i){
		tampon[i-1] = tampon[i];
	}
	tampon[tampon.size()-1] = 0;
	//std::cout << tampon[tampon.size()+1] << std::endl;				//affiche le temps, pas SegFault ??
	return J;
}
	

void Neurone::recoit(int h, int pasCourant, double Iext, double const& J) {
	tampon[tampon.size()-1] += J;
	std::cout << tampon[tampon.size()-1] << std::endl;
	/*double tau = capacite*resistance;
	if (tau > 0. and !refractaire) {
		potMemb = potMemb * exp(-h/tau) + Iext * resistance * (1-exp(-h/tau)) + TensionJ;
	}*/
}
