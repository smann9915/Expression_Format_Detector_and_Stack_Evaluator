#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;

    Token token = Token();
    for (int i = 0; i < line.length(); i++) {
        if (line.substr(i, 1) == " ") {
            if (!token.value.empty()) tokens.push_back(token);
            token.value = "";
        }
        else if (line.substr(i, 1) == "(" || line.substr(i, 1) == ")") {
            if (!- token.value.empty()) tokens.push_back(token);

            token.value = line.substr(i, 1);
            tokens.push_back(token);
            token.value = "";
        }
        else {
            token.value += line.substr(i, 1);
        }
    }

    if (token.value != "") {
        tokens.push_back(token);
    }

    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    // TODO
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    int numbers = 0;
    int operators = 0;

    for (int i = 0; i < tokens.size(); i++) {
         try {
             stoi(tokens[i].value);
             numbers++;
         }
         catch (invalid_argument ex) {
            if (isOperator(tokens[i].value) && numbers > operators) {
                operators++;
            }
            else {
                return false;
            }
         }
     }
    return numbers == operators + 1;
}

bool isValidInfix(const vector<Token>& tokens) {
    bool lastIsNum = false;

    for (int i = 0; i < tokens.size(); i++) {
        try {
            stoi(tokens[i].value);

            if (!lastIsNum) lastIsNum = true;
            else return false;
        }
        catch (invalid_argument ex) {
            if (isOperator(tokens[i].value) && lastIsNum) {
                lastIsNum = false;
            }
            else if (tokens[i].value == "(" && !lastIsNum) {
                try {
                    cout << "start";

                    stoi(tokens[i + 1].value);
                    i++;
                    lastIsNum = true;

                    cout << "complete";
                }
                catch (invalid_argument ex) {
                    cout << "failed";
                    return false;
                }
            }
            else if (tokens[i].value== ")" && lastIsNum) {
                lastIsNum = true;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    return 0.0;
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    for (const auto& t : tokens) {
        cout << t.value << ", ";
    }

    cout << endl << endl;

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}
