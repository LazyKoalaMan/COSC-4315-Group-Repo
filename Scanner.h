#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "TokenType.h"
#include "Token.h"

using namespace std;

class Scanner
{
    string source;
    vector<Token> tokens = vector<Token>();
    int start = 0;
    int current = 0;
    int line = 1;
    map<string, TokenType> keywords;

    public:
        Scanner(string source)
        {
            this->source = source;

            keywords["and"] = AND;
            keywords["not"] = NOT;
            keywords["class"] = CLASS;
            keywords["else"] = ELSE;
            keywords["false"] = FALSE;
            keywords["def"] = DEF;
            keywords["for"] = FOR;
            keywords["if"] = IF;
            keywords["NULL"] = _NULL;
            keywords["or"] = OR;
            keywords["print"] = PRINT;
            keywords["return"] = RETURN;
            keywords["true"] = TRUE;
            keywords["while"] = WHILE;
        }

        vector<Token> scanTokens()
        {
            while(!isAtEnd())
            {
                start = current;
                scanToken();
            }
           Token end = Token(_EOF, "", "EOF", line);//CHANGE: third arg was originally NULL
           tokens.push_back(end);
           return tokens;
        }
    
    private:
        bool isAtEnd()
        {
            return current >= source.length();
        }
        bool isDigit(char c)
        {
            return c >= 48 && c <= 57;
        }
        bool isAlpha(char c)
        {
            //[a-zA-Z] || '_'
            return (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95;
        }
        bool isAlphaNumeric(char c)
        {
            return isAlpha(c) || isDigit(c);
        }
        char advance()
        {
            current++;
            return source[current - 1];
        }
        /*void addToken(TokenType type)
        {
            addToken(type, NULL);
        }*/
        void addToken(TokenType type, string literal)
        {
            int length = current - start;
            string text = source.substr(start, length);
            
            Token newToken = Token(type, text, literal, line);
            tokens.push_back(newToken);
        }
        bool match(char expected)
        {
            if (isAtEnd())
                return false;
            if (source[current] != expected)
                return false;
            //else
            current++;
            return true;
        }
        char peek()
        {
            if (isAtEnd())
                return '\0';//FIXME: is this correct?
            return source[current];
        }
        char peekNext()
        {
            if (current + 1 >= source.length())
                return '\0';
            return source[current + 1];
        }
        string totalSpace()
        {
            string temp = "";
            while (peek() == ' ')
            {
                temp = temp + " ";
                advance();
            }
            return temp;
        }
        void stringType()
        {
            while(peek() != '"' && !isAtEnd())
            {
                if (peek() == '\n')
                    line++;
                advance();
            }
            if (isAtEnd())
            {
                //Lox.error(line, "Unterminated string."); //FIXME
                cout << "Error" << endl;
                return;
            }

            //Removs the surrounding quotes
            int length = (current - 1) - start;
            string value = source.substr(start + 1, length);

            //The closing ".
            advance();
            addToken(STRING, value);
        }
        void numberType()
        {
            while (isDigit(peek()))
            {
                advance();
            }
            //take in the "."
            if (peek() == '.' && isDigit(peekNext()))
            {
                advance();
                while (isDigit(peek()))
                {
                    advance();
                }
            }

           // addToken(NUMBER, stod(source.substr(start, current)));//FIXME: possible that it should be current + 1; FIXME: should be double that is passed but issue with literal passing
           int length = (current) - start;
           addToken(NUMBER, source.substr(start, length));
        }
        void identifier()
        {
            while (isAlphaNumeric(peek()))
            {
                advance();
            }

            int length = current - start;
            string text = source.substr(start, length);
            TokenType type = keywords[text];
            if (type == 0)
                type = IDENTIFIER;
            addToken(type, text);//CHANGE: original was addToken(type) with overloaded function that was removed
                                //CHANGE: original second arg was NULL

            //addToken(IDENTIFIER, NULL);
        }
        void scanToken()
        {
            char c = advance();

            switch(c)
            {
                case '(':
                    addToken(LEFT_PAREN, "(");
                    break;
                case ')':
                    addToken(RIGHT_PAREN, ")");
                    break;
                case '{':
                    addToken(LEFT_BRACE, "{");
                    break;
                case '}':
                    addToken(RIGHT_BRACE, "}");
                    break;
                case ',':
                    addToken(COMMA, ",");
                    break;
                case '.':
                    addToken(DOT, ".");
                    break;
                case '-':
                    addToken(MINUS, "-");
                    break;
                case '+':
                    addToken(PLUS, "+");
                    break;
                case ';':
                    addToken(SEMICOLON, ";");
                    break;
                case '*':
                    addToken(STAR, "*");
                    break;
                case '#':
                    while (peek() != '\n' && !isAtEnd())
                        advance();
                    break;
                //non-singular
                case '!':
                    if (match('='))
                    {
                        addToken(BANG_EQUAL, "!=");
                    }
                    else
                    {
                        addToken(BANG, "!");
                    }
                    break;
                case '=':
                    if (match('='))
                    {
                        addToken(EQUAL_EQUAL, "==");
                    }
                    else
                    {
                        addToken(EQUAL, "=");
                    }
                    break;
                case '<':
                    if (match('='))
                    {
                        addToken(LESS_EQUAL, "<=");
                    }
                    else
                    {
                        addToken(LESS, "<");
                    }
                    break;
                case '>':
                    addToken(match('=') ? GREATER_EQUAL : GREATER, NULL);
                    if (match('='))
                    {
                        addToken(GREATER_EQUAL, ">=");
                    }
                    else
                    {
                        addToken(GREATER, ">");
                    }
                    break;
                
                /*case ' '://FIXME: this is extremely questionable for Python because spaces and even tabs might matter
                case '\r':
                case '\t':
                    break;*/
                case '"':
                    stringType();
                    break;
                case '\n':
                    addToken(NEWL, "\n");
                    //the following will capture the indentation as well
                    addToken(NEWL, totalSpace());
                    break;
                default:
                    if (isDigit(c))
                    {
                        numberType();
                    }
                    else if (isAlpha(c))
                    {
                        identifier();
                    }
                    else
                    {
                        //Lox.error(line, "Unexpected character."); //FIXME
                    }
                    break;//FIXME: remove
            }
        }
};

#endif