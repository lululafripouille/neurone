#include <iostream>
//#include "Neurone.cpp"
#include "Reseau.hpp"
 
//constexpr double h (1);

int main () {
	double Iext (0);
	int pasCourant (0);
	//int pasFinal (0);
	/*
	Neurone neur1;
	Neurone neur2;
	
	std::vector<Neurone*> neurones = {&neur1, &neur2};
	neur1.modifieChargeables({&neur2});*/
	
	//std::cout << neur1.accesPotMemb();
	/*std::cout << "Entrez le temps final !" << std::endl;
	double v (0);
	std::cin >> v;
	pasFinal = v * 10000;*/
	/*std::cout << "Entrez le courant externe !" << std::endl;
	std::cin >> Iext;
	*/
	Reseau res;
	res.evolue(pasCourant, Iext);
	/*for (auto neur : neurones) {
		for (auto pic : neur->accesPasTempsPics()){
			std::cout << pic << std::endl;
		}
		std::cout << std::endl;
	}*/
	return 0;
}
