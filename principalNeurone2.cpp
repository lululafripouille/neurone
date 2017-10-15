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
	
	//std::cout << neur1.accesPotMemb();
	std::cout << "Entrez le temps final !" << std::endl;
	double v (0);
	std::cin >> v;
	tempsFinal = v * 1000;
	std::cout << "Entrez le courant externe !" << std::endl;
	std::cin >> Iext;
	res.evolue(Iext, tempsCourant, tempsFinal, h);
	for (auto neur : neurones) {
		for (auto pic : neur->accesTempsPics()){
			std::cout << pic << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}
