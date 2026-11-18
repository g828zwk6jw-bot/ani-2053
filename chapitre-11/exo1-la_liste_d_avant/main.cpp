#include <iostream>

#include <vector>

#include <string>

#include <unordered_set>

using namespace std;

int main() {

    int n, c, a;

    cin >> n;

    vector<string> avant(n);

    for (int i = 0; i < n; i++) {

        cin >> avant[i];

    }

    cin >> c;

    unordered_set<string> corrige;

    for (int i = 0; i < c; i++) {

        string key;

        cin >> key;

        corrige.insert(key);

    }

    cin >> a;

    unordered_set<string> apres;

    for (int i = 0; i < a; i++) {

        string key;

        cin >> key;

        apres.insert(key);

    }

    int vraies = 0;

    int fausses = 0;

    int oubliees = 0;

    int nouvelles = 0;

    unordered_set<string> avantSet;

    for (int i = 0; i < n; i++) {

        avantSet.insert(avant[i]);

        string category;

        if (corrige.count(avant[i])) {

            category = "DEVENUE_FAUSSE";

            fausses++;

        } else if (apres.count(avant[i])) {

            category = "ENCORE_VRAIE";

            vraies++;

        } else {

            category = "OUBLIEE";

            oubliees++;

        }

        cout << i + 1 << " " << avant[i]

             << " " << category << '\n';

    }

    for (const string& key : apres) {

        if (!avantSet.count(key)) {

            nouvelles++;

        }

    }

    int partOubliee = 0;

    if (vraies + oubliees > 0) {

        partOubliee = 100 * oubliees / (vraies + oubliees);

    }

    cout << "VRAIES " << vraies << '\n';

    cout << "FAUSSES " << fausses << '\n';

    cout << "OUBLIEES " << oubliees << '\n';

    cout << "NOUVELLES " << nouvelles << '\n';

    cout << "PART_OUBLIEE " << partOubliee << '\n';

    return 0;

}