

#include <iostream>

#include <vector>

#include <string>

#include <algorithm>

using namespace std;

struct Entry {

    string name;

    int value;

    int cost;

    string label;

    string kind;

    string target;

    int index;

    int cell;

    bool excluded;

    string reason;

};

int labelRank(const string& label) {

    if (label == "MESUREE") return 0;

    if (label == "OBSERVEE") return 1;

    return 2;

}

int getCell(int value, int cost) {

    bool highValue = value >= 3;

    bool highCost = cost >= 3;

    if (highValue && !highCost) return 0;

    if (highValue && highCost) return 1;

    if (!highValue && !highCost) return 2;

    return 3;

}

int main() {

    int n;

    cin >> n;

    vector<Entry> entries(n);

    for (int i = 0; i < n; i++) {

        Entry& e = entries[i];

        cin >> e.name >> e.value >> e.cost

            >> e.label >> e.kind;

        e.target = "";

        if (e.kind == "SOCLE") {

            cin >> e.target;

        }

        e.index = i;

        e.cell = -1;

        e.excluded = false;

        e.reason = "";

    }

    // Set aside entries that do not belong in the list.

    for (Entry& e : entries) {

        if (e.kind == "REECRITURE") {

            e.excluded = true;

            e.reason = "reecriture";

        } else if (e.kind == "CHOIX") {

            e.excluded = true;

            e.reason = "choix";

        } else if (e.label == "-") {

            e.excluded = true;

            e.reason = "sans_etiquette";

        }

    }

    // Apply the value of foundations.

    for (Entry& e : entries) {

        if (e.excluded || e.kind != "SOCLE") {

            continue;

        }

        for (const Entry& target : entries) {

            if (!target.excluded &&

                target.kind == "MANQUE" &&

                target.name == e.target) {

                e.value = max(e.value, target.value);

                break;

            }

        }

    }

    // Calculate the cell of every kept entry.

    vector<Entry> kept;

    for (Entry& e : entries) {

        if (!e.excluded) {

            e.cell = getCell(e.value, e.cost);

            kept.push_back(e);

        }

    }

    // Sort by cell, label, value, cost, then input order.

    sort(kept.begin(), kept.end(),

         [](const Entry& a, const Entry& b) {

        if (a.cell != b.cell)

            return a.cell < b.cell;

        if (labelRank(a.label) != labelRank(b.label))

            return labelRank(a.label) < labelRank(b.label);

        if (a.value != b.value)

            return a.value > b.value;

        if (a.cost != b.cost)

            return a.cost < b.cost;

        return a.index < b.index;

    });

    const string cells[] = {

        "MAINTENANT",

        "DECOUPER",

        "EN_PASSANT",

        "ON_NE_LE_FAIT_PAS"

    };

    bool honest = false;

    // Print kept entries.

    for (const Entry& e : kept) {

        cout << cells[e.cell] << " "

             << e.name << " "

             << e.label << "\n";

        if (e.cell == 3) {

            honest = true;

        }

    }

    // Print excluded entries in input order.

    for (const Entry& e : entries) {

        if (e.excluded) {

            cout << "HORS_LISTE "

                 << e.name << " "

                 << e.reason << "\n";

        }

    }

    // Print the verdict.

    if (honest) {

        cout << "VERDICT HONNETE\n";

    } else {

        cout << "VERDICT COMPLAISANT\n";

    }

    return 0;

}