#ifndef NEURONE_HPP
#define NEURONE_HPP

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include "constantes.hpp"

enum Nature {Excitateur, Inhibiteur};			///< nature, excitateur ou inhibiteur

/*!
 * @class Neurone
 * @brief Unite la plus petite de notre modelisation 
 */

class Neurone {
	public :
		//CONSTRUCTEURS, DESTRUCTEUR____________________________________
				/*!
		 * @brief Constructeur du neurone
		 * @param Nature du neurone
		 */
		Neurone(Nature n = Excitateur);
				/*!
		 * @brief Constructeur du neurone si la conception était autre
		 * @param Liste de neurones que l'instance courante peut charger
		 */
		Neurone(std::vector<Neurone*> charge);
				/*!
		 * @brief Destructeur du neurone
		 */
		~Neurone() = default;
				/*! 
		 * @brief Accès au potentiel membranaire
		 * @return Le potentiel membranaire
		 */
		//ACCESSEURS
		double accesPotMemb();
				/*!
		 * @brief Accès aux pas de temps auxquels les pics surviennent
		 * @return Les pas de temps auxquels les pics surviennent
		 */
		std::vector<double> accesPasTempsPics();
				/*!
		 * @brief Accès au nombre de pics
		 * @return Le nombre de pics
		 */
		size_t accesNbPics();
				/*!
		 * @brief Accès aux neurones auxquels l'instance courante peut transmettre de la tension, méthode non utilisée dans cette conception
		 * @return Les neurones auxquels l'instance courante peut transmettre de la tension
		 */
		std::vector<Neurone*> accesChargeables();
				/*!
		 * @brief Accès à la nature du neurone (excitateur ou inhibiteur)
		 * @return La nature du neurone
		 */
		Nature accesNature();
		
		//MANIPULATEUR
				/*!
		 * @brief manipulateurs modifiant les neurones auxquels l'instance courante peut transmettre de la tension
		 * @param Les neurones auxquels l'instance courante peut transmettre de la tension
		 */
		void modifieChargeables(std::vector<Neurone*> nouvCharg);
		//METHODES PUBLIQUES
				/*!
		 * @brief fonction principale de la modélisation du neurone, faisant évoluer son potentiel membranaire
		 * @param pasGlobal, le pas de temps global
		 * @param Iext, le courant externe
		 * @param poisson, la présence de pics provenant du reste du cerveau, générés par Poisson
		 * @return La présence d'un pic
		 */
		bool evolue(int pasGlobal, double Iext, bool poisson);
				/*!
		 * @brief entree d'une tension dans le tampon du neurone
		 * @param J, la tension soit Je, soit Ji
		 */
		void recoit(double const& J);
		
	private :
		//ATTRIBUTS_____________________________________________________
		double potMemb;								///< le potentiel membranaire
		std::vector<double> pics;					///< le tableau qui enregistre les pas de temps des occurences de décharges
		std::array<double,tailleTampon> tampon;		///< le tampon, utile pour modéliser le décalage entre décharge et impact
		std::vector<Neurone*> chargeables;			///< les neurones auxquels l'instance courante peut transmettre de la tension, non utilisée
		bool refractaire;							///< l'état, réfractaire ou non d'un neurone
		int horlogeRefractaire;						///< les pas de temps qu'il reste avant la fin de l'état réfractaire du neurone
		Nature nature;								///< la nature, excitateur ou inhibiteur d'un neurone
		
		//METHODES PRIVEES______________________________________________
		
				/*!
		 * @brief Gestion du déplacement des tensions dans le tampon
		 * @return La tension qui a fini son parcours dans le tampon
		 */
		double gestionTampon();
				/*!
		 * @brief gestion de l'attitude du neurone après un pic
		 * @param pasGlobal, le pas de temps courant
		 */
		void gestionPic(int pasGlobal);
				/*!
		 * @brief gestion de l'horloge correspondant au temps réfractaire et du potentiel
		 */
		void gestionRefractaire();
		//double accumulateur;
		//int pasCourant
		//std::vector<Neurone*> chargeables;
		
};

#endif //NEURONE_HPP
