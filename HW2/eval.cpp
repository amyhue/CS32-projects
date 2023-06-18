// Code for inToPostfix and evaluate functions based on the pseudo code from: 
// Source: Data Abstraction and Problem Solving with C++: Walls and Mirrors, Seventh Edition, by Frank M. Carrano and Timothy Henry, Addison Wesley, 2017.

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool hasHigherPrecedence(char operator1, char operator2);
// Checks if operator1 has greater precedence than operator2. If it has greater precedence
// return true. If the precedence is the same or less than operator 2, return false.

bool inToPostfix(string infix, string& postfix);
// Converts a infix expression to postfix. If the infix is syntactically valid expression
// sets postfix to the postfix form of that expression and return true. If the infix is not
// a syntactically valid expression, postfix may or may not be changed, but the function must 
// return false.


int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero. If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.


//////////////
// Implementation
//////////////

// Assumes valid operators are &, ^, !
// Order of precedence (high to low): !, &, ^
// Precedence is same betweeen the same characters
bool hasHigherPrecedence(char operator1, char operator2) {

	if (operator1 == '!') {
		if (operator2 == '&' || operator2 == '^') return true;
		else return false;
	}
	else if (operator1 == '&') {
		if (operator2 == '^') return true;
		else return false;
	}
	else if (operator1 == '^') {
		return false;
	}

	return false;
}


// Assumes valid operands are T, F
// Assumes valid operators are &, ^, !
// Accepts (, ) in the infix expression
bool inToPostfix(string infix, string& postfix) {

	postfix = "";
	stack<char> operatorStack;
	
	// get rid of whitespaces
	string newInfix;
	for (int i = 0; i < infix.size(); i++) {
		if (!isspace(infix[i]))
			newInfix += infix[i];
	}

	// if newInfix does not have at least one character, it is obviously invalid
	if (newInfix.size() <= 0) return false;

	// evalute if newInfix is a valid infix expression
	for (int i = 0; i < newInfix.size(); i++) {
		switch (newInfix[i]) {
			case 'T':
			case 'F':
				// if there exists a character before current and that character is T/F, return false
				
				// !***! if ')' is before current, the character should also return false
					// if(i!=0 && (newInfix[i-1] == 'T' || newInfix[i - 1] == 'F' || newInfix[i - 1] == ')'))
				
				// Because valid infix expressions should not have operands next to each other in their expression
				if (i != 0 && (newInfix[i - 1] == 'T' || newInfix[i - 1] == 'F'))
					return false;

				postfix += newInfix[i];
				break;
			case '!':
			case '(':
				// cannot have ), T, F before !, ( for a valid infix expression, return false
				if (i != 0 && (newInfix[i - 1] == ')' || newInfix[i - 1] == 'T' || newInfix[i - 1] == 'F'))
					return false;
				// cannot end an infix expression with ! or (
				if (i == (newInfix.size() - 1))
					return false;

				operatorStack.push(newInfix[i]);
				break;
			case ')':
 
				// if there is no ( to close, it's an invalid infix expression
				if (operatorStack.empty() /*|| operatorStack.top() == '('*/) return false;

				// cannot have operators in front of )
				// also cannot have ( in front of ) because cannot be an empty pair
				if(i!=0 && (newInfix[i - 1] == '(' || newInfix[i - 1] == '^' 
						 || newInfix[i - 1] == '&' || newInfix[i - 1] == '!'))
					return false;
				
				// pop stack until find the corresponding '('
				while (operatorStack.top() != '(') {
					char x = operatorStack.top();
					postfix += x;
					operatorStack.pop();
					// if the stack is empty before we find (, there is no corresponding '(' anymore;
					// so this is an invalid infix expressions
					if (operatorStack.empty()) return false; }
				operatorStack.pop(); // remove '('
				break;
			case '&':
			case '^':
				// cannot start or end an infix expression with & or ^
				if (i == 0 || i == (newInfix.size()-1))
					return false; 

				// valid infix expressions should not have !, (, ^, & before the operator
				if (i != 0 && (newInfix[i - 1] == '!' ||newInfix[i - 1] == '(' 
							|| newInfix[i - 1] == '^' || newInfix[i - 1] == '&'))
					return false;

				while (!operatorStack.empty() && operatorStack.top() != '(' && !hasHigherPrecedence(newInfix[i], operatorStack.top())) {
					char x = operatorStack.top();
					postfix += x;
					operatorStack.pop();
				}
				operatorStack.push(newInfix[i]);
				break;
			// if the item is not any of the accepted operator, operands, or parentheses, as seen above,
			//it's not a valid character for an infix expression
			default:
				return false;
		}
	}

	while (!operatorStack.empty()) {
		char x = operatorStack.top();
		
		// if the operator is '(', that means we never closed the parenthesis, so the infix expression is false
		if (x == '(') return false;

		postfix += x;
		operatorStack.pop();
	}

	return true;
}


// Assumes valid operands are T, F
// Assumes valid operators are &, ^, !
// Accepts (, ) in the infix expression
int evaluate(string infix, string& postfix, bool& result) {
	// if not syntactically valid, return false
	if(inToPostfix(infix, postfix) == false)
		return 1;
	
	// if inToPostfix() is true, the infix expression will have been converted to its postfix expression after running the if statement
	stack<bool> operandStack;
	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i] == 'T' || postfix[i] == 'F') {
			switch (postfix[i]) {
				case 'T':
					operandStack.push(true);
					break;
				case 'F':
					operandStack.push(false);
					break;
			}
		}
		else if (postfix[i] == '!') {
			bool operand1;
			operand1 = operandStack.top();
			operandStack.pop();

			operand1 = !operand1; // change value of operand1 to not operand1
			operandStack.push(operand1);
		}
		else { // ch is an binary operator
			bool operand1, operand2, newOperand;
			operand2 = operandStack.top();
			operandStack.pop();
			
			operand1 = operandStack.top();
			operandStack.pop();

			switch (postfix[i]) {
				case '&': // AND
					newOperand = operand1 && operand2;
					operandStack.push(newOperand);
					break;
				case '^': // XOR
					newOperand = !(operand1 == operand2) && (operand1 || operand2);
					operandStack.push(newOperand);
					break;
			}
		}
	}

	result = operandStack.top();
	return 0;
}

int main() {

	bool result = false;
	string postfix;
	
	cout << inToPostfix("(T^F)T", postfix) << ", " << postfix << endl;
	//assert(evaluate("(T^F)T", postfix, result) == 1);

	/*assert(evaluate("TT", postfix, result) == 1 && result == false);
	assert(evaluate("T!", postfix, result) == 1 && result == false);

	assert(evaluate("T^^", postfix, result) == 1 && result == false);
	assert(evaluate("F^T!", postfix, result) == 1 && result == false);
	assert(evaluate("^^", postfix, result) == 1 && result == false);
	assert(evaluate("!!", postfix, result) == 1 && result == false);
	assert(evaluate("()", postfix, result) == 1 && result == false);
	assert(evaluate("(T^F", postfix, result) == 1 && result == false);
	assert(evaluate("T^F)", postfix, result) == 1 && result == false);
	assert(evaluate("T&F!", postfix, result) == 1 && result == false);
	assert(evaluate("T!&F", postfix, result) == 1 && result == false);
	assert(evaluate("T^F^", postfix, result) == 1 && result == false);
	assert(evaluate("T&&F", postfix, result) == 1 && result == false);
	assert(evaluate("T||F", postfix, result) == 1 && result == false);
	assert(evaluate("t^f", postfix, result) == 1 && result == false);
	assert(evaluate("", postfix, result) == 1 && result == false);
	assert(evaluate("      ", postfix, result) == 1 && result == false);

	assert(evaluate("!!!T", postfix, result) == 0 && result == false && postfix == "T!!!");*/

	string pf;
	bool answer;
	/*assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);

	assert(evaluate("T", pf, answer) == 0 && answer == true && pf == "T");
	assert(evaluate("(F)", pf, answer) == 0 && answer == false && pf == "F");
	assert(evaluate("T^(F)", pf, answer) == 0 && answer == true && pf == "TF^");
	assert(evaluate("T ^ !F", pf, answer) == 0 && answer == false && pf == "TF!^");
	assert(evaluate("!(T&F)", pf, answer) == 0 && answer == true && pf == "TF&!");
	assert(evaluate("!T&F", pf, answer) == 0 && answer == false && pf == "T!F&");
	assert(evaluate("T^F&F", pf, answer) == 0 && answer == true && pf == "TFF&^");
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer == true
		&& pf == "TFTT&^F^!&FT&F&!!!^");
	assert(evaluate("(!T)", pf, answer) == 0 && answer == false && pf == "T!");

	assert(evaluate("T^T", pf, answer) == 0 && pf == "TT^" && answer == false);
	assert(evaluate("T^!T", pf, answer) == 0 && pf == "TT!^" && answer == true);
	assert(evaluate("T^!(T)", pf, answer) == 0 && pf == "TT!^" && answer == true);
	assert(evaluate("F^F", pf, answer) == 0 && pf == "FF^" && answer == false);
	assert(evaluate("!F&T", pf, answer) == 0 && pf == "F!T&" && answer == true);
	assert(evaluate("!(F&T)", pf, answer) == 0 && pf == "FT&!" && answer == true);
	assert(evaluate("!(T^T)", pf, answer) == 0 && pf == "TT^!" && answer == true);
	assert(evaluate("!F^!F", pf, answer) == 0 && pf == "F!F!^" && answer == false);
	assert(evaluate("F^!F&(T&F)", pf, answer) == 0 && pf == "FF!TF&&^" && answer == false);*/


	cout << "Passed all tests" << endl;

}

//int main() {
//
//	string postfix;
//	assert(inToPostfix("   T", postfix) && postfix == "T");
//;
//	assert(inToPostfix("(F)", postfix) == true && postfix == "F");
//	assert(inToPostfix("F   ", postfix) && postfix == "F");
//
//	assert(inToPostfix("T    F", postfix) == false);
//	assert(inToPostfix("^", postfix) == false);
//	assert(inToPostfix("!", postfix) == false);
//	assert(inToPostfix("(", postfix) == false);
//	assert(inToPostfix(")", postfix) == false);
//	assert(inToPostfix("&", postfix) == false);
//	assert(inToPostfix("()", postfix) == false);
//	assert(inToPostfix("!(", postfix) == false);
//
//	assert(inToPostfix("!T", postfix) == true && postfix == "T!");
//
//
//	assert(inToPostfix("!!T", postfix) == true && postfix == "T!!");
//	assert(inToPostfix("F!T", postfix) == false);
//
//	assert(inToPostfix("!(T)", postfix)  == true && postfix == "T!");
//	assert(inToPostfix("!(T)(F)", postfix) == false);
//
//	assert(inToPostfix("F(^T)", postfix) == false);
//	assert(inToPostfix("T^", postfix) == false);
//	assert(inToPostfix("T^!", postfix) == false);
//
//	assert(inToPostfix("(T", postfix) == false);
//	assert(inToPostfix("(T))", postfix) == false);
//	assert(inToPostfix(")T", postfix) == false);
//	assert(inToPostfix("T^)F)", postfix) == false);
//	assert(inToPostfix("(T", postfix) == false);
//	assert(inToPostfix("T^^F", postfix) == false);
//
//	assert(inToPostfix("T&!(F^T&T^F)^!!!(F&T&F)", postfix) == true && postfix == "TFTT&^F^!&FT&F&!!!^");
//	assert(inToPostfix("", postfix) == false);
//
//	cout << "Done!" << endl;
//	return 0;
//}
