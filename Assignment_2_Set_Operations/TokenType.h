#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType
{
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SLASH, STAR, LEFT_SQ_BRACK, RIGHT_SQ_BRACK, POUND, COLON, SEMICOLON,

    // One or two character tokens (the single character tokens can be followed by another)
    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

    // Literals. 
    IDENTIFIER, STRING, NUMBER,

    // Keywords. 
    AND, NOT, CLASS, ELSE, FALSE, DEF, FOR, IF, _NULL, OR, PRINT, RETURN, TRUE, WHILE,

    _EOF
};

#endif