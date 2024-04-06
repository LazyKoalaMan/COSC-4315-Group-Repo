#ifndef PARSEEVAL_H
#define PARSEEVAL_H

#include <bits/stdc++.h>
#include "Token.h"
#include "TokenType.h"
#include <vector>
#include <map>

using namespace std;

int retrieveNum(Token a, map<string, int> vars)
{
	if (a.type == IDENTIFIER)
	{
		return vars[a.literalStr];
	}
	else if (a.type == NUMBER)
	{
		return stoi(a.literalStr);
	}
	return -999999;
}

// Function to return precedence of operators
int prec(Token T) 
{
	/*if (T.literalStr == "^")
		return 3;*/
	if (T.type == SLASH || T.type == STAR)
		return 2;
	else if (T.type == PLUS || T.type == MINUS)
		return 1;
	else
		return -1;
}

// Function to return associativity of operators (vestigial)
/*char associativity(Token T) 
{
	if (c == '^')
		return 'R';
	return 'L'; // Default to left-associative
}*/

//Source: https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression/
//convert infix expression to postfix expression
vector<Token> infixToPostfix(vector<Token> s) 
{
	stack<Token> st;
	vector<Token> result;

	for (int i = 0; i < s.size(); i++) 
	{
		Token c = s[i];

		// If the scanned character is
		// an operand, add it to the output string.
		//if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		if (c.type == IDENTIFIER || c.type == NUMBER)
			result.push_back(c);

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (c.type == LEFT_PAREN)
			st.push(c);

		// If the scanned character is an ‘)’,
		// pop and add to the output string from the stack
		// until an ‘(‘ is encountered.
		else if (c.type == RIGHT_PAREN) {
			while (st.top().type != LEFT_PAREN) 
			{
				//result += st.top();
				result.push_back(st.top());
				st.pop();
			}
			st.pop(); // Pop '('
		}

		// If an operator is scanned
		else {
			while (!st.empty() && prec(s[i]) < prec(st.top()) || !st.empty() && prec(s[i]) == prec(st.top()))
			{
				//removed from condition: associativity(s[i]) == 'L'
				result.push_back(st.top());
				st.pop();
			}
			st.push(c);
		}
	}

	// Pop all the remaining elements from the stack
	while (!st.empty()) 
	{
		result.push_back(st.top());
		st.pop();
	}

	/*for (int i = 0; i < result.size(); i++)
	{
		cout << result[i].literalStr;
	}*/
	return result;
}

//Source: https://www.geeksforgeeks.org/evaluation-of-postfix-expression/
int evaluatePostfix(vector<Token> exp, map<string, int> vars)
{
	// Create a stack of capacity equal to expression size
	stack<int> st;

	// Scan all characters one by one
	for (int i = 0; i < exp.size(); ++i) {
		// If the scanned character is an operand 
		// (number here), push it to the stack.
		if (exp[i].type == NUMBER || exp[i].type == IDENTIFIER)
			st.push(retrieveNum(exp[i], vars));

		// If the scanned character is an operator, 
		// pop two elements from stack apply the operator
		else if (exp[i].type == PLUS || exp[i].type == MINUS || exp[i].type == STAR || exp[i].type == SLASH)
		{
			int val1 = st.top();
			st.pop();
			int val2 = st.top();
			st.pop();
			switch (exp[i].literalStr[0]) {
			case '+':
				st.push(val2 + val1);
				break;
			case '-':
				st.push(val2 - val1);
				break;
			case '*':
				st.push(val2 * val1);
				break;
			case '/':
				st.push(val2 / val1);
				break;
			}
		}
	}
	return st.top();
}

//initial call should set startParam to 0 and endParam to code.size(); indent = 0
void parser(vector<Token> code, int startParam, int endParam, int indent)
{
	int startLine = startParam;
	int endLine = endParam;
	map<string, int> vars;
	for (int i = startParam; i < endParam - 1; i++)//code.size() - 1 to ignore the EOF
	{
		//the following if statement will provide the index for the start of a statement and for that of the next line
		if ((i == 0 && code[i].type != POUND && code[i].type != NEWL) || (code[i - 1].type == NEWL && code[i].type != NEWL))//either first token or token is following a newline but not a newline itself
		{
			startLine = i;
			endLine = i;
			if (code[startLine].type != INDENT || (code[startLine].type == INDENT && code[startLine].literalStr.size() == indent))//only executes if each incoming line has same indentation
			{
				while (endLine != code.size() && code[endLine].type != NEWL)
				{
					endLine++;
				}

				//ASSIGNMENT
				if (code[startLine].type == IDENTIFIER && (startLine + 1 != code.size()) && code[startLine + 1].type == EQUAL)
				{
					//cout << "ASSIGNMENT" << endl;

					vector<Token> arithmetic;
					int curr = startLine;
					while (curr < endLine)
					{
						arithmetic.push_back(code[curr]);
						curr++;
					}

					arithmetic = infixToPostfix(arithmetic);
					int arithmeticValue = evaluatePostfix(arithmetic, vars);

					vars[code[startLine].literalStr] = arithmeticValue;

					//moves the iterator beyond current index
					i = curr;
				}
				//PRINT
				else if (code[startLine].type == PRINT)
				{
					//cout << "PRINT" << endl;

					int curr = startLine + 2;//starts expression to be printed
					string printValue = "";

					while(code[curr].type != RIGHT_PAREN)
					{
						if (code[curr].type == IDENTIFIER)
						{
							int value = vars[code[curr].literalStr];
							printValue = printValue + " " + to_string(value);
						}
						else if (code[curr].type == STRING)
						{
							printValue = printValue + code[curr].literalStr;
						}
						curr++;
					}
					cout << printValue << endl;

					//moves the iterator beyond current index
						//+1 to skip the right parentheses
					i = curr + 1;
				}
				//IF
				else if (code[startLine].type == IF)
				{
					//cout << "IF" << endl;

					int curr = startLine;
					int a = retrieveNum(code[curr + 1], vars);
					Token comparison = code[curr + 2];
					int b = retrieveNum(code[curr + 3], vars);

					bool boolean = false;

					if (comparison.literalStr == "==")
						boolean = (a == b);
					
					//skips to start of next line
					curr = i + 5;

					//hypothetically, this will allow for the execution of what is within if-statement
					//if boolean is false, then the current call will not execute the following lines because they exceed indentation
					if (boolean)
					{
						//FIXME: for now, just execute the very next statement
						//moves to the end of next line
						endLine = curr;
						while(code[curr].type != NEWL)
						{
							endLine++;
						}
						parser(code, curr, endLine, code[curr].literalStr.size());
					}
					else
					{
						//FIXME: for now, just skip the line

						//cout << i << " " << code[i].literalStr << endl;
						//skips the if-statement's line
						while(code[curr].type != NEWL)
						{
							curr++;
						}
						curr++;
						//skips the next line
						while(code[curr].type != NEWL)
						{
							curr++;
						}
						i = curr;					
					}
				}
			}
			else
			{
				/*int curr = startLine;
				while (curr != endParam - 1 && code[curr].literalStr != "\n")
				{
					curr++;
				}

				//skips the current line
				i = curr + 1;*/

				return;
			}
		}
	}
}

#endif