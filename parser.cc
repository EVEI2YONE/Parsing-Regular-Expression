/*
* Copyright (C) Rida Bazzi, 2017
*
* Do not share this file with anyone
*
* Do not post this file or derivatives of
* of this file online
*
*/

//possible need to have #include "iostream.h" - maybe <----------------------------------------
#include <iostream>
#include <cstdlib>
#include "parser.h"
#include "my_LexicalAnalyzer.h"

using namespace std;

Track *list = new Track();
int num = 1;

void Parser::syntax_error()
{
	cout << "SYNTAX ERROR\n";
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
	list = new Track();
	parse_tokens_section();
	Token str = expect(INPUT_TEXT);
	cout << str.lexeme << endl;
	my_LexicalAnalyzer(list, str.lexeme);
}


void Parser::parse_tokens_section()
{
	// tokens_section -> token_list HASH
	//the overall variable is the list that is a list of structures passed through to my_LexicalAnalysis parameter
	parse_token_list();
	expect(HASH);
}

void Parser::parse_token_list()
{
	// token_list -> token
	// token_list -> token COMMA token_list
	parse_token();
	//check if next token is # or ,
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
	num = 1;
}
//returns a REG pointer because a list of REG needs to be created
void Parser::parse_token()
{
	// token -> ID expr
	//new token to be inserted
	Token_list *temp_token = new Token_list();
	Token temp1 = expect(ID);
	temp_token->tok_ptr = new Token();
	temp_token->tok_ptr->line_no = temp1.line_no;
	temp_token->tok_ptr->lexeme = temp1.lexeme;
	temp_token->tok_ptr->token_type = temp1.token_type;

	//new REG expression graph to be inserted
	REG_list* temp_expr = new REG_list;
	temp_expr->next = NULL;
	temp_expr->expr = parse_expr();

	//prep to insert at end
	Token_list *lpparser = list->list_pointer; //lpparser = list_pointer_parser
	REG_list *teparser = list->reg_pointer; //teparser = temp_expr_parser

	//lpparser and teparser will be incremented at the same time, so only need to follow one
	if (lpparser == NULL) {
		list->list_pointer = temp_token;
		list->reg_pointer = temp_expr;
	}
	else {
		//find the end of linked list
		do {
			teparser = teparser->next;
			lpparser = lpparser->next;
		} while (lpparser->next != NULL);
		//insert temp_token and temp_expr
		lpparser->next = temp_token;
		teparser->next = temp_expr;
	}
	temp_token = NULL;
	temp_expr = NULL;
	num = 1; //used to indicate node_num in REG graphs/expressions
}
//returns REG pointer
//this also means that the REG_expression is created recursively
REG* Parser::parse_expr()
{
	// expr -> CHAR
	// expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
	// expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
	// expr -> LPAREN expr RPAREN STAR
	// expr -> UNDERSCORE

	Token t = lexer.GetToken();
	if (t.token_type == CHAR || t.token_type == UNDERSCORE) {
		// expr -> CHAR
		//create start and accept REG
		REG *expression = new REG;
		//start->char->accept
		//node_1 represents the start node
		//while node_2 is the accept node
		REG_node *node_1 = new REG_node;
		REG_node *node_2 = new REG_node;

		//create single character REG expression
		node_1->first_neighbor = node_2;
		node_1->second_neighbor = NULL;
		if (t.token_type == CHAR) {
			node_1->first_label = t.lexeme[0];
		}
		else {
			node_1->first_label = '_';
		}

		node_2->first_neighbor = NULL;
		node_2->second_neighbor = NULL;

		expression->start = node_1;
		expression->accept = node_2;

		node_1->node_num = num;
		num++;
		node_2->node_num = num;
		num++;
		return expression;
	}
	else if (t.token_type == LPAREN) {
		// expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
		// expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
		// expr -> LPAREN expr RPAREN STAR
		REG *expression = parse_expr();
		expect(RPAREN);
		Token t2 = lexer.GetToken();
		if (t2.token_type == DOT || t2.token_type == OR) {
			expect(LPAREN);
			REG *temp = parse_expr();
			if (t2.token_type == DOT) {
				expression->accept->first_label = '_';
				expression->accept->first_neighbor = temp->start;
				expression->accept = temp->accept;
			}
			else {
				REG_node *fork_node = new REG_node;
				//have the fork node point the the start of expression and temp nodes
				fork_node->first_neighbor = expression->start;
				fork_node->first_label = '_';
				fork_node->second_neighbor = temp->start;
				fork_node->second_label = '_';

				//set up accept node
				REG_node *accept_node = new REG_node;
				accept_node->first_neighbor = NULL;
				accept_node->second_neighbor = NULL;

				//have the end of expression and temp nodes point to accept node
				expression->accept->first_neighbor = accept_node;
				expression->accept->first_label = '_';
				temp->accept->first_neighbor = accept_node;
				temp->accept->first_label = '_';

				//reassign expression start and accept pointers
				expression->start = fork_node;
				expression->accept = accept_node;
				temp->accept = NULL;
				temp->start = NULL;
				fork_node->node_num = num;
				num++;
				accept_node->node_num = num;
				num++;
			}
			//temp is no longer needed
			expect(RPAREN);
		}
		else if (t2.token_type == STAR) {
			REG_node *fork_node = new REG_node;
			REG_node *accept_node = new REG_node;
			fork_node->node_num = num;
			num++;
			accept_node->node_num = num;
			num++;

			//set up and link fork node to expression->start and accept_node
			fork_node->first_neighbor = expression->start;
			fork_node->first_label = '_';
			fork_node->second_neighbor = accept_node;
			fork_node->second_label = '_';

			//set up accept_node
			accept_node->first_neighbor = NULL;
			accept_node->second_neighbor = NULL;

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
		return NULL;
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