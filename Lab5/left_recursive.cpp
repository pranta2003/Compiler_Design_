#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int n;
    cout << "Enter number of non-terminals: ";
    cin >> n;
    cin.ignore();

    string nonTerminal, input;
    for (int i = 0; i < n; i++) {
        cout << "\nEnter production (e.g., E->E+T|T): ";
        getline(cin, input);

        size_t pos = input.find("->");
        nonTerminal = input.substr(0, pos);
        string right = input.substr(pos + 2);

        vector<string> prods;
        stringstream ss(right);
        string temp;
        while (getline(ss, temp, '|'))
            prods.push_back(temp);

        vector<string> alpha, beta;

        // Separate left-recursive and non-left-recursive parts
        for (string p : prods) {
            if (p[0] == nonTerminal[0])
                alpha.push_back(p.substr(1)); // remove the first char (A)
            else
                beta.push_back(p);
        }

        if (!alpha.empty()) {
            cout << "\nGrammar is Left Recursive.\n";
            string newNonTerminal = nonTerminal + "'";

            cout << "\nAfter removing Left Recursion:\n";
            cout << nonTerminal << " -> ";
            for (int j = 0; j < beta.size(); j++) {
                cout << beta[j] << newNonTerminal;
                if (j != beta.size() - 1) cout << " | ";
            }

            cout << "\n" << newNonTerminal << " -> ";
            for (int j = 0; j < alpha.size(); j++) {
                cout << alpha[j] << newNonTerminal;
                if (j != alpha.size() - 1) cout << " | ";
            }
            cout << " | e\n";
        } else {
            cout << "\nGrammar is NOT Left Recursive.\n";
            cout << nonTerminal << " -> " << right << endl;
        }
    }

    return 0;
}
