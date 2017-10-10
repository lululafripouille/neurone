#include <iostream>
//#include "Neurone.cpp"
#include "Reseau.cpp"
 
constexpr double h (1);

int main () {
	double Iext (0);
	double tempsCourant (0);
	double tempsFinal (0);
	
	Neurone neur1;
	Neurone neur2;
	std::vector<Neurone*> neurones = {&neur1, &neur2};
	Reseau res (neurones);
	
	std::cout << neur1.accesPotMemb();
	std::cout << "Entrez le temps final !!" << std::endl;
	std::cin >> tempsFinal;
	std::cout << "Entrez le courant externe !!" << std::endl;
	std::cin >> Iext;
	res.evolue(Iext, tempsCourant, tempsFinal, h);
}
