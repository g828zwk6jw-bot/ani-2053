#include <iostream>

#include <vector>

#include <string>

#include <algorithm>

using namespace std;

struct Workaround {

    string name;

    int times = 0;

    int firstTime = 0;

    int firstIndex = 0;

};

int toSeconds(const string& time) {

    int minutes = stoi(time.substr(0, 2));

    int seconds = stoi(time.substr(3, 2));

    return minutes * 60 + seconds;

}

int main() {

    int n;

    string word;

    cin >> word >> n;

    vector<Workaround> observed;

    int horsSeance = 0;

    for (int i = 0; i < n; i++) {

        string time, name;

        cin >> time >> name;

        int seconds = toSeconds(time);

        if (seconds > 1200) {

            horsSeance++;

            continue;

        }

        auto it = find_if(

            observed.begin(),

            observed.end(),

            [&](const Workaround& w) {

                return w.name == name;

            }

        );

        if (it == observed.end()) {

            Workaround w;

            w.name = name;

            w.times = 1;

            w.firstTime = seconds;

            w.firstIndex = i;

            observed.push_back(w);

        } else {

            it->times++;

            if (seconds < it->firstTime) {

                it->firstTime = seconds;

                it->firstIndex = i;

            }

        }

    }

    int m;

    cin >> word >> m;

    vector<string> mentioned;

    for (int i = 0; i < m; i++) {

        string name;

        cin >> name;

        mentioned.push_back(name);

    }

    // Sort workarounds.

    sort(

        observed.begin(),

        observed.end(),

        [](const Workaround& a, const Workaround& b) {

            if (a.times != b.times)

                return a.times > b.times;

            if (a.firstTime != b.firstTime)

                return a.firstTime < b.firstTime;

            return a.firstIndex < b.firstIndex;

        }

    );

    int nonDits = 0;

    int totalTimes = 0;

    int nonDitTimes = 0;

    // Print observed workarounds.

    for (const Workaround& w : observed) {

        bool said = find(

            mentioned.begin(),

            mentioned.end(),

            w.name

        ) != mentioned.end();

        cout << w.name << " " << w.times << " ";

        if (said) {

            cout << "DIT\n";

        } else {

            cout << "NON_DIT\n";

            nonDits++;

            nonDitTimes += w.times;

        }

        totalTimes += w.times;

    }

    // Print the number of unmentioned workarounds.

    cout << "NON_DITS " << nonDits << "\n";

    // Calculate the percentage.

    int percentage = 0;

    if (totalTimes > 0) {

        percentage = (100 * nonDitTimes) / totalTimes;

    }

    cout << "PART_NON_DITE " << percentage << "\n";

    // Find mentioned workarounds never observed.

    cout << "DIT_SANS_VU";

    bool found = false;

    for (const string& name : mentioned) {

        bool seen = find_if(

            observed.begin(),

            observed.end(),

            [&](const Workaround& w) {

                return w.name == name;

            }

        ) != observed.end();

        if (!seen) {

            cout << " " << name;

            found = true;

        }

    }

    if (!found) {

        cout << " AUCUN";

    }

    cout << "\n";

    // Print observations outside the session.

    cout << "HORS_SEANCE " << horsSeance << "\n";

    return 0;

} 