#include <cassert>
#include "Reseau.hpp"
#include <cmath>
#include <random>
#include <array>


Reseau::Reseau() {
	/*std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution d (0.1);
	for (auto& ligne : relations) {
		for (auto& carre : ligne) {
			carre = d(gen);
			std::cout << carre;
		}
	std::cout << std::endl;
	}*/
	for (size_t i(0); i < reseau.size(); ++i) {
		if (i < nombreExcitateurs) {
			reseau[i] = new Neurone(Excitateur);						//crée les neurones, les premiers sont excitateurs, les seconds inhibiteurs
		} else {
			reseau[i] = new Neurone(Inhibiteur);
		}
	}
	
	std::random_device rd;												//pour distribution de Poisson
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<> disExc (0, nombreExcitateurs-1);
	std::uniform_int_distribution<> disInh (nombreExcitateurs, nombreExcitateurs+nombreInhibiteurs-1);
	
	for (auto& ligne : relations) {
		for (auto& carre : ligne) {
			carre = 0;													//initialise la matrice des connexions à zéro
		}
		for (int j(0); j < ConnexionExcitatrices ; ++j) {				//assigne une connexion à une relation selon le nombre généré par Poisson 
			int a (disExc(gen));
			assert(a >= 0);
			ligne[a] += 1;
		}
		for (int k(0); k < ConnexionInhibitrices; ++k) {				//assigne une connexion à une relation selon le nombre généré par Poisson
			int b(disInh(gen));
			assert(b < tailleReseau);
			ligne[b] += 1;
		}
		for (auto carre : ligne) {										//afffiche la matrice
			std::cout << carre;
		}
		std::cout << std::endl;
	}
}

/*
Reseau::Reseau(std::array<Neurone*> neurones) {
	//std::cout << "salut";
	reseau = neurones;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution d (0.1);
	for (auto& ligne : relations) {
		for (auto& carre : ligne) {
			carre = d(gen);
			std::cout << carre;
		}
	}
}*/

Reseau::~Reseau() {
	
	for (size_t i(0); i < reseau.size(); ++i) {							
			for (auto pic : reseau[i]->accesPasTempsPics()){			//affiche les pics
				std::cout << pic << "  ";
			}
			std::cout << std::endl;
			delete reseau[i];											//libère la mémoire des pointeurs alloués dynamiquement
	}
}


void Reseau::evolue(int pasCourant, int pasFinal, double Iext) {	
	assert(pasCourant < pasFinal);
	while (pasCourant < pasFinal) {										//boucle jusqu'au temps final
		/*for (size_t i (0); i < reseau.size() ; ++i) {
			
			occurPic = reseau[i]->evolue(h, tempsCourant, Iext);
			if (occurPic) {
				for (size_t j(i+1); j < reseau.size(); ++j) {
					reseau[j]->recoit(h, tempsCourant, Iext, TensionJ);
				}
			}
		}*/
		for (size_t i (0); i < tailleReseau ; ++i) {
			assert (reseau[i] != nullptr);
			if (reseau[i]->evolue(pasCourant, Iext)) {					//s'il y a un pic, réaliser ce qui suit
				for (size_t j (0) ; j < tailleReseau ; ++j) {
					if (i != j) {										//ATTENTION POSER QUESTION//_________
						for (int k(0); k < relations[i][j]; ++k) {
							if (reseau[i]->accesNature() == Excitateur) {
								reseau[j]->recoit(TensionJe);			//transmet le pic selon sa nature
							} else {
								reseau[j]->recoit(TensionJi);
							}
						}
					}
				}
			}
				/*for (size_t j(0); j < reseau[i]->accesChargeables().size(); ++j) {
					assert(reseau[i]->accesChargeables()[j] != nullptr);
					
					reseau[i]->accesChargeables()[j]->recoit(h, pasCourant, Iext, TensionJ);
				}*/
		}
		pasCourant += h;												//incremente le temps
		std::cout << pasCourant << "    ";
		for (auto neur : reseau) {										//affiche le potentiel membranaire
			std::cout << neur->accesPotMemb() << "    " ; 			
		}
		std::cout << std::endl;
	}
}
		//std::cerr << "bien"<< std::endl;
		/*
		occurPic = (reseau[0])->evolue(h, tempsCourant, Iext);
		if (occurPic) {
			for (size_t j(1); j < reseau.size(); ++j) {
				(reseau[j])->recoit(h, tempsCourant, Iext, TensionJ);
			}
		}
		occurPic = (reseau[1])->evolue(h, tempsCourant, 0);
		if (occurPic) {
			for (size_t j(2); j < reseau.size(); ++j) {
				(reseau[j])->recoit(h, tempsCourant, Iext, TensionJ);
			}
		}*/

