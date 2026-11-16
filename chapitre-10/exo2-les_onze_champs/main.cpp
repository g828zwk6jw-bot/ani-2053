#include <iostream>

#include <string>

using namespace std;

int main() {

    int n;

    if (!(cin >> n)) return 0;

    int restent = 0;

    int changes = 0;

    for (int i = 1; i <= n; ++i) {

        long long id;

        double x, y, echelle, rotation, opacite;

        int miroirX, miroirY;

        long long largeur, hauteur;

        int selectionne;

        string chemin;

        long long octets;

        cin >> id >> x >> y >> echelle >> rotation >> opacite

            >> miroirX >> miroirY >> largeur >> hauteur

            >> selectionne >> chemin >> octets;

        cout << "ITEM " << i;

        if (octets == 0) {

            cout << " SAUTE\n";

            continue;

        }

        ++restent;

        cout << " " << restent;

        bool anyChange = false;

        if (id != 0) {

            cout << " id";

            anyChange = true;

            ++changes;

        }

        if (selectionne == 1) {

            cout << " selected";

            anyChange = true;

            ++changes;

        }

        if (chemin != "-") {

            cout << " sourcePath";

            anyChange = true;

            ++changes;

        }

        if (!anyChange) cout << " AUCUN";

        cout << '\n';

    }

    cout << "RESTENT " << restent << '\n';

    cout << "CHANGES " << changes << '\n';

    return 0;

}