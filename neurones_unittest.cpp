#include <iostream>
#include <cmath>
#include "Neurone.hpp"
#include "Reseau.hpp"
#include "gtest/include/gtest/gtest.h"

using namespace std;

TEST (NeuronTest, MembranePotential) {
	Neurone neurone1;
	neurone1.evolue(0, 1.0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neurone1.accesPotMemb());
}

/*
TEST (NeuronTest, SpikeTimes) {
	Neurone neurone2;
	std::vector<Neurone*> neurones = {&neurone2};
	Reseau reseau2 (neurones);
	//cerr<<"built"<<endl;
	reseau2.evolue(1.01, 0, 1000, 1);
	//cerr<<"evolved"<<endl;
	int a (neurone2.accesPasTempsPics()[0]);
	//cerr<<"a"<<endl;
	EXPECT_EQ(924, a);
}*/

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
