
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Component {
    long long interval = 60;
    long long elapsed = 0;
    bool changed = false;

    bool sansSalete = false;
    bool depuisModif = false;
    bool savedGardeTemps = false;
    bool savedGardeSalete = false;
    bool strict = false;
    bool zeroIgnore = false;
    bool negatifCompte = false;

    void touch() {
        changed = true;

        if (depuisModif) {
            elapsed = 0;
        }
    }

    bool tick(long long d) {
        if (zeroIgnore && d <= 0) {
            return false;
        }

        if (d > 0 || (negatifCompte && d < 0)) {
            elapsed += d;
        }

        bool condition = sansSalete || changed;

        if (strict) {
            return condition && elapsed > interval;
        }

        return condition && elapsed >= interval;
    }

    void saved() {
        if (!savedGardeSalete) {
            changed = false;
        }

        if (!savedGardeTemps) {
            elapsed = 0;
        }
    }
};

int main() {
    string line;

    int detectes = 0;
    int nonDetectes = 0;

    vector<string> angleMort;

    const string document = "D:/planches/personnages.nkref";

    while (getline(cin, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream input(line);

        string nom;
        string fault;

        input >> nom;

        Component c;

        bool faulty = false;
        bool secoursFixe = false;
        bool secoursEstDoc = false;
        bool sansNomVide = false;

        while (input >> fault) {
            if (fault == "AUCUN") {
                break;
            }

            faulty = true;

            if (fault == "SANS_SALETE") {
                c.sansSalete = true;
            } else if (fault == "DEPUIS_MODIF") {
                c.depuisModif = true;
            } else if (fault == "SAVED_GARDE_TEMPS") {
                c.savedGardeTemps = true;
            } else if (fault == "SAVED_GARDE_SALETE") {
                c.savedGardeSalete = true;
            } else if (fault == "STRICT") {
                c.strict = true;
            } else if (fault == "ZERO_IGNORE") {
                c.zeroIgnore = true;
            } else if (fault == "NEGATIF_COMPTE") {
                c.negatifCompte = true;
            } else if (fault == "SECOURS_FIXE") {
                secoursFixe = true;
            } else if (fault == "SECOURS_EST_DOC") {
                secoursEstDoc = true;
            } else if (fault == "SANS_NOM_VIDE") {
                sansNomVide = true;
            }
        }

        vector<int> echecs;

        // Test 1
        Component test1 = c;
        test1.interval = 60;

        for (int i = 0; i < 3600; i++) {
            if (test1.tick(1)) {
                echecs.push_back(1);
                break;
            }
        }

        // Tests 2 and 3 on the same component
        Component test23 = c;
        test23.interval = 60;
        test23.touch();

        bool test2Pass = true;

        for (int i = 0; i < 59; i++) {
            if (test23.tick(1)) {
                test2Pass = false;
                break;
            }
        }

        if (!test2Pass) {
            echecs.push_back(2);
        } else if (!test23.tick(1)) {
            echecs.push_back(3);
        }

        // Tests 4 and 5 on the same component
        Component test45 = c;
        test45.interval = 60;
        test45.touch();

        for (int i = 0; i < 60; i++) {
            test45.tick(1);
        }

        test45.saved();

        bool test4Pass = true;

        for (int i = 0; i < 120; i++) {
            if (test45.tick(1)) {
                test4Pass = false;
                break;
            }
        }

        if (!test4Pass) {
            echecs.push_back(4);
        }

        test45.touch();

        if (!test45.tick(0)) {
            echecs.push_back(5);
        }

        // Test 6
        Component test6 = c;
        test6.interval = 10;
        test6.touch();
        test6.saved();

        bool test6Pass = true;

        for (int i = 0; i < 100; i++) {
            if (test6.tick(1)) {
                test6Pass = false;
                break;
            }
        }

        if (!test6Pass) {
            echecs.push_back(6);
        }

        // Test 7 and 8
        string secours;

        if (secoursFixe) {
            secours = "secours.nkref.auto";
        } else if (secoursEstDoc) {
            secours = document;
        } else {
            secours = document + ".auto";
        }

        if (secours == document) {
            echecs.push_back(7);
        }

        if (secours.compare(0, document.size(), document) != 0) {
            echecs.push_back(8);
        }

        // Test 9
        string secoursVide;

        if (secoursFixe) {
            secoursVide = "secours.nkref.auto";
        } else if (secoursEstDoc || sansNomVide) {
            secoursVide = "";
        } else {
            secoursVide = "planche-sans-nom.nkref.auto";
        }

        if (secoursVide.empty()) {
            echecs.push_back(9);
        }

        // Results
        if (echecs.empty()) {
            cout << nom << " PASSE\n";

            if (faulty) {
                nonDetectes++;
                angleMort.push_back(nom);
            }
        } else {
            cout << nom << " ECHOUE";

            for (int test : echecs) {
                cout << " " << test;
            }

            cout << '\n';

            if (faulty) {
                detectes++;
            }
        }
    }

    cout << "DETECTES " << detectes << '\n';
    cout << "NON_DETECTES " << nonDetectes << '\n';

    cout << "ANGLE_MORT";

    if (angleMort.empty()) {
        cout << " AUCUN";
    } else {
        for (const string& nom : angleMort) {
            cout << " " << nom;
        }
    }

    cout << '\n';

    return 0;
}

     
