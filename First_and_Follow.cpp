#include <bits/stdc++.h>
using namespace std;

// ---------- Helpers ----------
bool isNonTerminal(char c) {
    // We will treat capital letters as non-terminals
    return (c >= 'A' && c <= 'Z');
}

int main() {
    // ---------- 1. Store the grammar ----------

    // We map each NON-TERMINAL to a LIST of its productions (RHS)
    // Example: E -> T A  is stored as  "TA"
    //          A -> + T A | e   as "+TA" and "e"
    map<char, vector<string>> prod;

    prod['E'] = {"TA"};         // E -> T A
    prod['A'] = {"+TA", "e"};   // A -> + T A | ε (ε as 'e')
    prod['T'] = {"FB"};         // T -> F B
    prod['B'] = {"*FB", "e"};   // B -> * F B | ε
    prod['F'] = {"(E)", "i"};   // F -> ( E ) | id  (i = id)

    // Non-terminals list (for printing in proper order)
    vector<char> nonTerminals = {'E', 'A', 'T', 'B', 'F'};

    // ---------- 2. FIRST sets ----------
    map<char, set<char>> FIRST;

    // We will repeatedly apply rules until no new symbol is added
    bool changed = true;
    while (changed) {
        changed = false;

        // For every production A -> alpha
        for (auto &p : prod) {
            char A = p.first;
            for (string alpha : p.second) {

                // Special case: production is just epsilon "e"
                if (alpha == "e") {
                    if (!FIRST[A].count('e')) {
                        FIRST[A].insert('e');
                        changed = true;
                    }
                    continue;
                }

                bool allNullable = true; // assume all symbols can be epsilon

                // Traverse symbols in alpha from left to right
                for (int i = 0; i < (int)alpha.size(); i++) {
                    char X = alpha[i];

                    if (!isNonTerminal(X)) {
                        // X is a terminal ( +, *, (, ), i )
                        if (!FIRST[A].count(X)) {
                            FIRST[A].insert(X);
                            changed = true;
                        }
                        allNullable = false; // terminal cannot be epsilon
                        break; // stop, we handled first symbol
                    } else {
                        // X is a non-terminal
                        // Add FIRST(X) - {e} to FIRST(A)
                        bool hasEpsilonInX = false;
                        for (char c : FIRST[X]) {
                            if (c == 'e') hasEpsilonInX = true;
                            else {
                                if (!FIRST[A].count(c)) {
                                    FIRST[A].insert(c);
                                    changed = true;
                                }
                            }
                        }
                        if (hasEpsilonInX) {
                            // Need to look at next symbol as well
                            // (do nothing, just continue to next i)
                        } else {
                            allNullable = false;
                            break; // stop, because this symbol can't be epsilon
                        }
                    }
                }

                // If ALL symbols in alpha can become epsilon, add epsilon to FIRST(A)
                if (allNullable) {
                    if (!FIRST[A].count('e')) {
                        FIRST[A].insert('e');
                        changed = true;
                    }
                }
            }
        }
    }

    // ---------- 3. FOLLOW sets ----------
    map<char, set<char>> FOLLOW;

    // Rule: put $ in FOLLOW(start symbol)
    FOLLOW['E'].insert('$'); // E is the start symbol

    changed = true;
    while (changed) {
        changed = false;

        // For every production A -> alpha
        for (auto &p : prod) {
            char A = p.first;
            for (string alpha : p.second) {

                int n = alpha.size();

                // Look at each position in alpha
                for (int i = 0; i < n; i++) {
                    char B = alpha[i];

                    if (!isNonTerminal(B)) continue; // we only care non-terminals

                    // 1) Everything in FIRST(beta) - {e}  goes to FOLLOW(B)
                    // where beta is the string after B in alpha
                    bool betaCanBeEpsilon = true;
                    if (i + 1 < n) {
                        // there is some beta
                        for (int j = i + 1; j < n; j++) {
                            char X = alpha[j];

                            if (!isNonTerminal(X)) {
                                // X is terminal
                                if (!FOLLOW[B].count(X)) {
                                    FOLLOW[B].insert(X);
                                    changed = true;
                                }
                                betaCanBeEpsilon = false;
                                break;
                            } else {
                                // X is non-terminal
                                bool hasEpsilonInX = false;
                                for (char c : FIRST[X]) {
                                    if (c == 'e') hasEpsilonInX = true;
                                    else {
                                        if (!FOLLOW[B].count(c)) {
                                            FOLLOW[B].insert(c);
                                            changed = true;
                                        }
                                    }
                                }
                                if (hasEpsilonInX) {
                                    // continue to next symbol in beta
                                } else {
                                    betaCanBeEpsilon = false;
                                    break;
                                }
                            }
                        }
                    } else {
                        // B is at the end, so beta is empty => epsilon
                        betaCanBeEpsilon = true;
                    }

                    // 2) If beta can be epsilon, add FOLLOW(A) to FOLLOW(B)
                    if (betaCanBeEpsilon) {
                        for (char c : FOLLOW[A]) {
                            if (!FOLLOW[B].count(c)) {
                                FOLLOW[B].insert(c);
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }

    // ---------- 4. Print FIRST sets ----------
    cout << "FIRST sets:\n";
    for (char A : nonTerminals) {
        cout << "FIRST(" << A << ") = { ";
        bool firstPrint = true;
        for (char c : FIRST[A]) {
            if (!firstPrint) cout << ", ";
            firstPrint = false;
            if (c == 'e') cout << "ε";
            else if (c == 'i') cout << "id";
            else cout << c;
        }
        cout << " }\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char A : nonTerminals) {
        cout << "FOLLOW(" << A << ") = { ";
        bool firstPrint = true;
        for (char c : FOLLOW[A]) {
            if (!firstPrint) cout << ", ";
            firstPrint = false;
            if (c == '$') cout << "$";
            else if (c == 'i') cout << "id";
            else cout << c;
        }
        cout << " }\n";
    }

    return 0;
}


*/
FIRST(E) = { (, id }
FIRST(A) = { +, ε }
FIRST(T) = { (, id }
FIRST(B) = { *, ε }
FIRST(F) = { (, id }

FOLLOW(E) = { ), $ }
FOLLOW(A) = { ), $ }
FOLLOW(T) = { +, ), $ }
FOLLOW(B) = { +, ), $ }
FOLLOW(F) = { *, +, ), $ }
/*