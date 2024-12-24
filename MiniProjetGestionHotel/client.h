#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Client {
public:
    void ajouterClient(string CIN, string nom, string prenom, string tel);
    void afficherClients();
    void modifierClient(int client_id, string newCIN, string newNom, string newPrenom, string newTel);
    void supprimerClient(int client_id);
    void gestionClients(Client client);
private:
    int genererId(string filename);
};