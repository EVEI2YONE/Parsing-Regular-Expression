/*
* Copyright (C) Rida Bazzi, 2017
*
* Do not share this file with anyone
*/
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"

class REG_node {
	REG_node *first_neighbor;
	char first_label;
	REG_node *second_neighbor;
	char second_label;
};

class REG {
	REG_node *start;
	REG_node *accept;
};

class REG_list{
	REG *next;
}head = nullptr;


class Parser {
private:
	LexicalAnalyzer lexer;

	void syntax_error();
	Token expect(TokenType expected_type);
	Token peek();


	void parse_input();
	void parse_char_list();
	void parse_tokens_section();
	void parse_token_list();
	REG * parse_token();
	REG * parse_expr();


public:
	void ParseProgram();
};

#endif

