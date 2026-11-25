
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
        if (depuisModif) elapsed = 0;
    }

    bool tick(long long d) {
        if (zeroIgnore && d <= 0) return false;

        if (d > 0 || (negatifCompte && d < 0))
            elapsed += d;

        bool condition = sansSalete || changed;

        if (strict)
            return condition && elapsed > interval;

        return condition && elapsed >= interval;
    }

    void saved() {
        if (!savedGardeSalete) changed = false;
        if (!savedGardeTemps) elapsed = 0;
    }
};

int main() {
    string line;
    int detectes = 0;
    int nonDetectes = 0;
    vector<string> angles;

    while (getline(cin, line)) {
        if (line.empty()) continue;

        istringstream input(line);
        string name, fault;

        if (!(input >> name)) continue;

        Component base;
        bool faulty = false;
        bool secoursEstDoc = false;
        bool secoursFixe = false;
        bool sansNomVide = false;

        while (input >> fault) {
            if (fault == "AUCUN") break;

            faulty = true;

            if (fault == "SANS_SALETE")
                base.sansSalete = true;
            else if (fault == "DEPUIS_MODIF")
                base.depuisModif = true;
            else if (fault == "SAVED_GARDE_TEMPS")
                base.savedGardeTemps = true;
            else if (fault == "SAVED_GARDE_SALETE")
                base.savedGardeSalete = true;
            else if (fault == "STRICT")
                base.strict = true;
            else if (fault == "ZERO_IGNORE")
                base.zeroIgnore = true;
            else if (fault == "NEGATIF_COMPTE")
                base.negatifCompte = true;
            else if (fault == "SECOURS_EST_DOC")
                secoursEstDoc = true;
            else if (fault == "SECOURS_FIXE")
                secoursFixe = true;
            else if (fault == "SANS_NOM_VIDE")
                sansNomVide = true;
        }

        vector<int> failed;

        // Test 1
        Component c1 = base;
        bool test1 = true;
        for (int i = 0; i < 3600; ++i) {
            if (c1.tick(1)) {
                test1 = false;
                break;
            }
        }
        if (!test1) failed.push_back(1);

        // Tests 2 and 3: same component
        Component c23 = base;
        c23.touch();

        bool test2 = true;
        for (int i = 0; i < 59; ++i) {
            if (c23.tick(1)) test2 = false;
        }
        if (!test2) failed.push_back(2);

        bool test3 = c23.tick(1);
        if (!test3) failed.push_back(3);

        // Tests 4 and 5: same component
        Component c45 = base;
        c45.touch();

        for (int i = 0; i < 60; ++i)
            c45.tick(1);

        c45.saved();

        bool test4 = true;
        for (int i = 0; i < 120; ++i) {
            if (c45.tick(1)) test4 = false;
        }
        if (!test4) failed.push_back(4);

        c45.touch();
        if (!c45.tick(0)) failed.push_back(5);

        // Test 6
        Component c6 = base;
        c6.interval = 10;
        c6.touch();
        c6.saved();

        bool test6 = true;
        for (int i = 0; i < 100; ++i) {
            if (c6.tick(1)) test6 = false;
        }
        if (!test6) failed.push_back(6);

        // Tests 7, 8 and 9: backup name
        string document = "D:/planches/personnages.nkref";
        string secours;

        if (secoursFixe)
            secours = "secours.nkref.auto";
        else if (secoursEstDoc)
            secours = document;
        else
            secours = document + ".auto";

        if (secours == document)
            failed.push_back(7);

        if (secours.rfind(document, 0) != 0)
            failed.push_back(8);

        string emptyDocument;
        string emptySecours;

        if (secoursFixe)
            emptySecours = "secours.nkref.auto";
        else if (secoursEstDoc || sansNomVide)
            emptySecours = "";
        else
            emptySecours = "planche-sans-nom.nkref.auto";

        if (emptySecours.empty())
            failed.push_back(9);

        if (failed.empty()) {
            cout << name << " PASSE\n";

            if (faulty) {
                ++nonDetectes;
                angles.push_back(name);
            }
        } else {
            cout << name << " ECHOUE";
            for (int test : failed)
                cout << " " << test;
            cout << "\n";

            if (faulty) ++detectes;
        }
    }

    cout << "DETECTES " << detectes << "\n";
    cout << "NON_DETECTES " << nonDetectes << "\n";
    cout << "ANGLE_MORT";

    if (angles.empty()) {
        cout << " AUCUN";
    } else {
        for (const string& name : angles)
            cout << " " << name;
    }

    cout << "\n";
    return 0;
}

