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
            if (!token.value.empty()) tokens.push_back(token);

            token.value = line.substr(i, 1);
            tokens.push_back(token);
            token.value = "";
        }
        else {
            token.value += line.substr(i, 1);
        }
    }

    if (token.value.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    if (op == "*" || op == "/") {
        return 1;
    }
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
                    stoi(tokens[i + 1].value);
                    i++;
                    lastIsNum = true;
                }
                catch (invalid_argument ex) {
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
    ArrayStack<Token> operators;

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].value == "(" || precedence(tokens[i].value) == 1) {
            operators.push(tokens[i]);
        }
        else if (precedence(tokens[i].value) == 0) {
            if (operators.empty()) operators.push(tokens[i]);

            else if (precedence(operators.top().value) == 1) {
                output.push_back(operators.top());
                operators.pop();
                operators.push(tokens[i]);
            }
            else {
                operators.push(tokens[i]);
            }
        }
        else if (tokens[i].value == ")") {
            while (true) {
                Token op = operators.top();
                operators.pop();
                if (op.value == "(") {
                    break;
                }
                output.push_back(op);
            }
        }
        else {
            output.push_back(tokens[i]);
        }
    }

    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;

    for (int i = 0; i < tokens.size(); i++) {
        try {
            double num = stod(tokens[i].value);
            stack.push(num);
        }
        catch (invalid_argument ex) {
            double num1 = stack.top();
            stack.pop();

            double num2 = stack.top();
            stack.pop();

            if (tokens[i].value == "+") {
                stack.push(num2 + num1);
            }
            else if (tokens[i].value == "-") {
                stack.push(num2 - num1);
            }
            else if (tokens[i].value == "*") {
                stack.push(num2 * num1);
            }
            else {
                stack.push(num2 / num1);
            }
        }
    }

    return stack.top();
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
