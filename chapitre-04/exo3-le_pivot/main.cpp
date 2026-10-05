#include <iostream>

#include <string>

#include <algorithm>

using namespace std;

int main() {

    int N;

    cin >> N;

    int refuses = 0;

    for (int i = 0; i < N; ++i) {

        string nom;

        long long w, h, px, py, ox, oy, sx, sy, angle;

        cin >> nom >> w >> h >> px >> py >> ox >> oy >> sx >> sy >> angle;

        long long a = angle % 360;

        if (a < 0) {

            a += 360;

        }

        if (a % 90 != 0) {

            cout << nom << " ANGLE REFUSE\n";

            refuses++;

            continue;

        }

        long long c = 0;

        long long s = 0;

        if (a == 0) {

            c = 1;

            s = 0;

        }

        else if (a == 90) {

            c = 0;

            s = 1;

        }

        else if (a == 180) {

            c = -1;

            s = 0;

        }

        else if (a == 270) {

            c = 0;

            s = -1;

        }

        long long x[4] = {0, w, w, 0};

        long long y[4] = {0, 0, h, h};

        long long worldX[4];

        long long worldY[4];

        for (int j = 0; j < 4; ++j) {

            long long ax = (x[j] - ox) * sx;

            long long ay = (y[j] - oy) * sy;

            long long rx = ax * c - ay * s;

            long long ry = ax * s + ay * c;

            worldX[j] = px + rx;

            worldY[j] = py + ry;

        }

        long long minX = worldX[0];

        long long maxX = worldX[0];

        long long minY = worldY[0];

        long long maxY = worldY[0];

        for (int j = 1; j < 4; ++j) {

            minX = min(minX, worldX[j]);

            maxX = max(maxX, worldX[j]);

            minY = min(minY, worldY[j]);

            maxY = max(maxY, worldY[j]);

        }

        cout << nom << " COINS "

             << worldX[0] << " " << worldY[0] << " "

             << worldX[1] << " " << worldY[1] << " "

             << worldX[2] << " " << worldY[2] << " "

             << worldX[3] << " " << worldY[3] << "\n";

        cout << nom << " BOITE "

             << minX << " " << minY << " "

             << maxX << " " << maxY << "\n";

    }

    cout << "REFUSES " << refuses << "\n";

    return 0;

}