#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

#include <sstream>

using namespace std;

struct Event {

    long long turn;

    int order;

    int sequence;

    string output;

    bool screenshot;

};

vector<string> split(const string& s, char delimiter) {

    vector<string> result;

    string part;

    stringstream ss(s);

    while (getline(ss, part, delimiter))

        result.push_back(part);

    if (s.empty() || s.back() == delimiter)

        result.push_back("");

    return result;

}

bool parseNumber(const string& s, long long& n) {

    if (s.empty()) return false;

    try {

        size_t pos;

        n = stoll(s, &pos);

        return pos == s.size();

    } catch (...) {

        return false;

    }

}

int main() {

    vector<Event> events;

    int ignored = 0;

    int never = 0;

    int sequence = 0;

    bool hasExit = false;

    long long exitFrame = 0;

    auto add = [&](long long turn, int order,

                   string output, bool shot = false) {

        events.push_back({turn, order, sequence++, output, shot});

    };

    string line;

    while (getline(cin, line)) {

        size_t equal = line.find('=');

        if (equal == string::npos) {

            ignored++;

            continue;

        }

        string name = line.substr(0, equal);

        string value = line.substr(equal + 1);

        if (name == "NK_AGENT_SHOT") {

            int kept = 0;

            for (const string& item : split(value, ',')) {

                long long n;

                if (!parseNumber(item, n)) {

                    ignored++;

                } else if (kept < 8) {

                    add(n - 1, 8,

                        "TOUR " + to_string(n - 1) + " CAPTURE", true);

                    kept++;

                } else {

                    ignored++;

                }

            }

        }

        else if (name == "NK_AGENT_EXIT") {

            long long n;

            if (parseNumber(value, n)) {

                hasExit = true;

                exitFrame = n;

            } else {

                ignored++;

            }

        }

        else if (name == "NK_AGENT_DROP") {

            int kept = 0;

            for (const string& item : split(value, ';')) {

                size_t p1 = item.find(':');

                size_t p2 = p1 == string::npos ? string::npos : item.find(':', p1 + 1);

                size_t p3 = p2 == string::npos ? string::npos : item.find(':', p2 + 1);

                long long n;

                if (p3 == string::npos ||

                    !parseNumber(item.substr(0, p1), n)) {

                    ignored++;

                    continue;

                }

                string x = item.substr(p1 + 1, p2 - p1 - 1);

                string y = item.substr(p2 + 1, p3 - p2 - 1);

                string path = item.substr(p3 + 1);

                if (kept < 8) {

                    add(n, 3, "TOUR " + to_string(n) +

                        " DEPOT " + path + " " + x + " " + y);

                    kept++;

                } else {

                    ignored++;

                }

            }

        }

        else if (name == "NK_AGENT_CLICK") {

            int kept = 0;

            for (const string& item : split(value, ';')) {

                vector<string> p = split(item, ':');

                long long n;

                if (p.size() < 3 || !parseNumber(p[0], n)) {

                    ignored++;

                    continue;

                }

                if (kept < 8) {

                    add(n, 4, "TOUR " + to_string(n) +

                        " CLIC " + p[1] + " " + p[2]);

                    kept++;

                } else {

                    ignored++;

                }

            }

        }

        else if (name == "NK_AGENT_PAN" ||

                 name == "NK_AGENT_ZOOM" ||

                 name == "NK_AGENT_MOVE" ||

                 name == "NK_AGENT_GRID") {

            vector<string> p = split(value, ':');

            long long n;

            int required = name == "NK_AGENT_ZOOM" ? 4 :

                           name == "NK_AGENT_GRID" ? 2 : 3;

            if (p.size() < required || !parseNumber(p[0], n)) {

                ignored++;

                continue;

            }

            string type;

            int order;

            if (name == "NK_AGENT_PAN") {

                type = "PAN";

                order = 1;

            } else if (name == "NK_AGENT_ZOOM") {

                type = "ZOOM";

                order = 2;

            } else if (name == "NK_AGENT_MOVE") {

                type = "MOVE";

                order = 5;

            } else {

                type = "GRILLE";

                order = 7;

            }

            string output = "TOUR " + to_string(n) + " " + type;

            for (int i = 1; i < required; i++)

                output += " " + p[i];

            add(n, order, output);

        }

        else if (name == "NK_AGENT_PACK") {

            long long n;

            if (parseNumber(value, n))

                add(n, 6, "TOUR " + to_string(n) + " RANGE");

            else

                ignored++;

        }

        else {

            ignored++;

        }

    }

    sort(events.begin(), events.end(),

        [](const Event& a, const Event& b) {

            if (a.turn != b.turn) return a.turn < b.turn;

            if (a.order != b.order) return a.order < b.order;

            return a.sequence < b.sequence;

        });

    for (const Event& e : events) {

        bool happens = e.turn > 0 || e.screenshot;

        if (e.screenshot)

            happens = e.turn >= 0;

        

        if (hasExit && exitFrame > 0) {

            if (e.screenshot)

                happens = happens && e.turn < exitFrame;

            else

                happens = happens && e.turn < exitFrame;

        }

        if (happens)

            cout << e.output << "\n";

        else

            never++;

    }

    if (hasExit && exitFrame > 0)

        cout << "ARRET " << exitFrame - 1 << "\n";

    else

        cout << "SANS_ARRET\n";

    cout << "JAMAIS " << never << "\n";

    cout << "IGNORES " << ignored << "\n";

    return 0;

}

