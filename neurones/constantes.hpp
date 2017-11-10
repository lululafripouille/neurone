#include <cmath>

#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP


constexpr double resistance (20);				///< la resistance de la membrane
constexpr double capacite (1);					///< la capacite de la membrane
constexpr double seuil (20);					///< le seuil du pic
constexpr double Decalage (1.5);				///< le décalage entre le pic et l'addition de la tension dans l'autre neurone en ms
constexpr int tailleTampon(16);					///< la taille du tampon
constexpr int h (1);							///< le pas de temps (correspond à 1/10 ms)
constexpr double TensionJe (0.1);				///< la tension transmises par des neurones excitateurs
constexpr int teta (20);						///< le facteur teta, non utilisé dans la dernieère conception
constexpr double e (0.1);						///< le rapport entre excitateurs et inhibiteurs
constexpr int nombreExcitateurs (10000);		///< le nombre de neurones excitateurs
constexpr int tauRefractaire(20);				///< le pas de temps durant lequel le neurone reste réfractaire
constexpr int pasFinal(12005);					///< le pas de temps final
constexpr double eta(4);						///< le facteur eta, lien entre nuSeuil et nuExt
constexpr double g(6);							///< le facteur g, lien entre Je et Ji

const double TensionJi (-g*TensionJe);			///< la tension transmises par des neurones inhibiteurs	
const double tau (resistance * capacite);		///< la constante temporelle membranaire
const double c1 (exp(-(h/10.0)/tau));			///<une constante, inutile de la recalculer à chaque fois
const double c2 (1-c1);							///<une constante, inutile de la recalculer à chaque fois
const int nombreInhibiteurs (0.25 * nombreExcitateurs); ///< le nombre de neurones inhibiteurs
const int ConnexionExcitatrices (e * nombreExcitateurs);///< le nombre de connexions excitatrices
const int ConnexionInhibitrices (e * nombreInhibiteurs);///< le nombre de connexions inhibitrices
const int nombreConnexions (ConnexionExcitatrices+ConnexionInhibitrices);///<le nombre de connexions
const double nuSeuil (seuil/(TensionJe*tau));	///< seuil du facteur de fréquence des pics aléatoires
const double nuExt (eta*nuSeuil);				///< facteur de fréquence des pics aléatoires
const double nuExtParPas(nuExt/10);				///< facteur de fréquence des pics aléatoires par pas
const int tailleReseau (nombreExcitateurs + nombreInhibiteurs);///< la taille du réseau, en nombre de neurones


#endif //CONSTANTES_HPP
