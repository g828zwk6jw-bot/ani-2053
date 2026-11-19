#include <iostream>

#include <vector>

#include <string>

using namespace std;

int main() {

    vector<string> undoStack;

    vector<int> strokes;

    int strokeNumber = 0;

    int undoNumber = 0;

    int justes = 0;

    int riens = 0;

    int trahis = 0;

    int operations = 0;

    int annulables = 0;

    string command;

    while (cin >> command) {

        if (command == "ANNULE") {

            undoNumber++;

            string expected;

            if (undoStack.empty()) {

                expected = "AUCUNE";

            } else {

                expected = undoStack.back();

                undoStack.pop_back();

            }

            string obtained;

            if (strokes.empty()) {

                obtained = "RIEN";

            } else {

                obtained = "TRAIT " + to_string(strokes.back());

                strokes.pop_back();

            }

            string verdict;

            if (obtained == "RIEN") {

                if (expected == "AUCUNE") {

                    verdict = "JUSTE";

                    justes++;

                } else {

                    verdict = "RIEN";

                    riens++;

                }

            } else if (expected == obtained) {

                verdict = "JUSTE";

                justes++;

            } else {

                verdict = "TRAHI";

                trahis++;

            }

            cout << "ANNULE " << undoNumber

                 << " ATTENDU " << expected

                 << " OBTENU " << obtained

                 << " " << verdict << "\n";

        }

        else if (command == "TRAIT") {

            strokeNumber++;

            operations++;

            annulables++;

            undoStack.push_back(

                "TRAIT " + to_string(strokeNumber)

            );

            strokes.push_back(strokeNumber);

        }

        else if (command == "EFFACE") {

            operations++;

            undoStack.push_back("EFFACE");

            strokes.clear();

        }

        else if (command == "RANGE") {

            operations++;

            undoStack.push_back("RANGE");

        }

        else if (command == "DEPOSE" ||

                 command == "DEPLACE" ||

                 command == "SUPPRIME" ||

                 command == "MIROIR") {

            string name;

            cin >> name;

            operations++;

            undoStack.push_back(command + " " + name);

        }

    }

    cout << "JUSTES " << justes << "\n";

    cout << "RIENS " << riens << "\n";

    cout << "TRAHIS " << trahis << "\n";

    cout << "ANNULABLES " << annulables

         << " SUR " << operations << "\n";

    return 0;

}