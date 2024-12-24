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

class Reservation {
public:
    void ajouterReservation(int client_id, int chambre_id, string dateArrivee, string dateDepart);
    void afficherReservation();
    void modifierReservation(int reservation_id, int client_id, int chambre_id, string dateArrivee, string dateDepart);
    void supprimerReservation(int reservation_id);
    void afficherCalendrier(int chambre_id);
    void gestionReservation(Reservation reservation);
private:
    int genererId(string filename);
    bool estDisponible(int chambre_id, string dateArrivee, string dateDepart);
    vector<string> genererPlageDates(string dateDebut, string dateFin);

    map<int, set<string>> calendrier;
};