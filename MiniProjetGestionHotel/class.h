#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Client {
public:
    void ajouterClient(string CIN, string nom, string prenom, string tel) {
        ofstream file("clients.txt", ios::app); // Ouverture en mode ajout
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

    void afficherClients() {
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

private:
    int genererId(string filename) {
        ifstream file(filename);
        int lastId = 0;
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string id;
                getline(iss, id, ',');
                lastId = stoi(id);
            }
            file.close();
        }
        return lastId + 1;
    }
};