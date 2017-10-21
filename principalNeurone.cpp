#include <iostream>
//#include "Neurone.cpp"
#include "Reseau.cpp"
 
constexpr double h (1);

int main () {
	double Iext (0);
	double tempsCourant (0);
	double tempsFinal (0);
	
	Neurone neur;
	
	std::cout << neur.accesPotMemb();
	std::cout << "Entrez le temps final !!" << std::endl;
	std::cin >> tempsFinal;
	std::cout << "Entrez le courant externe !!" << std::endl;
	std::cin >> Iext;
	while(tempsCourant < tempsFinal) {
		neur.evolue(h, tempsCourant, Iext);
		tempsCourant += h;
		std::cout << tempsCourant << "    ";
		std::cout << neur.accesPotMemb() << std::endl;
	}
}
