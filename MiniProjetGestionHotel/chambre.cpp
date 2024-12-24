#include "chambre.h"

void Chambre::ajouterChambre(string numeroChambre, string type, double PrixParNuit) {
    ofstream file("chambres.txt", ios::app);
    int chambre_id = genererId("chambres.txt");
    if (file.is_open()) {
        file << "ID : " << chambre_id << " , "
            << "Numero : " << numeroChambre << " , "
            << "Type : " << type << " , "
            << "Prix Par Nuit : " << PrixParNuit << endl;
        file.close();
        cout << "Chambre ajoutee avec succes : ID = " << chambre_id << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier chambres.txt" << endl;
    }
}

void Chambre::afficherChambre() {
    ifstream file("chambres.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier chambres.txt" << endl;
    }
}

void Chambre::modifierChambre(int chambre_id, string numeroChambre, string type, double PrixParNuit) {
    vector<string> lignes;
    ifstream file_in("chambres.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(chambre_id)) != string::npos) {
                ostringstream modifiedLine;
                modifiedLine << "ID : " << chambre_id
                    << " , Numero : " << numeroChambre
                    << " , Type : " << type
                    << " , Prix Par Nuit : " << PrixParNuit;
                lignes.push_back(modifiedLine.str());
                found = true;
            }
            else {
                lignes.push_back(line);
            }
        }
        file_in.close();

        ofstream file_out("chambres.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Chambre modifiee avec succes !" << endl;
        else
            cout << "Chambre avec ID " << chambre_id << " non trouvee." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier chambres.txt" << endl;
    }
}

void Chambre::supprimerChambre(int chambre_id) {
    vector<string> lignes;
    ifstream file_in("chambres.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(chambre_id)) == string::npos) {
                lignes.push_back(line);
            }
            else {
                found = true;
            }
        }
        file_in.close();

        ofstream file_out("chambres.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Chambre avec ID " << chambre_id << " supprimee avec succes !" << endl;
        else
            cout << "Chambre avec ID " << chambre_id << " non trouvee." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier chambres.txt" << endl;
    }
}

void Chambre::gestionChambre(Chambre chambre) {
    int choix;
    do {
        cout << "-----------------" << endl;
        cout << " Gestion des Chambres" << endl;
        cout << "-----------------" << endl;
        cout << "1. Ajouter une chambre" << endl;
        cout << "2. Afficher les chambres" << endl;
        cout << "3. Modifier une chambre" << endl;
        cout << "4. Supprimer une chambre" << endl;
        cout << "0. Retour au menu principal" << endl;
        cout << "-----------------" << endl;
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();
        cout << "-----------------" << endl;

        switch (choix) {
        case 1: {
            int chambre_id;
            string numeroChambre, type;
            double PrixParNuit;
            cout << "Ajout d'une nouvelle chambre : " << endl;
            cout << "Numero de la chambre : ";
            cin >> numeroChambre;
            cout << "Type : ";
            cin >> type;
            cout << "Prix par nuit : ";
            cin >> PrixParNuit;
            chambre_id = chambre.genererId("chambres.txt");
            chambre.ajouterChambre(numeroChambre, type, PrixParNuit);
            break;
        }
        case 2:
            cout << "Liste des chambres : " << endl;
            chambre.afficherChambre();
            break;
        case 3: {
            int chambre_id;
            string numeroChambre, type;
            double PrixParNuit;
            cout << "Liste des chambres : " << endl;
            chambre.afficherChambre();
            cout << "-----------------" << endl;
            cout << "Entrez l'ID de la chambre à modifier : ";
            cin >> chambre_id;
            cout << "Nouveau numero de chambre : ";
            cin >> numeroChambre;
            cout << "Nouveau type : ";
            cin >> type;
            cout << "Nouveau prix par nuit : ";
            cin >> PrixParNuit;
            chambre.modifierChambre(chambre_id, numeroChambre, type, PrixParNuit);
            break;
        }
        case 4: {
            int chambre_id;
            cout << "Liste des chambres : " << endl;
            chambre.afficherChambre();
            cout << "-----------------" << endl;
            cout << "Entrez l'ID de la chambre à supprimer : ";
            cin >> chambre_id;
            chambre.supprimerChambre(chambre_id);
            break;
        }
        case 0:
            cout << "Retour au menu principal..." << endl;
            break;
        default:
            cout << "Choix invalide ! Veuillez réessayer." << endl;
        }
        cout << endl;
    } while (choix != 0);
}

int Chambre::genererId(string filename) {
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