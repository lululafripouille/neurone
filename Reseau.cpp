#include <cassert>
#include "Reseau.hpp"
#include <cmath>

Reseau::Reseau(std::vector<Neurone*> neurones) {
	reseau = neurones;
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
		std::cout << reseau[0]->accesPotMemb() << "    " << reseau[1]->accesPotMemb() << std::endl;
		pasCourant += h;
	}
}

