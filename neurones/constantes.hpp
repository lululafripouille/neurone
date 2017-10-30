#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP


constexpr double resistance (20);				///< la resistance de la membrane
constexpr double capacite (1);					///< la capacite de la membrane
constexpr double seuil (20);					///< le seuil du pic
constexpr double Decalage (1.5);				///< le décalage entre le pic et l'addition de la tension dans l'autre neurone en ms
constexpr int tailleTampon(16);					///< la taille du tampon
constexpr int h (1);							///< le pas de temps (correspond à 1/10 ms)
constexpr double TensionJe (0.1);				///< la tension transmises par des neurones excitateurs
constexpr double TensionJi (-0.5);				///< la tension transmises par des neurones inhibiteurs	
constexpr int teta (20);						//??
constexpr double e (0.1);						///< le rapport entre excitateurs et inhibiteurs
constexpr int nombreExcitateurs (3500);			///< le nombre de neurones excitateurs
constexpr int tauRefractaire(2);				///< le pas de temps durant lequel le neurone reste réfractaire
constexpr int pasFinal(1000);					///< le pas de temps final

const double tau (resistance * capacite);		//?
const double c1 (exp(-(h/10.0)/tau));			///<une constante
const double c2 (1-c1);							///<une constante
const int nombreInhibiteurs (0.25 * nombreExcitateurs); ///< le nombre de neurones inhibiteurs
const int ConnexionExcitatrices (e * nombreExcitateurs);///< le nombre de connexions excitatrices
const int ConnexionInhibitrices (e * nombreInhibiteurs);///< le nombre de connexions inhibitrices
const int nombreConnexions (ConnexionExcitatrices+ConnexionInhibitrices);///<le nombre de connexions
const double nu_seuil (teta/(ConnexionExcitatrices * TensionJe * tau));//?
const double nu (2*nu_seuil);					//?
const int tailleReseau (nombreExcitateurs + nombreInhibiteurs);///< la taille du réseau, en nombre de neurones


#endif //CONSTANTES_HPP
