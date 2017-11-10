#include "Neurone.hpp"
#include <cmath>
#include <cassert>
#include <random>

//CONSTRUCTEURS, DESTRUCTEUR____________________________________________
Neurone::Neurone(Nature n)
	: potMemb (0.0), horlogeRefractaire(tauRefractaire), nature(n), refractaire (false) {	//initialisations
	
	while(!pics.empty()) {
		pics.pop_back();
	}
	for (auto carre : tampon) {
		carre = 0.0;
	}
}

Neurone::Neurone(std::vector<Neurone*> charge, Nature n)				//conception où il faudrait passer en paramètre les neurones auxquels l'instance courante pourrait passer son pic
	: potMemb (0.0), horlogeRefractaire(tauRefractaire), nature(n), refractaire (false) {	//initialisations
	
	while(!pics.empty()) {
		pics.pop_back();
	}
	for (auto carre : tampon) {
		carre = 0.0;
	}
	chargeables = charge;
}

//ACCESSEURS____________________________________________________________
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

Nature Neurone::accesNature() {
	return nature;
}

//MANIPULATEUR__________________________________________________________
	
void Neurone::modifieChargeables(std::vector<Neurone*> nouvCharg){		
	chargeables = nouvCharg;
}

//AUTRES METHODES PUBLIQUES_____________________________________________

bool Neurone::evolue(int pasGlobal, double Iext, bool poisson) {
	if (refractaire){													//cas où il est réfractaire
		gestionRefractaire();
	}
	if (potMemb >= seuil) {												//occurence d'un pic
		gestionPic(pasGlobal);
	}
	double J (gestionTampon());
	
	if (!refractaire) {
		if (poisson) {
			static std::random_device rd;								//génération de la variable aléatoire									
			static std::mt19937 gen(rd());
			static std::poisson_distribution<> d(nuExtParPas);
		//std::cerr << nu * nombreExcitateurs * h/10. * TensionJe << "     ";
			potMemb = potMemb * c1 + Iext * resistance * c2 + J + d(gen)*TensionJe;	//equation principale décrivant l'évolution du potentiel membranaire
		//std::cerr << d(gen) << " ";
		//std::cerr << J << "   " << std::endl;
		} else {
			potMemb = potMemb * c1 + Iext * resistance * c2 + J;		
		}
	}
	if (potMemb >= seuil) {
		return true;
	}
	return false;
}

void Neurone::recoit(double const& J) {
	tampon[tampon.size()-1] += J;
}

//METHODES PRIVEES______________________________________________________

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
	return J;
}
