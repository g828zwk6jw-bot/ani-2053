#include <iostream>

#include <vector>

#include <string>

#include <cmath>

using namespace std;

struct Image {

    string nom;

    double x, y;

    double largeur, hauteur;

    double echelle;

};

bool touche(const Image& img, double px, double py) {

    double demiLargeur = img.largeur * img.echelle / 2.0;

    double demiHauteur = img.hauteur * img.echelle / 2.0;

    return abs(px - img.x) <= demiLargeur &&

           abs(py - img.y) <= demiHauteur;

}

int main() {

    int N;

    cin >> N;

    vector<Image> images(N);

    for (int i = 0; i < N; i++) {

        cin >> images[i].nom

            >> images[i].x

            >> images[i].y

            >> images[i].largeur

            >> images[i].hauteur

            >> images[i].echelle;

    }

    int Q;

    cin >> Q;

    int erreurs = 0;

    for (int k = 1; k <= Q; k++) {

        double px, py;

        cin >> px >> py;

        string A = "AUCUN";

        string B = "AUCUN";

        // Recherche a rebours : image du dessus

        for (int i = N - 1; i >= 0; i--) {

            if (touche(images[i], px, py)) {

                A = images[i].nom;

                break;

            }

        }

        // Recherche en avant

        for (int i = 0; i < N; i++) {

            if (touche(images[i], px, py)) {

                B = images[i].nom;

                break;

            }

        }

        cout << "CLIC " << k << " " << A << " " << B << '\n';

        if (A != B) {

            erreurs++;

        }

    }

    cout << "ERREURS " << erreurs << '\n';

    return 0;

}