#ifndef RESEAU_HPP
#define RESEAU_HPP
#include "Neurone.hpp"
#include <iostream>
#include <vector>
#include <array>
#include "constantes.hpp"

/*!
 * @class Reseau
 * @brief Classe s'occupant des relations entre neurones 
 */

class Reseau {
	public :
		//CONSTRUCTEUR, DESTRUCTEUR_____________________________________
			/*!
		 * @brief Constructeur du réseau
		 */
		 Reseau();
				/*!
		 * @brief Destructeur du réseau
		 */
		~Reseau();
		//Reseau(std::array<Neurone*, tailleReseau>);
		//METHODES PUBLIQUES____________________________________________
				/*!
		 * @brief accesseur au nombre moyen de pics par neurone par seconde
		 * @return le nombre moyen de pics par neurone par seconde
		 */
		int accesMoyennePicsParNeuroneParSec();
				/*!
		 * @brief accesseur à la case du tableau des relations entre neurones
		 * @return l'index du neurone de la table de relations de ligne ligne_ et de colonne colonne_
		 */
		int accesCaseRelations (int ligne_, int colonne_);

				/*!
		 * @brief Méthode principale de la classe, modélisant indirectement l'évolution des potentiels membranaires 
		 * @param pasInitial, le pas de temps de départ de la simulation
		 * @param pasFinal, le pas de temps final de la simulation
		 * @param Iext, le courant externe
		 * @param poisson, la présence de pics provenant du reste du cerveau, générés par Poisson
		 */
		void evolue(int pasInitial, double Iext, bool poisson);
	private :
		//ATTRIBUTS_____________________________________________________
		std::array<Neurone*, tailleReseau> reseau;						///< le tableau de pointeurs sur les neurones composant le réseau
		std::vector<std::array<unsigned short int, nombreConnexions>> relations;///< la matrice du nombre de connexions entre neurones
		std::array<int, pasFinal> tableauAImprimer;						///< tableau pour pics totaux par pas de temps
		double moyennePicsParNeuroneParSeconde;							///< la moyenne du nombre de pics par neurone par seconde
};

#endif //RESEAU_HPP

