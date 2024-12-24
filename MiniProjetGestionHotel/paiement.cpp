#include "paiement.h"
#include "client.h"

bool Paiement::clientAReservation(int client_id) {
    ifstream file("reservations.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Client ID : " + to_string(client_id)) != string::npos) {
                return true; 
            }
        }
        file.close();
    }
    return false;
}

void Paiement::ajouterPaiement(int client_id, double Montant_Total, string Montant_Payer, string Date_Paiement) {
    if (!clientAReservation(client_id)) {
        cout << "Le client n'a pas de reservation valide. Impossible d'ajouter le paiement." << endl;
        return;
    }

    int paiement_id = genererId("paiements.txt");
    ofstream file("paiements.txt", ios::app);
    if (file.is_open()) {
        file << "ID : " << paiement_id << " , "
            << "Client ID : " << client_id << " , "
            << "Montant Total : " << Montant_Total << " , "
            << "Montant Payer : " << Montant_Payer << " , "
            << "Date Paiement : " << Date_Paiement << endl;
        file.close();
        cout << "Paiement ajoute avec succès. ID = " << paiement_id << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier paiements.txt" << endl;
    }
}

void Paiement::afficherPaiement() {
    ifstream file("paiements.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier paiements.txt" << endl;
    }
}

void Paiement::modifierPaiement(int paiement_id, int client_id, double Montant_Total, string Montant_Payer, string Date_Paiement) {
    vector<string> lignes;
    ifstream file_in("paiements.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(paiement_id)) != string::npos) {
                ostringstream modifiedLine;
                modifiedLine << "ID : " << paiement_id << " , "
                    << "Client ID : " << client_id << " , "
                    << "Montant Total : " << Montant_Total << " , "
                    << "Montant Payer : " << Montant_Payer << " , "
                    << "Date Paiement : " << Date_Paiement;
                lignes.push_back(modifiedLine.str());
                found = true;
            }
            else {
                lignes.push_back(line);
            }
        }
        file_in.close();

        ofstream file_out("paiements.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Paiement modifie avec succès. ID = " << paiement_id << endl;
        else
            cout << "Paiement avec ID " << paiement_id << " non trouve." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier paiements.txt" << endl;
    }
}

void Paiement::supprimerPaiement(int paiement_id) {
    vector<string> lignes;
    ifstream file_in("paiements.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(paiement_id)) == string::npos) {
                lignes.push_back(line);
            }
            else {
                found = true;
            }
        }
        file_in.close();

        ofstream file_out("paiements.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Paiement supprime avec succès. ID = " << paiement_id << endl;
        else
            cout << "Paiement avec ID " << paiement_id << " non trouve." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier paiements.txt" << endl;
    }
}

void Paiement::gestionPaiement(Paiement paiement) {
    int choix;
    Client client;

    do {
        cout << "-------------------------" << endl;
        cout << "Gestion des Paiements" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Ajouter un paiement\n";
        cout << "2. Afficher les paiements\n";
        cout << "3. Modifier un paiement\n";
        cout << "4. Supprimer un paiement\n";
        cout << "5. Quitter\n";
        cout << "-------------------------" << endl;
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();
        cout << "-----------------" << endl;

        switch (choix) {
        case 1: {
            int client_id;
            double Montant_Total;
            string Montant_Payer, Date_Paiement;
            cout << "Liste des clients : " << endl;
            client.afficherClients();
            cout << "Entrez l'ID du client : ";
            cin >> client_id;
            cout << "Entrez le montant total : ";
            cin >> Montant_Total;
            cout << "Entrez le montant paye : ";
            cin >> Montant_Payer;
            cout << "Entrez la date de paiement (AAAA-MM-JJ) : ";
            cin >> Date_Paiement;
            paiement.ajouterPaiement(client_id, Montant_Total, Montant_Payer, Date_Paiement);
            break;
        }
        case 2:
            cout << "Liste des paiements : " << endl;
            paiement.afficherPaiement();
            break;
        case 3: {
            int paiement_id, client_id;
            double Montant_Total;
            string Montant_Payer, Date_Paiement;
            cout << "Liste des paiements : " << endl;
            paiement.afficherPaiement();
            cout << "Entrez l'ID du paiement a modifier : ";
            cin >> paiement_id;
            cout << "Entrez le nouvel ID du client : ";
            cin >> client_id;
            cout << "Entrez le montant total : ";
            cin >> Montant_Total;
            cout << "Entrez le montant paye : ";
            cin >> Montant_Payer;
            cout << "Entrez la date de paiement (AAAA-MM-JJ) : ";
            cin >> Date_Paiement;
            paiement.modifierPaiement(paiement_id, client_id, Montant_Total, Montant_Payer, Date_Paiement);
            break;
        }
        case 4: {
            int paiement_id;
            cout << "Liste des paiements : " << endl;
            paiement.afficherPaiement();
            cout << "Entrez l'ID du paiement a supprimer : ";
            cin >> paiement_id;
            paiement.supprimerPaiement(paiement_id);
            break;
        }
        case 5:
            cout << "Quitter le menu de gestion des paiements.\n";
            break;
        default:
            cout << "Choix invalide. Veuillez reessayer.\n";
        }
    } while (choix != 5);
}

int Paiement::genererId(string filename) {
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