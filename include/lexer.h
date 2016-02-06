#pragma once

#undef yyFlexLexer
#include <FlexLexer.h>

class Lexer : public yyFlexLexer {

public:
    Lexer();
    virtual int yylex();
    void resetState();
};
