#include <iostream>

#include <cmath>

using namespace std;

int main() {

    const double pi = 3.141592653589793;

    int N;

    cin >> N;

    int visibles = 0;

    int refuses = 0;

    for (int i = 0; i < N; ++i) {

        int r, n;

        cin >> r >> n;

        if (n < 3) {

            cout << r << " " << n << " REFUSE\n";

            ++refuses;

            continue;

        }

        if (r == 0) {

            cout << r << " " << n << " 0 JAMAIS\n";

            continue;

        }

        double g = r * (1.0 - cos(pi / n));

        long long ecart = static_cast<long long>(floor(g * 1000.0));

        long long zoom = static_cast<long long>(ceil(100.0 / g));

        if (zoom <= 100) {

            cout << r << " " << n << " " << ecart << " "

                 << zoom << " VISIBLE\n";

            ++visibles;

        } else {

            cout << r << " " << n << " " << ecart << " "

                 << zoom << " INVISIBLE\n";

        }

    }

    cout << "VISIBLES " << visibles << "\n";

    cout << "REFUSES " << refuses << "\n";

    return 0;

}