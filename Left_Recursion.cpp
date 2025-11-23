#include <bits/stdc++.h>
using namespace std;

/*
Input format:
n                            // number of nonterminals
For each line:
A->Aa|b|Ac   (no spaces)

Example:
2
E->E+T|T
T->T*F|F
*/

int main() {
    int n;
    cout << "Enter number of nonterminals: ";
    if (!(cin >> n)) return 0;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    map<char, vector<string>> grammar;

    cout << "Enter productions (e.g., E->E+T|T):\n";
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

    cout << "\n--- Analyzing Left Recursion ---\n";
    for (auto &p : grammar) {
        char A = p.first;
        auto &prods = p.second;
        vector<string> alpha, beta;

        for (auto &rhs : prods) {
            if (!rhs.empty() && rhs[0] == A) {
                alpha.push_back(rhs.substr(1)); // after A
            } else {
                beta.push_back(rhs);
            }
        }

        if (alpha.empty()) {
            cout << "Nonterminal " << A << " has NO immediate left recursion.\n";
            continue;
        }

        cout << "Nonterminal " << A << " has immediate left recursion.\n";
        char Aprime = (char)(A + 1); // simple choice, e.g., E' -> F in ASCII

        cout << "After removing left recursion:\n";
        cout << A << " -> ";
        for (size_t i = 0; i < beta.size(); ++i) {
            cout << beta[i] << Aprime;
            if (i + 1 < beta.size()) cout << " | ";
        }
        cout << "\n";

        cout << Aprime << " -> ";
        for (size_t i = 0; i < alpha.size(); ++i) {
            cout << alpha[i] << Aprime << " | ";
        }
        cout << "ε\n\n";
    }

    return 0;
}
