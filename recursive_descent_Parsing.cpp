#include <bits/stdc++.h>
using namespace std;

// ---------- Global data ----------
vector<string> tokens;   // token list: "id", "+", "*", "(", ")"
int pos = 0;             // current position in tokens

// helper: return current token or "" if finished
string current() {
    if (pos < (int)tokens.size()) return tokens[pos];
    return "";
}

// helper: try to match a token
bool match(const string &expected) {
    if (current() == expected) {
        pos++;
        return true;
    }
    return false;
}

// ---------- Recursive Descent Functions ----------
// Grammar:
// E  → T E'
// E' → + T E' | ε
// T  → F T'
// T' → * F T' | ε
// F  → (E) | id

bool E();     // forward declarations
bool Eprime();
bool T();
bool Tprime();
bool F();

// E → T E'
bool E() {
    if (!T()) return false;
    if (!Eprime()) return false;
    return true;
}

// E' → + T E' | ε
bool Eprime() {
    if (current() == "+") {
        if (!match("+")) return false;
        if (!T()) return false;
        if (!Eprime()) return false;
    }
    // if current is not "+", E' -> ε (do nothing, just return true)
    return true;
}

// T → F T'
bool T() {
    if (!F()) return false;
    if (!Tprime()) return false;
    return true;
}

// T' → * F T' | ε
bool Tprime() {
    if (current() == "*") {
        if (!match("*")) return false;
        if (!F()) return false;
        if (!Tprime()) return false;
    }
    // if current is not "*", T' -> ε
    return true;
}

// F → (E) | id
bool F() {
    if (current() == "id") {
        return match("id");
    } else if (current() == "(") {
        if (!match("(")) return false;
        if (!E()) return false;
        if (!match(")")) return false;
        return true;
    }
    return false;   // neither id nor '('E')'
}

// ---------- Tokenizer ----------
// Convert string like "(id+id)*id" into tokens: "(", "id", "+", "id", ")", "*", "id"
bool tokenize(const string &s) {
    tokens.clear();
    int n = s.size();
    for (int i = 0; i < n; ) {
        if (isspace(s[i])) { i++; continue; }

        if (s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '*') {
            tokens.push_back(string(1, s[i]));
            i++;
        } else if (i + 1 < n && s[i] == 'i' && s[i+1] == 'd') {
            tokens.push_back("id");
            i += 2;
        } else {
            // invalid character
            return false;
        }
    }
    return true;
}

// ---------- main ----------
int main() {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    if (!tokenize(input)) {
        cout << "Invalid characters in input.\n";
        return 0;
    }

    pos = 0;
    bool ok = E();                 // start symbol

    // expression is valid only if:
    // 1) E() returned true
    // 2) all tokens are consumed (pos == tokens.size())
    if (ok && pos == (int)tokens.size()) {
        cout << "Input string is accepted.\n";
    } else {
        cout << "Input string is rejected.\n";
    }

    return 0;
}
