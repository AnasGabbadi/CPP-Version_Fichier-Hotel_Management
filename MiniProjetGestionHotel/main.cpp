#include <iostream>
#include "client.h"
#include "chambre.h"
#include "reservation.h"
#include "Paiement.h"

using namespace std;            

int main() {
    Client client;
    Chambre chambre;
    Reservation reservation;
    Paiement paiement;
    int choix;
    do {
        cout << "-----------------" << endl;
        cout << "       MENU      " << endl;
        cout << "-----------------" << endl;
        cout << "1. Gestion des clients" << endl;
        cout << "2. Gestion des chambres" << endl;
        cout << "3. Gestion des reservations" << endl;
        cout << "4. Gestion des paiements" << endl;
        cout << "0. Quitter" << endl;
        cout << "-----------------" << endl;
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();
        cout << "-----------------" << endl;

        switch (choix) {
        case 1:
            client.gestionClients(client);
            break;
        case 2:
            chambre.gestionChambre(chambre);
            break;
        case 3:
            reservation.gestionReservation(reservation);
        break;
        case 4:
            paiement.gestionPaiement(paiement);
            break;
        case 0:
            cout << "Au revoir!" << endl;
            break;
        default:
            cout << "Choix invalide. Veuillez réessayer." << endl;
        }
    } while (choix != 0);

    return 0;
}