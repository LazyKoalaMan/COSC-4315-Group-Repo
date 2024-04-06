#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType
{
    LEFT_PAREN, RIGHT_PAREN, COMMA, MINUS, PLUS, STAR, POUND, COLON, SLASH, 
    //the following currently are not used
    LEFT_BRACE, RIGHT_BRACE, LEFT_SQ_BRACK, RIGHT_SQ_BRACK, SEMICOLON, DOT, 

    // One or two character tokens (the single character tokens can be followed by another)
    EQUAL, EQUAL_EQUAL,
    //the following currently are not used
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, BANG, BANG_EQUAL, 

    // Literals. 
    IDENTIFIER, STRING, NUMBER, NEWL, INDENT,

    // Keywords. 
    AND, ELSE, IF, PRINT,
    //the following currently are not used
    CLASS, NOT, FALSE, DEF, FOR, _NULL, OR, RETURN, TRUE, WHILE,

    _EOF
};

#endif