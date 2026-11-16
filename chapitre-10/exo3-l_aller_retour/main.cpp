#include <iostream>

#include <iomanip>

#include <cmath>

#include <string>

using namespace std;

double clean(double value) {

    if (abs(value) < 0.0005) return 0.0;

    return value;

}

int main() {

    double W, H;

    if (!(cin >> W >> H)) return 0;

    double cx = 0.0;

    double cy = 0.0;

    double zoom = 1.0;

    string command;

    cout << fixed;

    while (cin >> command) {

        if (command == "VERS_MONDE") {

            double px, py;

            cin >> px >> py;

            double x = cx + (px - W / 2.0) / zoom;

            double y = cy + (py - H / 2.0) / zoom;

            cout << setprecision(2)

                 << "MONDE " << clean(x)

                 << " " << clean(y) << '\n';

        }

        else if (command == "VERS_PIXEL") {

            double mx, my;

            cin >> mx >> my;

            double x = (mx - cx) * zoom + W / 2.0;

            double y = (my - cy) * zoom + H / 2.0;

            cout << setprecision(2)

                 << "PIXEL " << clean(x)

                 << " " << clean(y) << '\n';

        }

        else if (command == "DEPLACE") {

            double dx, dy;

            cin >> dx >> dy;

            cx -= dx / zoom;

            cy -= dy / zoom;

        }

        else if (command == "ZOOM") {

            double f, px, py;

            cin >> f >> px >> py;

            double ax = cx + (px - W / 2.0) / zoom;

            double ay = cy + (py - H / 2.0) / zoom;

            zoom *= f;

            if (zoom < 0.02) zoom = 0.02;

            if (zoom > 64.0) zoom = 64.0;

            cx = ax - (px - W / 2.0) / zoom;

            cy = ay - (py - H / 2.0) / zoom;

        }

        else if (command == "GRILLE") {

            double m;

            cin >> m;

            double s = 1.0;

            while (s * zoom < m) {

                s *= 2.0;

            }

            while (s * 0.5 * zoom >= m) {

                s *= 0.5;

            }

            cout << setprecision(6)

                 << "GRILLE " << s << '\n';

        }

        else if (command == "ORIGINE") {

            cx = 0.0;

            cy = 0.0;

            zoom = 1.0;

        }

    }

    cout << setprecision(2)

         << "CENTRE " << clean(cx)

         << " " << clean(cy) << '\n';

    cout << "ZOOM " << clean(zoom) << '\n';

    return 0;

}