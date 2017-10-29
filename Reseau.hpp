#ifndef RESEAU_HPP
#define RESEAU_HPP
#include "Neurone.hpp"
#include <iostream>
#include <vector>
#include <array>


/*!
 * @class Reseau
 * @brief Classe s'occupant des relations entre neurones 
 */

class Reseau {
	public :
		//CONSTRUCTEUR, DESTRUCTEUR
			/*!
		 * @brief Constructeur du réseau
		 */
		 Reseau();
				/*!
		 * @brief Destructeur du réseau
		 */
		~Reseau();
		//Reseau(std::array<Neurone*, tailleReseau>);
		//METHODE PUBLIQUE
				/*!
		 * @brief Méthode principale de la classe, modélisant indirectement l'évolution des potentiels membranaires 
		 * @param pasInitial, le pas de temps de départ de la simulation
		 * @param pasFinal, le pas de temps final de la simulation
		 * @param Iext, le courant externe
		 */
		void evolue(int pasInitial, int pasFinal, double Iext);
	private :
		//ATTRIBUTS
		std::array<Neurone*, tailleReseau> reseau;								///< le tableau de pointeurs sur les neurones composant le réseau
		std::array<std::array<size_t, tailleReseau>, tailleReseau> relations;	///< la matrice du nombre de connexions entre neurones
};

#endif //RESEAU_HPP

