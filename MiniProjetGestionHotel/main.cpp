#include <iostream>
#include "class.h"  

using namespace std;

int main() {
    Client client;

    int choix;
    do {
        cout << "-----------------";
        cout << "\nMenu :\n";
        cout << "-----------------" << endl;
        cout << "1. Ajouter un client\n";
        cout << "2. Afficher les clients\n";
        cout << "3. Modifier un client\n";
        cout << "4. Supprimer un client\n";
        cout << "0. Quitter\n";
        cout << "-----------------" << endl;
        cout << "Choix : ";
        cin >> choix;
        cout << "-----------------" << endl;
        switch (choix) {
        case 1: {
            string CIN, nom, prenom, tel;
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
        case 3: {
            string CIN, newNom, newPrenom, newTel;
            client.afficherClients();
            cout << "-----------------" << endl;
            cout << "Entrez le CIN du client a modifier : ";
            cin >> CIN;
            cout << "Nouveau Nom : ";
            cin >> newNom;
            cout << "Nouveau Prenom : ";
            cin >> newPrenom;
            cout << "Nouveau Tel : ";
            cin >> newTel;
            client.modifierClient(CIN, newNom, newPrenom, newTel);
            break;
        }
        case 4: {
            client.afficherClients();
            cout << "-----------------" << endl;
            string CIN;
            cout << "Entrez le CIN du client a supprimer : ";
            cin >> CIN;
            client.supprimerClient(CIN);
            break;
        }
        case 0:
            cout << "Au revoir !" << endl;
            break;
        default:
            cout << "Choix invalide !" << endl;
        }
    } while (choix != 0);

    return 0;
}
