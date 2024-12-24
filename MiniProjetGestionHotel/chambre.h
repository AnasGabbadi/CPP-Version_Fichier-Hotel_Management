#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Chambre {
public:
    void ajouterChambre(string numeroChambre, string type, double PrixParNuit);
    void afficherChambre();
    void modifierChambre(int chambre_id, string numeroChambre, string type, double PrixParNuit);
    void supprimerChambre(int chambre_id);
    void gestionChambre(Chambre chambre);
private:
    int genererId(string filename);
};