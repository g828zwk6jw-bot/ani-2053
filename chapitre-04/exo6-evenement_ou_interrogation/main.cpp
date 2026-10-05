#include <iostream>

#include <string>

using namespace std;

int main() {

    int v, N;

    cin >> v >> N;

    int xe = 0;

    int xi = 0;

    bool space = false;

    bool right = false;

    bool left = false;

    int sautsEvenements = 0;

    int sautsInterrogation = 0;

    int manques = 0;

    for (int frame = 1; frame <= N; ++frame) {

        int k;

        cin >> k;

        int spacePresses = 0;

        for (int j = 0; j < k; ++j) {

            string event;

            cin >> event;

            bool pressed = event[0] == '+';

            string name = event.substr(1);

            if (name == "SPACE") {

                if (pressed) {

                    ++sautsEvenements;

                    ++spacePresses;

                    space = true;

                } else {

                    space = false;

                }

            }

            else if (name == "RIGHT") {

                if (pressed) {

                    right = true;

                    xe += v;

                } else {

                    right = false;

                }

            }

            else if (name == "LEFT") {

                if (pressed) {

                    left = true;

                    xe -= v;

                } else {

                    left = false;

                }

            }

        }

        if (space) {

            ++sautsInterrogation;

        }

        if (right) {

            xi += v;

        }

        if (left) {

            xi -= v;

        }

        if (!space) {

            manques += spacePresses;

        }

        cout << frame << " " << xe << " " << xi << "\n";

    }

    cout << "SAUTS EVENEMENTS " << sautsEvenements << "\n";

    cout << "SAUTS INTERROGATION " << sautsInterrogation << "\n";

    cout << "MANQUES " << manques << "\n";

    return 0;

}

