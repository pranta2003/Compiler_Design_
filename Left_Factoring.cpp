#include <bits/stdc++.h>
using namespace std;

/*
Input:
n
E->idT|idF|(E)
T->*FT|ε
(assume ε written as #)

We will find common prefixes and factor them:
E->idT|idF|(E)
=> E->idX|(E)
   X->T|F
*/

string longestCommonPrefix(const vector<string> &v) {
    if (v.empty()) return "";
    string pref = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        size_t j = 0;
        while (j < pref.size() && j < v[i].size() && pref[j] == v[i][j]) j++;
        pref = pref.substr(0, j);
        if (pref.empty()) break;
    }
    return pref;
}

int main() {
    int n;
    cout << "Enter number of nonterminals: ";
    if (!(cin >> n)) return 0;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    map<char, vector<string>> grammar;

    cout << "Enter productions (e.g., E->idT|idF|(E)):\n";
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        if (line.empty()) { --i; continue; }
        char A = line[0];
        size_t pos = line.find("->");
        if (pos == string::npos) continue;
        string rhs = line.substr(pos + 2);

        string cur;
        for (char c : rhs) {
            if (c == '|') {
                grammar[A].push_back(cur);
                cur.clear();
            } else {
                cur.push_back(c);
            }
        }
        if (!cur.empty()) grammar[A].push_back(cur);
    }

    cout << "\n--- Left Factoring Result ---\n";
    for (auto &p : grammar) {
        char A = p.first;
        auto &prods = p.second;

        string lcp = longestCommonPrefix(prods);
        if (lcp.size() <= 0) {
            cout << A << " -> ";
            for (size_t i = 0; i < prods.size(); ++i) {
                cout << prods[i];
                if (i + 1 < prods.size()) cout << " | ";
            }
            cout << "\n";
            continue;
        }

        cout << "Nonterminal " << A << " is left factorable with prefix \"" << lcp << "\".\n";

        char Aprime = (char)(A + 1);

        cout << "After left factoring:\n";
        cout << A << " -> " << lcp << Aprime << "\n";

        cout << Aprime << " -> ";
        bool first = true;
        for (auto &rhs : prods) {
            if (rhs.rfind(lcp, 0) == 0) { // starts with lcp
                string suffix = rhs.substr(lcp.size());
                if (suffix.empty()) suffix = "ε";
                if (!first) cout << " | ";
                cout << suffix;
                first = false;
            }
        }
        cout << "\n\n";
    }

    return 0;
}
