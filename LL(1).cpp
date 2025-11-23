#include <bits/stdc++.h>
using namespace std;

// Check if a symbol is a non-terminal (capital letter)
bool isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Parsing table: key = (NonTerminal, Terminal), value = RHS string
map<pair<char,char>, string> table;

// Build the LL(1) parsing table for our fixed grammar
void buildTable() {
    // E -> T A
    table[{ 'E', 'i' }] = "TA";
    table[{ 'E', '(' }] = "TA";

    // A (E')
    // A -> + T A
    table[{ 'A', '+' }] = "+TA";
    // A -> epsilon on ), $
    table[{ 'A', ')' }] = "e";
    table[{ 'A', '$' }] = "e";

    // T -> F B
    table[{ 'T', 'i' }] = "FB";
    table[{ 'T', '(' }] = "FB";

    // B (T')
    // B -> * F B
    table[{ 'B', '*' }] = "*FB";
    // B -> epsilon on +, ), $
    table[{ 'B', '+' }] = "e";
    table[{ 'B', ')' }] = "e";
    table[{ 'B', '$' }] = "e";

    // F
    // F -> id  (we use 'i')
    table[{ 'F', 'i' }] = "i";
    // F -> ( E )
    table[{ 'F', '(' }] = "(E)";
}

// Convert string like "id+id*id$" to tokens: i + i * i $
string tokenize(const string &s) {
    string tokens;
    int n = s.size();
    for (int i = 0; i < n; ) {
        if (i + 1 < n && s[i] == 'i' && s[i+1] == 'd') {
            tokens.push_back('i'); // single token for id
            i += 2;
        } else {
            tokens.push_back(s[i]);
            i++;
        }
    }
    // make sure it ends with $
    if (tokens.empty() || tokens.back() != '$') tokens.push_back('$');
    return tokens;
}

int main() {
    buildTable();

    cout << "Enter input (example: id+id*id$): ";
    string input;
    cin >> input;

    string tokens = tokenize(input);

    // Parsing stack
    stack<char> st;
    st.push('$');
    st.push('E');  // start symbol

    int idx = 0;                 // current position in tokens
    char a = tokens[idx];        // current input symbol

    cout << "\nSteps:\n";
    cout << "Stack\t\tInput\t\tAction\n";
    cout << "---------------------------------------------\n";

    while (!st.empty()) {
        // print current stack
        stack<char> temp = st;
        string stackContent;
        while (!temp.empty()) {
            stackContent.push_back(temp.top());
            temp.pop();
        }
        reverse(stackContent.begin(), stackContent.end());

        string remainingInput = tokens.substr(idx);

        cout << stackContent << "\t\t" << remainingInput << "\t\t";

        char X = st.top();

        if (!isNonTerminal(X)) { // X is terminal or $
            if (X == a) {
                if (X == '$') {
                    cout << "Accept\n";
                    break;
                }
                st.pop();
                idx++;
                a = tokens[idx];
                cout << "Match " << X << "\n";
            } else {
                cout << "Error: expected " << X << ", found " << a << "\n";
                break;
            }
        } else { // X is non-terminal
            auto it = table.find({X, a});
            if (it == table.end()) {
                cout << "Error: no rule for (" << X << ", " << a << ")\n";
                break;
            }

            string rhs = it->second;
            st.pop();

            if (rhs == "e") {
                cout << X << " -> epsilon\n";
                // push nothing
            } else {
                cout << X << " -> " << rhs << "\n";
                // push RHS in reverse order
                for (int i = (int)rhs.size() - 1; i >= 0; i--) {
                    st.push(rhs[i]);
                }
            }
        }
    }

    if (st.empty() && a == '$') {
        cout << "\nInput string is accepted.\n";
    } else {
        cout << "\nInput string is rejected.\n";
    }

    return 0;
}
