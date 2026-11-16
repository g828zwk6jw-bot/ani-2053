#include <iostream>

#include <vector>

#include <string>

#include <sstream>

#include <algorithm>

using namespace std;

bool contains(const vector<string>& names, const string& name) {

    return find(names.begin(), names.end(), name) != names.end();

}

void removeAt(vector<string>& arr, int index) {

    if (index >= 0 && index < (int)arr.size()) {

        arr.erase(arr.begin() + index);

    }

}

void swapAt(vector<string>& arr, int i, int j) {

    if (i >= 0 && j >= 0 &&

        i < (int)arr.size() && j < (int)arr.size()) {

        swap(arr[i], arr[j]);

    }

}

int main() {

    string line;

    vector<string> ajoute, supprime, echange;

    getline(cin, line);

    {

        istringstream ss(line);

        string name;

        ss >> line;

        while (ss >> name) ajoute.push_back(name);

    }

    getline(cin, line);

    {

        istringstream ss(line);

        string name;

        ss >> line;

        while (ss >> name) supprime.push_back(name);

    }

    getline(cin, line);

    {

        istringstream ss(line);

        string name;

        ss >> line;

        while (ss >> name) echange.push_back(name);

    }

    vector<string> model, textures, sources;

    int N;

    cin >> N;

    for (int k = 0; k < N; k++) {

        string operation;

        cin >> operation;

        if (operation == "AJOUTE") {

            string name;

            cin >> name;

            model.push_back(name);

            if (contains(ajoute, "textures"))

                textures.push_back(name);

            if (contains(ajoute, "sources"))

                sources.push_back(name);

        }

        else if (operation == "SUPPRIME") {

            int c;

            cin >> c;

            vector<int> indices(c);

            for (int j = 0; j < c; j++)

                cin >> indices[j];

            for (int j = c - 1; j >= 0; j--) {

                int i = indices[j];

                removeAt(model, i);

                if (contains(supprime, "textures"))

                    removeAt(textures, i);

                if (contains(supprime, "sources"))

                    removeAt(sources, i);

            }

        }

        else if (operation == "MONTE") {

            int i;

            cin >> i;

            if (i + 1 < (int)model.size()) {

                swapAt(model, i, i + 1);

                if (contains(echange, "textures"))

                    swapAt(textures, i, i + 1);

                if (contains(echange, "sources"))

                    swapAt(sources, i, i + 1);

            }

        }

        else if (operation == "DESCEND") {

            int i;

            cin >> i;

            if (i > 0 && i < (int)model.size()) {

                swapAt(model, i, i - 1);

                if (contains(echange, "textures"))

                    swapAt(textures, i, i - 1);

                if (contains(echange, "sources"))

                    swapAt(sources, i, i - 1);

            }

        }

    }

    int L = max({

        model.size(),

        textures.size(),

        sources.size()

    });

    int decales = 0;

    for (int i = 0; i < (int)L; i++) {

        string m = i < (int)model.size() ? model[i] : "-";

        string t = i < (int)textures.size() ? textures[i] : "-";

        string s = i < (int)sources.size() ? sources[i] : "-";

        cout << i << " " << m << " " << t << " " << s << '\n';

        if (m == "-" || t == "-" || s == "-" ||

            m != t || m != s) {

            decales++;

        }

    }

    cout << "DECALES " << decales << '\n';

    return 0;

}