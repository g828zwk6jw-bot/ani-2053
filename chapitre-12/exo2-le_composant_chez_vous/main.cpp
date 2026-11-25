
#include <iostream>
#include <string>

using namespace std;

int main() {
    long long intervalle;
    string document;
    string mot;

    cin >> mot >> intervalle;
    cin >> mot >> document;

    if (document == "-") {
        document = "planche-sans-nom.nkref";
    }

    string secoursNom = document + ".auto";

    long long temps = 0;
    long long elapsed = 0;

    bool changed = false;
    bool disqueOK = true;

    int sauvegardes = 0;
    int echecs = 0;

    string commande;

    while (cin >> commande) {
        if (commande == "TOUCH") {
            changed = true;
        }
        else if (commande == "TICK") {
            long long d;
            cin >> d;

            if (d > 0) {
                elapsed += d;
                temps += d;
            }

            if (changed && elapsed >= intervalle) {
                if (disqueOK) {
                    cout << temps << " SECOURS\n";
                    sauvegardes++;

                    changed = false;
                    elapsed = 0;
                } else {
                    cout << temps << " ECHEC\n";
                    echecs++;
                }
            }
        }
        else if (commande == "CTRL_S") {
            if (disqueOK) {
                cout << temps << " MANUELLE\n";

                changed = false;
                elapsed = 0;
            } else {
                cout << temps << " MANUELLE_ECHEC\n";
                echecs++;
            }
        }
        else if (commande == "DISQUE") {
            string etat;
            cin >> etat;

            disqueOK = (etat == "OK");
        }
    }

    cout << "SAUVEGARDES " << sauvegardes << '\n';
    cout << "ECHECS " << echecs << '\n';

    cout << "EN_ATTENTE "
         << (changed ? "OUI" : "NON") << '\n';

    cout << "SECOURS_NOM " << secoursNom << '\n';

    return 0;
}
