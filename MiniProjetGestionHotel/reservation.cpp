#include "reservation.h"
#include "client.h"
#include "chambre.h"

void Reservation::ajouterReservation(int client_id, int chambre_id, string dateArrivee, string dateDepart) {
    if (!estDisponible(chambre_id, dateArrivee, dateDepart)) {
        cout << "Erreur : La chambre " << chambre_id << " n'est pas disponible pour les dates demandees." << endl;
        return;
    }

    int reservation_id = genererId("reservations.txt");
    ofstream file("reservations.txt", ios::app);
    if (file.is_open()) {
        file << "ID : " << reservation_id << " , "
            << "Client ID : " << client_id << " , "
            << "Chambre ID : " << chambre_id << " , "
            << "Date Arrivee : " << dateArrivee << " , "
            << "Date Depart : " << dateDepart << endl;
        file.close();
        cout << "Reservation ajoutee avec succes. ID = " << reservation_id << endl;

        vector<string> dates = genererPlageDates(dateArrivee, dateDepart);
        for (const string& date : dates) {
            calendrier[chambre_id].insert(date);
        }
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier reservations.txt" << endl;
    }
}

void Reservation::afficherReservation() {
    ifstream file("reservations.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier reservations.txt" << endl;
    }
}

void Reservation::modifierReservation(int reservation_id, int client_id, int chambre_id, string dateArrivee, string dateDepart) {
    vector<string> lignes;
    ifstream file_in("reservations.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(reservation_id)) != string::npos) {
                ostringstream modifiedLine;
                modifiedLine << "ID : " << reservation_id << " , "
                    << "Client ID : " << client_id << " , "
                    << "Chambre ID : " << chambre_id << " , "
                    << "Date Arrivee : " << dateArrivee << " , "
                    << "Date Depart : " << dateDepart;
                lignes.push_back(modifiedLine.str());
                found = true;
            }
            else {
                lignes.push_back(line);
            }
        }
        file_in.close();

        ofstream file_out("reservations.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Reservation modifiee avec succes. ID = " << reservation_id << endl;
        else
            cout << "Reservation avec ID " << reservation_id << " non trouvee." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier reservations.txt" << endl;
    }
}

void Reservation::supprimerReservation(int reservation_id) {
    vector<string> lignes;
    ifstream file_in("reservations.txt");
    bool found = false;

    if (file_in.is_open()) {
        string line;
        while (getline(file_in, line)) {
            if (line.find("ID : " + to_string(reservation_id)) == string::npos) {
                lignes.push_back(line);
            }
            else {
                found = true;
            }
        }
        file_in.close();

        ofstream file_out("reservations.txt", ios::trunc);
        for (const string& l : lignes) {
            file_out << l << endl;
        }
        file_out.close();

        if (found)
            cout << "Reservation supprimee avec succes. ID = " << reservation_id << endl;
        else
            cout << "Reservation avec ID " << reservation_id << " non trouvee." << endl;
    }
    else {
        cerr << "Erreur : Impossible d'ouvrir le fichier reservations.txt" << endl;
    }
}

void Reservation::afficherCalendrier(int chambre_id) {
    if (calendrier.find(chambre_id) == calendrier.end() || calendrier[chambre_id].empty()) {
        cout << "La chambre " << chambre_id << " est disponible tous les jours." << endl;
        return;
    }

    cout << "Calendrier pour la chambre " << chambre_id << " : " << endl;
    for (const string& date : calendrier[chambre_id]) {
        cout << "Reservee: " << date << endl;
    }
}

bool Reservation::estDisponible(int chambre_id, string dateArrivee, string dateDepart) {
    vector<string> datesDemandees = genererPlageDates(dateArrivee, dateDepart);

    for (const string& date : datesDemandees) {
        if (calendrier[chambre_id].find(date) != calendrier[chambre_id].end()) {
            return false;
        }
    }
    return true;
}

vector<string> Reservation::genererPlageDates(string dateDebut, string dateFin) {
    vector<string> dates;
    tm tmDebut = {}, tmFin = {};
    istringstream ssDebut(dateDebut), ssFin(dateFin);

    ssDebut >> get_time(&tmDebut, "%Y-%m-%d");
    ssFin >> get_time(&tmFin, "%Y-%m-%d");

    time_t timeDebut = mktime(&tmDebut);
    time_t timeFin = mktime(&tmFin);

    while (timeDebut <= timeFin) {
        tm current;
        localtime_s(&current, &timeDebut);
        ostringstream oss;
        oss << put_time(&current, "%Y-%m-%d");
        dates.push_back(oss.str());

        timeDebut += 86400;
    }

    return dates;
}

void Reservation::gestionReservation(Reservation reservation) {
    Client client;
    Chambre chambre;

    int choix;
    do {
        cout << "-------------------------" << endl;
        cout << "Gestion des Reservations" << endl;
        cout << "-------------------------" << endl;
        cout << "1. Ajouter une reservation\n";
        cout << "2. Afficher les reservations\n";
        cout << "3. Modifier une reservation\n";
        cout << "4. Supprimer une reservation\n";
        cout << "5. Afficher le calendrier d'une chambre\n";
        cout << "6. Quitter\n";
        cout << "-------------------------" << endl;
        cout << "Choix : ";
        cin >> choix;
        cin.ignore();
        cout << "-----------------" << endl;

        switch (choix) {
        case 1: {
            int client_id, chambre_id;
            string dateArrivee, dateDepart;
            cout << "Liste des clients : " << endl;
            client.afficherClients();
            cout << "Entrez l'ID du client : ";
            cin >> client_id;
            cout << "Liste des chambres : " << endl;
            chambre.afficherChambre();
            cout << "Entrez l'ID de la chambre : ";
            cin >> chambre_id;
            cout << "Entrez la date d'arrivee (AAAA-MM-JJ) : ";
            cin >> dateArrivee;
            cout << "Entrez la date de depart (AAAA-MM-JJ) : ";
            cin >> dateDepart;
            ajouterReservation(client_id, chambre_id, dateArrivee, dateDepart);
            break;
        }
        case 2:
            cout << "Liste des reservations : " << endl;
            afficherReservation();
            break;
        case 3: {
            int reservation_id, client_id, chambre_id;
            string dateArrivee, dateDepart;
            cout << "Liste des reservations : " << endl;
            afficherReservation();
            cout << "Entrez l'ID de la reservation a modifier : ";
            cin >> reservation_id;
            cout << "Entrez le nouvel ID du client : ";
            cin >> client_id;
            cout << "Entrez le nouvel ID de la chambre : ";
            cin >> chambre_id;
            cout << "Entrez la nouvelle date d'arrivee (AAAA-MM-JJ) : ";
            cin >> dateArrivee;
            cout << "Entrez la nouvelle date de depart (AAAA-MM-JJ) : ";
            cin >> dateDepart;
            modifierReservation(reservation_id, client_id, chambre_id, dateArrivee, dateDepart);
            break;
        }
        case 4: {
            int reservation_id;
            cout << "Liste des reservations : " << endl;
            afficherReservation();
            cout << "Entrez l'ID de la reservation a supprimer : ";
            cin >> reservation_id;
            supprimerReservation(reservation_id);
            break;
        }
        case 5: {
            int chambre_id;
            cout << "Liste des chambres : " << endl;
            chambre.afficherChambre();
            cout << "Entrez l'ID de la chambre : ";
            cin >> chambre_id;
            afficherCalendrier(chambre_id);
            break;
        }
        case 6:
            cout << "Quitter le menu de gestion des reservations.\n";
            break;
        default:
            cout << "Choix invalide. Veuillez reessayer.\n";
        }
    } while (choix != 6);
}

int Reservation::genererId(string filename) {
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
