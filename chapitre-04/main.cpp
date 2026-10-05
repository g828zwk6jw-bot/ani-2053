#include <iostream>

using namespace std;

int main() {

    int C, R, W, H, F, D, P;

    cin >> C >> R >> W >> H >> F >> D >> P;

    int N;

    cin >> N;

    int cell = 0;

    int elapsed = 0;

    int avances = 0;

    int plafonnes = 0;

    for (int i = 0; i < N; ++i) {

        int dt;

        cin >> dt;

        if (dt > P) {

            dt = P;

            ++plafonnes;

        }

        elapsed += dt;

        while (elapsed >= D) {

            elapsed -= D;

            ++avances;

            ++cell;

            if (cell >= F) {

                cell = 0;

            }

        }

        int column = cell % C;

        int row = cell / C;

        int x = column * W;

        int y = row * H;

        cout << cell << " " << x << " " << y << " "

             << W << " " << H << "\n";

    }

    cout << "AVANCES " << avances << "\n";

    cout << "PLAFONNES " << plafonnes << "\n";

    return 0;

}