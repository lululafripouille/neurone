#ifndef RESEAU_HPP
#define RESEAU_HPP
#include "Neurone.cpp"
#include <iostream>
#include <vector>

constexpr double Decalage (1);
constexpr double TensionJ (5);

class Reseau {
	public :
		Reseau(std::vector<Neurone*>);
		void evolue(double Iext, double tempsCourant, double tempsFinal, double h);
	private :
		std::vector<Neurone*> reseau;
		bool occurPic;
};

#endif //RESEAU_HPP

