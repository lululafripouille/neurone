#include <iostream>
#include <cmath>
#include "Neurone.hpp"
#include "Reseau.hpp"
#include "gtest/include/gtest/gtest.h"

TEST (NeuronTest, MembranePotential) {
	Neurone neurone1;
	neurone1.evolue(1, 0, 1.0);
	EXPECT_EQ(20.0*(1.0-std::exp(-0.1/20.0)), neurone1.accesPotMemb());
}

TEST (NeuronTest, SpikeTimes) {
	Neurone neurone2;
	//std::vector<Neurone*> neurones = {&neurone2};
	Reseau reseau2 ({&neurone2});
	reseau2.evolue(1.01, 0, 1000, 1);
	EXPECT_EQ(924, neurone2.accesPasTempsPics()[0]);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
