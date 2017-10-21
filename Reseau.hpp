#ifndef RESEAU_HPP
#define RESEAU_HPP
#include "Neurone.hpp"
#include <iostream>
#include <vector>

constexpr double TensionJ (0.1);

class Reseau {
	public :
		Reseau(std::vector<Neurone*>);
		void evolue(double Iext, int pasCourant, int pasFinal, int h);
	private :
		std::vector<Neurone*> reseau;
		bool occurPic;
};

#endif //RESEAU_HPP

