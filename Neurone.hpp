#ifndef NEURONE_HPP
#define NEURONE_HPP

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
//#include <chrono>

//constexpr double tau (0.02);
constexpr double resistance (20);
constexpr double capacite (1);
constexpr double seuil (20);
constexpr double Decalage (1.5);
constexpr int tailleTampon(16);
constexpr int h (1);
const double tau (resistance * capacite);
const double c1 (exp(-(h/10.0)/tau));
const double c2 (1-c1);

enum Nature {Excitateur, Inhibiteur};

class Neurone {
	public :
		Neurone(Nature n = Excitateur);
		Neurone(std::vector<Neurone*> charge);
		~Neurone();
		double accesPotMemb();
		std::vector<double> accesPasTempsPics();
		size_t accesNbPics();
		std::vector<Neurone*> accesChargeables();
		void modifieChargeables(std::vector<Neurone*> nouvCharg);
		bool evolue(int h, int pasGlobal, double Iext);
		void recoit(int h, int pasCourant, double Iext, double const& J);
		
	private :
		double potMemb;
		std::vector<double> pics;
		std::array<double,tailleTampon> tampon;
		std::vector<Neurone*> chargeables;
		bool refractaire;
		//double accumulateur;
		double pasCourant;
		//std::vector<Neurone*> chargeables;
		Nature nature;
		
		double gestionTampon();
};

#endif //NEURONE_HPP
