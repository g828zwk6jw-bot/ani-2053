#include <iostream>

#include <string>

#include <iomanip>

#include <sstream>

using namespace std;

struct Task {

    string name;

    long long minimum;

    long long perday;

    long long start;

    long long gestures;

    long long waiting;

};

string formatTime(long long seconds) {

    long long minutes = seconds / 60;

    long long remaining = seconds % 60;

    ostringstream result;

    result << minutes << ":"

           << setw(2) << setfill('0') << remaining;

    return result.str();

}

int main() {

    Task task;

    bool running = false;

    long long totalDay = 0;

    long long time;

    string command;

    while (cin >> time >> command) {

        if (command == "DEBUT") {

            cin >> task.name

                >> task.minimum

                >> task.perday;

            task.start = time;

            task.gestures = 0;

            task.waiting = 0;

            running = true;

        }

        else if (command == "FIN") {

            string name;

            cin >> name;

            if (running) {

                long long extra =

                    task.gestures > task.minimum

                    ? task.gestures - task.minimum

                    : 0;

                long long duration = time - task.start;

                long long daySeconds =

                    (task.waiting * task.perday) / 1000;

                cout << task.name

                     << " GESTES " << task.gestures

                     << " EN_TROP " << extra

                     << " DUREE " << duration

                     << " ATTENTE " << task.waiting

                     << " JOUR " << formatTime(daySeconds)

                     << "\n";

                totalDay += daySeconds;

                running = false;

            }

        }

        else if (command == "CLIC" ||

                 command == "MOLETTE" ||

                 command == "GLISSE") {

            if (running) {

                task.gestures++;

            }

        }

        else if (command == "TOUCHE") {

            string key;

            cin >> key;

            if (running) {

                task.gestures++;

            }

        }

        else if (command == "ATTENTE") {

            long long waitingTime;

            cin >> waitingTime;

            if (running) {

                task.waiting += waitingTime;

            }

        }

    }

    if (running) {

        cout << task.name << " INACHEVEE\n";

    }

    cout << "TOTAL_JOUR " << formatTime(totalDay) << "\n";

    return 0;

}