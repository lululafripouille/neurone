#ifndef NEURONE_HPP
#define NEURONE_HPP

#include <iostream>
#include <vector>
#include <array>
#include <chrono>

//constexpr double tau (0.02);
constexpr double resistance (20);
constexpr double capacite (1);
constexpr double seuil (20);


class Neurone {
	public :
		Neurone();
		~Neurone();
		double accesPotMemb();
		std::vector<double> accesTempsPics();
		size_t accesNbPics();
		bool evolue(double h, double tempsGlobal, double Iext);
		void recoit(double h, double tempsCourant, double Iext, double const& J);
	private :
		double potMemb;
		std::vector<double> pics;
		std::array<double,20> tampon;
		bool refractaire;
		//double accumulateur;
		double tempsCourant;
		std::vector<Neurone*> chargeables;
		
		double gestionTampon();
};

#endif //NEURONE_HPP
