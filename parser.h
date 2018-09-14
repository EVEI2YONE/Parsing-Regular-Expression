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
public:
    REG_node *first_neighbor;
    char first_label;
    REG_node *second_neighbor;
    char second_label;
    int node_num;
};

class REG {
public:
    REG_node *start;
    REG_node *accept;
};

class REG_list {
public:
    REG *expr = nullptr;
    REG_list *next = nullptr;
}*REG_head = nullptr;

//this is for variable Track list for when my_LexicalAnalysis is called with the parameter
//list being a list of structures containing Token pointer and REG pointer
class Track{
public:
    REG_list *reg_pointer;
    Token_list *token_pointer;
};

class Token_list{
    Token *tok_ptr = nullptr;
    Token *next = nullptr;
}*Token_head = nullptr;

class Parser {
private:
    LexicalAnalyzer lexer;
    int num = 1;
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