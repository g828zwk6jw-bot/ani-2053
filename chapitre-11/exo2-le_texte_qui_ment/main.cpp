#include <iostream>

#include <vector>

#include <string>

#include <unordered_set>

#include <unordered_map>

using namespace std;

struct Commit {

    string hash;

    string action;

    vector<string> features;

};

struct Announcement {

    string hash;

    string state;

    string feature;

};

int main() {

    int H;

    cin >> H;

    vector<Commit> commits(H);

    unordered_map<string, int> positions;

    for (int i = 0; i < H; i++) {

        cin >> commits[i].hash;

        cin >> commits[i].action;

        int k;

        cin >> k;

        positions[commits[i].hash] = i;

        for (int j = 0; j < k; j++) {

            string feature;

            cin >> feature;

            commits[i].features.push_back(feature);

        }

    }

    vector<unordered_set<string>> history(H);

    for (int i = 0; i < H; i++) {

        if (i > 0) {

            history[i] = history[i - 1];

        }

        for (const string& feature : commits[i].features) {

            if (commits[i].action == "AJOUTE") {

                history[i].insert(feature);

            } else {

                history[i].erase(feature);

            }

        }

    }

    int A;

    cin >> A;

    vector<Announcement> announcements(A);

    for (int i = 0; i < A; i++) {

        cin >> announcements[i].hash;

        cin >> announcements[i].state;

        cin >> announcements[i].feature;

    }

    int lies = 0;

    for (int i = 0; i < A; i++) {

        const Announcement& announcement = announcements[i];

        int writtenAt = positions[announcement.hash];

        bool shouldExist =

            announcement.state == "DISPONIBLE";

        auto isTrue = [&](int commitIndex) {

            bool exists =

                history[commitIndex].count(announcement.feature) > 0;

            return exists == shouldExist;

        };

        if (isTrue(H - 1)) {

            cout << "ANNONCE " << i + 1 << " VRAI\n";

        } else {

            int lyingSince = H - 1;

            while (lyingSince > writtenAt &&

                   !isTrue(lyingSince - 1)) {

                lyingSince--;

            }

            cout << "ANNONCE " << i + 1

                 << " MENT "

                 << commits[lyingSince].hash << "\n";

            lies++;

        }

    }

    cout << "MENSONGES " << lies << "\n";

    return 0;

}