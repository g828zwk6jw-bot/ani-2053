#include <iostream>

#include <string>

using namespace std;

int main() {

    int N;

    cin >> N;

    int pointsTotal = 0;

    int segmentsTotal = 0;

    int trianglesTotal = 0;

    int refusesTotal = 0;

    for (int i = 0; i < N; ++i) {

        string type;

        int vertices;

        cin >> type >> vertices;

        if (type == "POINTS") {

            cout << type << " " << vertices << " " << vertices << " POINTS 0\n";

            pointsTotal += vertices;

        }

        else if (type == "LINES") {

            int count = vertices / 2;

            int left = vertices % 2;

            cout << type << " " << vertices << " " << count << " SEGMENTS " << left << "\n";

            segmentsTotal += count;

        }

        else if (type == "LINE_STRIP") {

            int count = 0;

            int left = vertices;

            if (vertices >= 2) {

                count = vertices - 1;

                left = 0;

            }

            cout << type << " " << vertices << " " << count << " SEGMENTS " << left << "\n";

            segmentsTotal += count;

        }

        else if (type == "TRIANGLES") {

            int count = vertices / 3;

            int left = vertices % 3;

            cout << type << " " << vertices << " " << count << " TRIANGLES " << left << "\n";

            trianglesTotal += count;

        }

        else if (type == "TRIANGLE_STRIP" || type == "TRIANGLE_FAN") {

            int count = 0;

            int left = vertices;

            if (vertices >= 3) {

                count = vertices - 2;

                left = 0;

            }

            cout << type << " " << vertices << " " << count << " TRIANGLES " << left << "\n";

            trianglesTotal += count;

        }

        else {

            cout << type << " " << vertices << " REFUSE\n";

            refusesTotal++;

        }

    }

    cout << "POINTS " << pointsTotal << "\n";

    cout << "SEGMENTS " << segmentsTotal << "\n";

    cout << "TRIANGLES " << trianglesTotal << "\n";

    cout << "REFUSES " << refusesTotal << "\n";

    return 0;

}