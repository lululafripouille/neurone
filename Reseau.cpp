
#include "Reseau.hpp"
#include <cmath>

Reseau::Reseau(std::vector<Neurone*> neurones) {
	reseau = neurones;
}

void Reseau::evolue(double Iext, double tempsCourant, double tempsFinal, double h) {
	while (tempsCourant < tempsFinal) {
		/*for (size_t i (0); i < reseau.size() ; ++i) {
			occurPic = (reseau[i])->evolue(h, tempsCourant, Iext);
			if (occurPic) {
				for (size_t j(i+1); j < reseau.size(); ++j) {
					(reseau[j])->recoit(h, tempsCourant, Iext, TensionJ);
				}
			}
		}*/
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
		}
		
		
		tempsCourant += h;
		std::cout << tempsCourant << "    ";
		std::cout << reseau[0]->accesPotMemb() << "    " << reseau[1]->accesPotMemb() << std::endl;
	}
}

