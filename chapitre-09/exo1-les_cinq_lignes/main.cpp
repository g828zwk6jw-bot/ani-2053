#include <iostream>

#include <string>

using namespace std;

int main() {

    string C;

getline(cin, C);

string names[5] = {

    "DESTRUCTEUR",

    "COPIE",

    "AFFECTATION_COPIE",

    "DEPLACEMENT",

    "AFFECTATION_DEPLACEMENT"

};

string states[5] = {

    "ABSENT",

    "ABSENT",

    "ABSENT",

    "ABSENT",

    "ABSENT"

};

string line;

    while (getline(cin, line)) {

        size_t comment = line.find("//");

        if (comment != string::npos)

            line = line.substr(0, comment);

        string s;

        for (char ch : line) {

            if (ch != ' ')

                s += ch;

        }

        if (s.empty())

            continue;

        int index = -1;

        string copyPrefix = C + "(const" + C + "&";

        string copyAssignPrefix =

            C + "&operator=(const" + C + "&";

        string movePrefix = C + "(" + C + "&&";

        string moveAssignPrefix =

            C + "&operator=(" + C + "&&";

        if (s.find("~" + C + "(") != string::npos) {

            index = 0;

        }

        else if (s.rfind(copyPrefix, 0) == 0 &&

                 (s.size() == copyPrefix.size() ||

                  s[copyPrefix.size()] != '&')) {

            index = 1;

        }

        else if (s.rfind(copyAssignPrefix, 0) == 0 &&

                 (s.size() == copyAssignPrefix.size() ||

                  s[copyAssignPrefix.size()] != '&')) {

            index = 2;

        }

        else if (s.rfind(movePrefix, 0) == 0) {

            index = 3;

        }

        else if (s.rfind(moveAssignPrefix, 0) == 0) {

            index = 4;

        }

        if (index != -1) {

            if (s.size() >= 9 &&

    s.substr(s.size() - 9) == "=default;")

                states[index] = "DEFAUT";

            else if (s.size() >= 8 &&

         s.substr(s.size() - 8) == "=delete;")

                states[index] = "SUPPRIME";

            else

                states[index] = "ECRIT";

        int count = 0;

    for (int i = 0; i < 5; i++) {

        if (states[i] != "ABSENT")

            count++;

    }

    bool moveDeclared =

        states[3] != "ABSENT" ||

        states[4] != "ABSENT";

    string rule;

    if (count == 0)

        rule = "ZERO";

    else if (count == 5)

        rule = "CINQ";

    else if (states[0] != "ABSENT" &&

             states[1] != "ABSENT" &&

             states[2] != "ABSENT" &&

             !moveDeclared)

        rule = "TROIS";

    else

        rule = "INCOMPLETE";
 for (int i = 0; i < 5; i++) {

        cout << names[i] << " " << states[i] << '\n';

    }

    cout << "REGLE " << rule << '\n';

    if (rule == "INCOMPLETE") {

        int limit = moveDeclared ? 5 : 3;

        for (int i = 0; i < limit; i++) {

            if (states[i] == "ABSENT")

                cout << "MANQUE " << names[i] << '\n';

        }

    }

    cout << "POSSEDE "

         << (states[0] == "ECRIT" ? "OUI" : "NON") << '\n';

    cout << "UNIQUE "

         << (states[1] == "SUPPRIME" &&

             (states[3] == "ECRIT" || states[3] == "DEFAUT")

             ? "OUI" : "NON") << '\n';
return 0;

}