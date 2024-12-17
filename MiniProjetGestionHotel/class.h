#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Client {
public:
    void ajouterClient(string CIN, string nom, string prenom, string tel) {
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

    void modifierClient(string CIN, string newNom, string newPrenom, string newTel) {
        vector<string> lignes;
        ifstream file_in("clients.txt");
        bool found = false;

        if (file_in.is_open()) {
            string line;
            while (getline(file_in, line)) {
                if (line.find(CIN) != string::npos) { 
                    ostringstream modifiedLine;
                    modifiedLine << CIN << ",Nom:" << newNom << ",Prenom:" << newPrenom << ",Tel:" << newTel;
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
                cout << "Client avec CIN " << CIN << " non trouve." << endl;
        }
        else {
            cerr << "Erreur : Impossible d'ouvrir le fichier clients.txt" << endl;
        }
    }

    void supprimerClient(string CIN) {
        vector<string> lignes;
        ifstream file_in("clients.txt");
        bool found = false;

        if (file_in.is_open()) {
            string line;
            while (getline(file_in, line)) {
                if (line.find(CIN) == string::npos) {
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
                cout << "Client supprime avec succes !" << endl;
            else
                cout << "Client avec CIN " << CIN << " non trouve." << endl;
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