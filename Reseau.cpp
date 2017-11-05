#include <cassert>
#include "Reseau.hpp"
#include <cmath>
#include <random>
#include <array>
#include <fstream>
#include <string>


Reseau::Reseau() 
	: moyennePicsParNeuroneParSeconde (0) {
		std::cout << nuExtParPas << std::endl;
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
	
	for (int i (0); i < tailleReseau; ++i) {
		std::array<unsigned short int, nombreConnexions> ligne;
		/*for (auto& carre : ligne) {
			carre = 0;													//initialise la matrice des connexions à zéro
		}*/
		for (int j(0); j < ConnexionExcitatrices ; ++j) {				//assigne une connexion à une relation selon le nombre généré par Poisson 
			int a (disExc(gen));
			assert(a >= 0);
			//ligne[a] += 1;
			ligne[j] = a; 
		}
		for (int k(0); k < ConnexionInhibitrices; ++k) {				//assigne une connexion à une relation selon le nombre généré par Poisson
			int b(disInh(gen));
			assert(b < tailleReseau);
			//ligne[b] += 1;
			ligne[k+ConnexionExcitatrices] = b;
		}
		relations.push_back(ligne);
		/*for (auto carre : ligne) {									//affiche la matrice
			std::cout << carre << "  ";
		}
		std::cout << std::endl;*/
	}
	for (auto& carre : tableauAImprimer) {
		carre = 0;														//initialise à zéro
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
			/*for (auto pasDeTempsPic : reseau[i]->accesPasTempsPics()){	//affiche les pics
				//std::cout << pic << "  ";
				//tableauAImprimer[pasDeTempsPic] += 1;
			}
			//std::cout << std::endl;*/
			delete reseau[i];											//libère la mémoire des pointeurs alloués dynamiquement
	}
}

int Reseau::accesMoyennePicsParNeuroneParSec() {
	return moyennePicsParNeuroneParSeconde;
}


int Reseau::accesCaseRelations (int ligne, int colonne) {
	assert(ligne < relations.size());
	assert(colonne < relations[ligne].size());
	return relations[ligne][colonne];
}

void Reseau::evolue(int pasCourant, double Iext, bool poisson) {	
	assert(pasCourant < pasFinal);
	std::string nomDossier ("donnee.txt");
	std::ofstream texte (nomDossier);
	while (pasCourant < pasFinal) {										//boucle jusqu'au temps final
		/*for (size_t i (0); i < reseau.size() ; ++i) {
			
			occurPic = reseau[i]->evolue(h, tempsCourant, Iext);
			if (occurPic) {
				for (size_t j(i+1); j < reseau.size(); ++j) {
					reseau[j]->recoit(h, tempsCourant, Iext, TensionJ);
				}
			}
		}*/
		/*for (size_t i (0); i < tailleReseau ; ++i) {
			assert (reseau[i] != nullptr);
			if (reseau[i]->evolue(pasCourant, Iext)) {					//s'il y a un pic, réaliser ce qui suit
				for (size_t j (0) ; j < tailleReseau ; ++j) {
					if (i != j) {										//ATTENTION POSER QUESTION//_________
						for (int k(0); k < relations[i][j]; ++k) {		//selon le nombre de liens reliant les neurones
							if (reseau[i]->accesNature() == Excitateur) {
								reseau[j]->recoit(TensionJe);			//transmet le pic selon sa nature
							} else {
								reseau[j]->recoit(TensionJi);
							}
						}
					}
				}
			}
				for (size_t j(0); j < reseau[i]->accesChargeables().size(); ++j) {
					assert(reseau[i]->accesChargeables()[j] != nullptr);
					
					reseau[i]->accesChargeables()[j]->recoit(h, pasCourant, Iext, TensionJ);
				}
		}*/
		
		for (size_t i (0); i < tailleReseau ; ++i) {
			assert (reseau[i] != nullptr);
			if (reseau[i]->evolue(pasCourant, Iext, poisson)) {			//s'il y a un pic, réaliser ce qui suit
				tableauAImprimer[pasCourant] += 1;
				moyennePicsParNeuroneParSeconde += 1;
				//if (i < 50) {
					texte << pasCourant/10.0 << '\t' << i << '\n';
				//}
				for (size_t j (0) ; j < nombreConnexions ; ++j) {
					if (i != j) {										//ATTENTION POSER QUESTION//_________
						if (reseau[i]->accesNature() == Excitateur) {
							reseau[relations[i][j]]->recoit(TensionJe);	//transmet le pic selon sa nature
						} else {
							reseau[relations[i][j]]->recoit(TensionJi);
						}
					}
				}
			}
		}
		pasCourant += h;												//incremente le temps
		/*std::cout << pasCourant << "    ";
		for (auto neur : reseau) {										//affiche le potentiel membranaire
			std::cout << neur->accesPotMemb() << "    " ; 			
		}
		std::cout << std::endl;*/
	}
	/*for (size_t i(0); i < reseau.size(); ++i) {							
		for (auto pasDeTempsPic : reseau[i]->accesPasTempsPics()){
			//std::cout << pic << "  ";
	tableauAImprimer[pasDeTempsPic] += 1;
	moyennePicsParNeuroneParSeconde += 1;
		}
	}*/
	std::cerr << "   " << moyennePicsParNeuroneParSeconde << std::endl;
	texte.close();
	moyennePicsParNeuroneParSeconde = moyennePicsParNeuroneParSeconde * 10000 / (pasFinal * tailleReseau);
	for (auto carre : tableauAImprimer) {
		std::cout << carre << std::endl;
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

