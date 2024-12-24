#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <ctime>
#include <iomanip>
#include <map>

using namespace std;

class Paiement {
public:
    void ajouterPaiement(int client_id, double Montant_Total, string Montant_Payer, string Date_Paiement);
    void afficherPaiement();
    void modifierPaiement(int paiement_id, int client_id, double Montant_Total, string Montant_Payer, string Date_Paiement);
    void supprimerPaiement(int paiement_id);
    void gestionPaiement(Paiement paiement);
private:
    int genererId(string filename);
    bool clientAReservation(int client_id);
};