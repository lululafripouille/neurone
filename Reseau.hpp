#ifndef RESEAU_HPP
#define RESEAU_HPP
#include "Neurone.hpp"
#include <iostream>
#include <vector>
#include <array>

constexpr double TensionJ (0.1);
constexpr size_t tailleReseau (10);

class Reseau {
	public :
		Reseau(std::vector<Neurone*>);
		void evolue(double Iext, int pasCourant, int pasFinal, int h);
	private :
		std::vector<Neurone*> reseau;
		bool occurPic;
		std::array<std::array<bool, tailleReseau>, tailleReseau> relations;
};

#endif //RESEAU_HPP

