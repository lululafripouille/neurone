#include <cassert>
#include "Reseau.hpp"
#include <cmath>
#include <random>
#include <array>
/*
Reseau::Reseau() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution d (0.1);
	for (auto& ligne : relations) {
		for (auto& carre : ligne) {
			carre = d(gen);
			std::cout << carre;
		}
	std::cout << std::endl;
	}
	std::arra
	reseau = std::array<>
	
	
	
}*/


Reseau::Reseau(std::vector<Neurone*> neurones) {
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
	std::cout << std::endl;
	}
	std::cerr << "salut";
}

void Reseau::evolue(double Iext, int pasCourant, int pasFinal, int h) {
	//assert(tempsCourant < tempsFinal);
	while (pasCourant < pasFinal) {
		/*for (size_t i (0); i < reseau.size() ; ++i) {
			
			occurPic = reseau[i]->evolue(h, tempsCourant, Iext);
			if (occurPic) {
				for (size_t j(i+1); j < reseau.size(); ++j) {
					reseau[j]->recoit(h, tempsCourant, Iext, TensionJ);
				}
			}
		}*/
		for (size_t i (0); i < reseau.size() ; ++i) {
			assert (reseau[i] != nullptr);
			
			occurPic = reseau[i]->evolue(h, pasCourant, Iext);
			if (occurPic) {
				for (size_t j(0); j < reseau[i]->accesChargeables().size(); ++j) {
					assert(reseau[i]->accesChargeables()[j] != nullptr);
					reseau[i]->accesChargeables()[j]->recoit(h, pasCourant, Iext, TensionJ);
				}
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
		std::cout << pasCourant << "    ";
		for (auto neur : reseau) {
			std::cout << neur->accesPotMemb() << "    " ; 
		}
		std::cout << std::endl;
		pasCourant += h;
	}
}

