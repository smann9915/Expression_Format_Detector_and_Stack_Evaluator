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
        //Uses spaces to separate input
        if (line.substr(i, 1) == " ") {
            if (!token.value.empty()) tokens.push_back(token);
            token.value = "";
        }
        //Handles parenthesis separately as they aren't normally separated by spaces
        else if (line.substr(i, 1) == "(" || line.substr(i, 1) == ")") {
            if (!token.value.empty()) tokens.push_back(token);

            token.value = line.substr(i, 1);
            tokens.push_back(token);
            token.value = "";
        }
        //Tokenizes any other input
        else {
            token.value += line.substr(i, 1);
        }
    }

    if (!token.value.empty()) {
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
    if (op == "+" || op == "-") {
        return 0;
    }
    return -1;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    int numbers = 0;
    int operators = 0;

    for (int i = 0; i < tokens.size(); i++) {
        //checks if the token is a number
         try {
             stoi(tokens[i].value);
             numbers++;
         }
        //checks if the token is an operator
         catch (invalid_argument ex) {
             //checks if the operator is in a valid spot
            if (isOperator(tokens[i].value) && numbers - 1 > operators) {
                operators++;
            }
            else {
                return false;
            }
         }
     }
    //return if there are enough numbers and if there are enough operators for the numbers
    return numbers - 1 == operators && numbers >= 2;
}

bool isValidInfix(const vector<Token>& tokens) {
    bool lastIsNum = false;
    int paranthesis_count = 0;

    for (int i = 0; i < tokens.size(); i++) {
        //check if the token is an int
        try {
            stoi(tokens[i].value);

            //Enures no number tokens back to back
            if (!lastIsNum) lastIsNum = true;
            else return false;
        }
        catch (invalid_argument ex) {
            //Checks if it is a valid operator
            if (isOperator(tokens[i].value) && lastIsNum) {
                lastIsNum = false;
            }
            //checks if the left parenthesis is in a valid spot
            else if (tokens[i].value == "(" && !lastIsNum) {
                paranthesis_count++;
                lastIsNum = false;
            }
            //Checks for and if the right paranethsis is in a valid
            else if (tokens[i].value== ")" && lastIsNum) {
                paranthesis_count--;
            }
            //If the token doesn't match any of these it must not be infix
            else {
                return false;
            }
        }
    }
    //Checks if we end on a number and if the paraenthsis even out
    return lastIsNum && paranthesis_count == 0;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    ArrayStack<Token> operators;

    for (int i = 0; i < tokens.size(); i++) {
        //pushes high priority and left paranethsis on to the stack no matter what
        if (tokens[i].value == "(" || precedence(tokens[i].value) == 1) {
            operators.push(tokens[i]);
        }
        else if (precedence(tokens[i].value) == 0) {
            //Immediately can push low priority if the stack is empty
            if (operators.empty()) {
                operators.push(tokens[i]);
            }
            //If the stack has a higher precedent operator pop it and then push
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
            //Loop through all operators inbetween the parenthesis to make them happen first in the postfix
            while (true) {
                Token op = operators.top();
                operators.pop();

                if (op.value == "(") {
                    break;
                }
                output.push_back(op);
            }
        }
        //This is only reached when the token is a number so we add it im7 mediately
        else {
            output.push_back(tokens[i]);
        }
    }

    //Adds all remaining operators to the postfix equation once the tokens have been looped through
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
        //Adds a number to the stack
        try {
            double num = stod(tokens[i].value);
            stack.push(num);
        }
        catch (invalid_argument ex) {
            double num1 = stack.top();
            stack.pop();

            double num2 = stack.top();
            stack.pop();

            //Checks what operation to do and executes it and returns the result to the stack
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
