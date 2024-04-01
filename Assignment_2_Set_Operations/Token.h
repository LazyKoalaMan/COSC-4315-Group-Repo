#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "TokenType.h"

using namespace std;

class Token
{
    TokenType type;
    string lexeme;
    //auto literal;//Object literal //FIXME: also add to constructor
    //char literalCh;FIXME: the literal should become a double if a double or a char if a char or etc
    //int literalInt;
    string literalStr;
    int line;

    public:
        Token(TokenType type, string lexeme, string literalStr, int line)
        {
            this->type = type;
            this->lexeme = lexeme;
            this->literalStr = literalStr;
            this->line = line;
        }
        string toString()
        {
            //return "lexeme: " + lexeme + "; literal: " + literalStr;
            return literalStr;
        }
};

#endif