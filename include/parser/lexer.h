#pragma once

#undef yyFlexLexer
#include <FlexLexer.h>

/**
 * \class Lexer
 * \brief Custom lexer class that inherits from yyFlexLexer.
 *
 * Class for wrapping generated lexer from Flex generator.
 */
class Lexer : public yyFlexLexer {

  public:
	/**
	* Constructor
	*/
	Lexer();

	/**
	* Overriden method from generated lexer for lexical analysis
	*/
	virtual int yylex();

	/**
	* Resets state of lexer
	*/
	void resetState();

	void setServiceState();
};
