#include "Neurone.hpp"
#include <cmath>
#include <cassert>
#include <random>


Neurone::Neurone(Nature n)
	: potMemb (0.0), horlogeRefractaire(tauRefractaire), nature(n) {	//initialisations
	
	while(!pics.empty()) {
		pics.pop_back();
	}
	refractaire = false;
}

Neurone::Neurone(std::vector<Neurone*> charge) {						//conception où il faudrait passer en paramètre les neurones auxquels l'instance courante pourrait passer son pic
	Neurone();
	chargeables = charge;
}


size_t Neurone::accesNbPics() {											//accesseurs
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

Nature Neurone::accesNature() {
	return nature;
}

void Neurone::modifieChargeables(std::vector<Neurone*> nouvCharg){		//manipulateur
	chargeables = nouvCharg;
}

bool Neurone::evolue(int pasGlobal, double Iext) {
	if (refractaire){													//cas où il est réfractaire
		gestionRefractaire();
	}
	if (potMemb >= seuil) {												//occurence d'un pic
		gestionPic(pasGlobal);
	}
	double J (gestionTampon());
	
	if (tau > 0. and !refractaire) {
		std::random_device rd;											//génération de la variable aléatoire									
		std::mt19937 gen(rd());
		std::poisson_distribution<> d(nu * nombreExcitateurs * h * TensionJe);
		
		potMemb = potMemb * c1 + Iext * resistance * c2 + J + d(gen);	//equation principale décrivant l'évolution du potentiel membranaire
	}
	if (potMemb >= seuil) {
		return true;
	}
	return false;
}


void Neurone::gestionRefractaire() {
	potMemb = 0;
	--horlogeRefractaire;												//décrémente l'horloge du temps où le neurone est réfractaire
	if (horlogeRefractaire <= 0) {
		refractaire = false;
	}
}

void Neurone::gestionPic(int pasGlobal) {
	pics.push_back(pasGlobal);											//enregistre le temps
	refractaire = true;
	horlogeRefractaire = tauRefractaire;								//réinitialise l'horloge
	potMemb = 0;
}


double Neurone::gestionTampon() {
	assert(tampon.size() > 0);											//inutile pour l'instant car il s'agit d'un array et non d'un vector, mais lors d'un changement de conception il pourrait s'avérer utile
	double J (tampon[0]);
	for (size_t i (1); i < tampon.size() ; ++i){
		tampon[i-1] = tampon[i];
	}
	tampon[tampon.size()-1] = 0;
	//std::cout << tampon[tampon.size()+1] << std::endl;				//affiche le temps, pas SegFault ??
	return J;
}
		

void Neurone::recoit(double const& J) {
	tampon[tampon.size()-1] += J;
}
