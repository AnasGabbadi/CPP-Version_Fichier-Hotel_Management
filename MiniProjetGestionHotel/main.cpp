#include <iostream>
#include "class.h"

using namespace std;

int main() {
    Client client;

    int choix;
    do {
        cout << "\nMenu :\n";
        cout << "1. Ajouter un client\n";
        cout << "2. Afficher les clients\n";
        cout << "0. Quitter\n";
        cout << "Choix : ";
        cin >> choix;

        switch (choix) {
        case 1: {
            string CIN ,nom, prenom, tel;
            cout << "CIN : ";
            cin >> CIN;
            cout << "Nom : ";
            cin >> nom;
            cout << "Prenom : ";
            cin >> prenom;
            cout << "Tel : ";
            cin >> tel;
            client.ajouterClient(CIN, nom, prenom, tel);
            break;
        }
        case 2:
            client.afficherClients();
            break;
        case 0:
            cout << "Au revoir !" << endl;
            break;
        default:
            cout << "Choix invalide !" << endl;
        }
    } while (choix != 0);

    return 0;
}
