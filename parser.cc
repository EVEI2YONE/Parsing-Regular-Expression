/*
* Copyright (C) Rida Bazzi, 2017
*
* Do not share this file with anyone
*
* Do not post this file or derivatives of
* of this file online
*
*/
#include <iostream>
#include <cstdlib>
#include "parser.h"

using namespace std;

typedef struct REG_node {
	struct REG_node *first_neighbor;
	char first_label;
	struct REG_node *second_neighbor;
	char second_label;
};

typedef struct REG {
	struct REG_node *start;
	struct REG_node *accept;
};

void Parser::syntax_error()
{
	cout << "SYNTAX ERROR\n";
	//at some point I need to free up all this malloc items <---------------------------
	exit(1);
}

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
	Token t = lexer.GetToken();
	if (t.token_type != expected_type)
		syntax_error();
	return t;
}

// this function simply checks the next token without
// consuming the input
// Written by Mohsen Zohrevandi
Token Parser::peek()
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}

// Parsing

void Parser::parse_input()
{
	//input -> tokens_section INPUT_TEXT

	parse_tokens_section();
	expect(INPUT_TEXT);
}


void Parser::parse_tokens_section()
{
	// tokens_section -> token_list HASH
	parse_token_list();
	expect(HASH);
}

void Parser::parse_token_list()
{
	// token_list -> token
	// token_list -> token COMMA token_list
	parse_token();
	Token t = peek();
	if (t.token_type == COMMA)
	{
		// token_list -> token COMMA token_list
		expect(COMMA);
		parse_token_list();
	}
	else if (t.token_type == HASH)
	{
		// token_list -> token
	}
	else
	{
		syntax_error();
	}

}

void Parser::parse_token()
{
	// token -> ID expr

	expect(ID);
	parse_expr();

}
//returns REG pointer
	//this also means that the REG_expression is created recursively
void Parser::parse_expr()
{
	// expr -> CHAR
	// expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
	// expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
	// expr -> LPAREN expr RPAREN STAR
	// expr -> UNDERSCORE

	Token t = lexer.GetToken();
	if (t.token_type == CHAR) {
		// expr -> CHAR
		//create start and accept REG
		REG *expression = (struct REG *)malloc(sizeof(struct REG));
		//start->char->accept
		//node_1 represents the start node
		//while node_2 is the accept node
		REG_node *node_1 = (struct REG_node *)malloc(sizeof(struct REG_node));
		REG_node *node_2 = (struct REG_node *)malloc(sizeof(struct REG_node));

		//create single character REG expression
		node_1->first_neighbor = node_2;
		node_1->second_neighbor = nullptr;
		node_1->first_label = CHAR;

		node_2->first_neighbor = nullptr;
		node_2->second_neighbor = nullptr;
		
		expression->start = node_1;
		expression->accept = node_2;
		return expression;
	}
	else if (t.token_type == UNDERSCORE) {
		// expr -> UNDERSCORE
		//underscore represents epsilon
		//this is useful as a transition with STAR, AND, OR expressions
		REG *expression = (struct REG *)malloc(sizeof(struct REG));
		//start->underscore->accept
		//node_1 represents start node
		//while node_2 represents accept node
		REG_node *node_1 = (struct REG_node *)malloc(sizeof(struct REG_node));
		REG_node *node_2 = (struct REG_node *)malloc(sizeof(struct REG_node));

		//create single character REG expression
		node_1->first_neighbor = node_2;
		node_1->second_neighbor = nullptr;
		node_1->first_label = '_';

		node_2->first_neighbor = nullptr;
		node_2->second_neighbor = nullptr;
		
		expression->start = node_1;
		expression->accept = node_2;
		return expression;
	}
	else if (t.token_type == LPAREN) {
		// expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
		// expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
		// expr -> LPAREN expr RPAREN STAR
		REG *expression = (struct REG *)malloc(sizeof(struct REG));
		REG *temp = parse_expr();
		expression->start = temp->start;
		expression->accept = temp->accept;
		expect(RPAREN);
		Token t2 = lexer.GetToken();
		if (t2.token_type == DOT || t2.token_type == OR) {
			expect(LPAREN);
			temp = parse_expr();
			if(t2.token_type == DOT){
				expression->accept->first_neighbor = temp->start;
				expression->accept = temp->accept;
			}
			else{
				REG_node *fork_node = (struct REG_node *)malloc(sizeof(REG_node));
				//have the fork node point the the start of expression and temp nodes
				fork_node->first_neighbor = expression->start;
				fork_node->first_label = '_';
				fork_node->second_neighbor = temp->start;
				fork_node->second_label = '_';

				//set up accept node
				REG_node *accept_node = (struct REG_node *)malloc(sizeof(REG_node));
				accept_node->first_neighbor = nullptr;
				accept_node->second_neighbor = nullptr;

				//have the end of expression and temp nodes point to accept node
				expression->accept->first_neighbor = accept_node;
				expression->accept->first_label = '_';
				temp->accept->first_neighbor = accept_node;
				temp->accept->first_label = accept_node;

				//reassign expression start and accept pointers
				expression->start = fork_node;
				expression->accept = expression->accept->first_neighbor;
			}
			//temp is no longer needed
			temp = nullptr;
			expect(RPAREN);
		}
		else if (t2.token_type == STAR){
			REG_node *fork_node = (struct REG_node *)malloc(sizeof(struct REG_node));
			REG_node *accept_node = (struct REG_node *)malloc(sizeof(struct REG_node));
			//set up and link fork node to expression->start and accept_node
			fork_node->first_neighbor = expression->start;
			fork_node->first_label = '_';
			fork_node->second_neighbor = accept_node;
			fork_node->second_label = '_';
			//set up accept_node
			accept_node->first_neighbor = nullptr;
			accept_node->second_neighbor = nullptr;
			//change expression->accept first, that way second neighbor can have easier access to previous neighbor
			expression->accept->first_neighbor = accept_node;
			expression->accept->first_label = '_';
			expression->accept->second_neighbor = expression->start;
			expression->accept->second_label = '_';
			//now that expression->accept is set up, reassign start/accept pointers in expression
			expression->start = fork_node;
			expression->accept = accept_node;
		}
		return expression;
	}
	else {
		syntax_error();
		return nullptr;
	}
}


void Parser::ParseProgram()
{
	parse_input();	//process the entire string of input - token or token_list, along with the lexemes to process
	expect(END_OF_FILE);
}

int main()
{
	Parser parser;
	//----------------------------prompt the user for some input
	parser.ParseProgram(); //function above
}
