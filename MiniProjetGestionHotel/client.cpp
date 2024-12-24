#include <iostream>
#include "client.h"

using namespace std;

void Client::ajouterClient(string CIN, string nom, string prenom, string tel) {
    ofstream file("clients.txt", ios::app);
    if (file.is_open()) {
        int client_id = genererId("clients.txt");
        file << "ID : " << client_id << " , " << "CIN : " << CIN << " , " << "Nom : " << nom << " , " << "Prenom : " << prenom << " , " << "Tel : " << tel << endl;
        file.close();
        cout << "Client ajoute avec succes : ID = " << client_id << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt" << endl;
    }
}

void Client::afficherClients() {
    ifstream file("clients.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt" << endl;
    }
}

void Client::modifierClient(int client_id, string newCIN, string newNom, string newPrenom, string newTel) {
    vector<string> lignes;
    ifstream file_in("clients.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(client_id)) != string::npos) {
                ostringstream modifiedLine;
                modifiedLine << "ID : " << client_id
                    << " , CIN : " << newCIN
                    << " , Nom : " << newNom
                    << " , Prenom : " << newPrenom
                    << " , Tel : " << newTel;
                lignes.push_back(modifiedLine.str());
                found = true;
            }
            else {
                lignes.push_back(line);
            }
        }
        file_in.close();

        ofstream file_out("clients.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Client modifie avec succes !" << endl;
        else
            cout << "Client avec ID " << client_id << " non trouve." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt" << endl;
    }
}

void Client::supprimerClient(int client_id) {
    vector<string> lignes;
    ifstream file_in("clients.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(client_id)) == string::npos) {
                lignes.push_back(line);
            }
            else {
                found = true;
            }
        }
        file_in.close();

        ofstream file_out("clients.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Client avec ID " << client_id << " supprime avec succes !" << endl;
        else
            cout << "Client avec ID " << client_id << " non trouve." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt" << endl;
    }
}

void Client::gestionClients(Client client) {
    int choix;
    do {
        cout << "-------------------" << endl;
        cout << "Gestion des Clients" << endl;
        cout << "-------------------" << endl;
        cout << "1. Ajouter un client" << endl;
        cout << "2. Afficher les clients" << endl;
        cout << "3. Modifier un client" << endl;
        cout << "4. Supprimer un client" << endl;
        cout << "0. Retour au menu principal" << endl;
        cout << "-----------------" << endl;
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();
        cout << "-----------------" << endl;

        switch (choix) {
        case 1: {
            string CIN, nom, prenom, tel;
            cout << "Ajout d'un nouveau client : " << endl;
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
            cout << "Liste des clients : " << endl;
            client.afficherClients();
            break;
        case 3: {
            string newCIN, newNom, newPrenom, newTel;
            int client_id;
            cout << "Liste des clients : " << endl;
            client.afficherClients();
            cout << "-----------------" << endl;
            cout << "Entrez l'ID du client a modifier : ";
            cin >> client_id;
            cout << "Nouveau CIN : ";
            cin >> newCIN;
            cout << "Nouveau Nom : ";
            cin >> newNom;
            cout << "Nouveau Prenom : ";
            cin >> newPrenom;
            cout << "Nouveau Tel : ";
            cin >> newTel;
            client.modifierClient(client_id, newCIN, newNom, newPrenom, newTel);
            break;
        }
        case 4: {
            cout << "Liste des clients : " << endl;
            client.afficherClients();
            cout << "-----------------" << endl;
            int client_id;
            cout << "Entrez l'ID du client a supprimer : ";
            cin >> client_id;
            client.supprimerClient(client_id);
            break;
        }
        case 0:
            cout << "Retour au menu principal..." << endl;
            break;
        default:
            cout << "Choix invalide ! Veuillez reessayer." << endl;
        }
        cout << endl;
    } while (choix != 0);
}

int Client::genererId(string filename) {
    ifstream file(filename);
    int lastId = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find("ID : ");
            if (pos != string::npos) {
                size_t start = pos + 5;
                size_t end = line.find(" ,", start);
                string idStr = line.substr(start, end - start);
                lastId = stoi(idStr);
            }
        }
        file.close();
    }
    return lastId + 1;
}
