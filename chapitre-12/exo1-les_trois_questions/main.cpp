
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int k;
    string word;

    cin >> word >> k;

    vector<string> untouchables(k);

    for (int i = 0; i < k; i++) {
        cin >> untouchables[i];
    }

    int n;
    cin >> n;

    int purs = 0;
    int aRevoir = 0;
    int filetsAPoser = 0;

    vector<string> prets;

    for (int i = 0; i < n; i++) {
        string nom;
        int b, t, e;

        cin >> nom >> b;

        vector<string> besoins(b);

        for (int j = 0; j < b; j++) {
            cin >> besoins[j];
        }

        cin >> t;

        vector<string> parties(t);

        for (int j = 0; j < t; j++) {
            cin >> parties[j];
        }

        cin >> e;

        string lieu;

        bool glue = false;
        bool decouper = false;

        for (const string& besoin : besoins) {
            if (besoin == "FENETRE" ||
                besoin == "SOURIS" ||
                besoin == "CLAVIER" ||
                besoin == "GPU") {
                glue = true;
            }

            if (besoin == "DISQUE" ||
                besoin == "HORLOGE" ||
                besoin == "RESEAU") {
                decouper = true;
            }
        }

        if (glue) {
            lieu = "GLUE";
        } else if (decouper) {
            lieu = "DECOUPER";
        } else {
            lieu = "FICHIER_PUR";
            purs++;
        }

        string touche = "INTACT";

        for (const string& partie : parties) {
            if (find(untouchables.begin(),
                     untouchables.end(),
                     partie) != untouchables.end()) {
                touche = "REVOIR " + partie;
                aRevoir++;
                break;
            }
        }

        string filet;

        if (e == 0) {
            filet = "FILET_D_ABORD";
            filetsAPoser++;
        } else {
            filet = "FILET_EXISTANT";
        }

        cout << nom << " " << lieu << " "
             << touche << " " << filet << '\n';

        if (touche == "INTACT" && e > 0) {
            prets.push_back(nom);
        }
    }

    cout << "PURS " << purs << '\n';
    cout << "A_REVOIR " << aRevoir << '\n';
    cout << "FILETS_A_POSER " << filetsAPoser << '\n';

    cout << "PRETS";

    if (prets.empty()) {
        cout << " AUCUN";
    } else {
        for (const string& nom : prets) {
            cout << " " << nom;
        }
    }

    cout << '\n';

    return 0;
}
