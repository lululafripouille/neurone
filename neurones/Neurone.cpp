#include "Neurone.hpp"
#include <cmath>


Neurone::Neurone() {
	potMemb = 0.0;
	while(!pics.empty()) {
		pics.pop_back();
	}
	/*for (auto J : tampon) {
		J = 0;
	}*/
	refractaire = false;
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

std::vector<double> Neurone::accesTempsPics() {
	return pics;
}


bool Neurone::evolue(double h, double tempsGlobal, double Iext) {
	tempsCourant = tempsGlobal;
	if (refractaire){
		refractaire = false;
		//std::cout << "dehors";
	}
	if (potMemb >= seuil) {
		pics.push_back (tempsCourant);
		refractaire = true;
		potMemb = 0;
	}
	double tau = capacite*resistance;
	double J (0);
	for (size_t i (1); i < tampon.size() ; ++i){
		tampon[i-1] = tampon[i];
	}
	tampon[tampon.size()-1] = 0;
	if (tampon[0] > 0.000000001) {
		J = tampon[0];
	} 
	if (tau > 0. and !refractaire) {
		potMemb = potMemb * exp(-h/tau) + Iext * resistance * (1-exp(-h/tau)) + J;
	}
	if (potMemb >= seuil) {
		return true;
	}
	return false;
}


void Neurone::recoit(double h, double tempsCourant, double Iext, double const& J) {
	tampon[tampon.size()-1] += J;
	//std::cout << tampon[tampon.size()-1];
	/*double tau = capacite*resistance;
	if (tau > 0. and !refractaire) {
		potMemb = potMemb * exp(-h/tau) + Iext * resistance * (1-exp(-h/tau)) + TensionJ;
	}*/
}
