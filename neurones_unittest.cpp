#include <iostream>
#include <cmath>
#include <random>
#include "Neurone.hpp"
#include "Reseau.hpp"
#include "gtest/include/gtest/gtest.h"


TEST (NeuronTest, PotentielMembranaire) {
	Neurone neurone1;
	neurone1.evolue(0, 1.0, false);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neurone1.accesPotMemb());
}

TEST (NeuronTest, TempsPics) {
	Neurone neurone2;
	int a (0);
	//std::vector<Neurone*> neurones = {&neurone2};
	//Reseau reseau2 (neurones);
	//cerr<<"built"<<endl;
	for (int i (0); i < 1000 ; ++i) {
		neurone2.evolue(a, 1.01, false);
		std::cerr << neurone2.accesPotMemb() << std::endl;
		a+=1;
	}
	//cerr<<"evolved"<<endl;
	int b(neurone2.accesPasTempsPics()[0]);
	//cerr<<"a"<<endl;
	EXPECT_EQ(924, b);
}


TEST (NeuronTest, AccesALaNature) {
	bool resultat (false);
	Neurone neurone1(Inhibiteur);
	Neurone neurone2(Excitateur);
	if (neurone1.accesNature() == Inhibiteur and neurone2.accesNature() ==	Excitateur) {
		resultat = true;
	}		
	EXPECT_EQ(true, resultat);
}


TEST (NeuronTest, TableauRelations) {
	Reseau res2;
	bool fonctionne(true);
	std::random_device rd;												//pour distribution de Poisson
	std::mt19937 gen(rd());
	
	std::uniform_int_distribution<> disColonne (0, nombreConnexions-1);
	std::uniform_int_distribution<> disLigne (0, tailleReseau-1);
	
	for (int i (0); i < 100; ++i) {
		int l (disLigne(gen));
		int c (disColonne(gen));
		std::cerr << l <<"  " << c <<"  "<< res2.accesCaseRelations(l,c)<< std::endl;
		if ((c > ConnexionExcitatrices-1 and res2.accesCaseRelations(l,c) < nombreExcitateurs) or
			(c < ConnexionExcitatrices and res2.accesCaseRelations(l,c) > nombreExcitateurs-1)) {
			fonctionne = false;
			std::cerr << l <<"  " << c <<"  "<< res2.accesCaseRelations(l,c)<< std::endl;
		}
	}
	EXPECT_EQ(true, fonctionne);
}


TEST (NeuronTest, MoyennePicsParNeurone) {								//ATTENTION LE TEST N'EST INFORMATIF QUE SI 
	Reseau res1;														//LA TAILLE DU RESEAU EST SUPERIEURE A 5000 ET INFERIEURE A 20000
	int pasCourant (0);													//G EGAL A 5 ET ETA A 2 , SINON IL EST TOUJOURS VRAI
	double Iext (0.0);
	res1.evolue(pasCourant, Iext, true);
	std::cout << "   " << res1.accesMoyennePicsParNeuroneParSec();
	int dividende (1);
	if (tailleReseau > 5000 and tailleReseau < 20000 and g == 5 and eta == 2) {//ATTENTION, TECHNIQUE PEU ELEGANTE mais permet de vérifier que le nombre de pics par seconde est cohérent (entre 30 et 40 pour 12500 neurones)
		dividende = res1.accesMoyennePicsParNeuroneParSec()/25;			//travail avec des entiers, cela revient à dire accesMoyennePicsParNeuroneParSec() compris entre 25 et 50
	}
	EXPECT_EQ(1, dividende);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
