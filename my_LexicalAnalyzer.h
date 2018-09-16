#ifndef __MY_LEXICALANALYZER__H__
#define __MY_LEXICALANALYZER__H__

#include "parser.h"
#include <string>

struct REG_node {
    struct REG_node *first_neighbor;
    char first_label;
    struct REG_node *second_neighbor;
    char second_label;
    int node_num;
};

struct REG {
    struct REG_node *start;
    struct REG_node *accept;
};

struct REG_list {
    struct REG *expr;
    struct REG_list *next;
};

//this is for variable Track list for when my_LexicalAnalysis is called with the parameter
//list being a list of structures containing Token pointer and REG pointer

class Token_list{
public:
    Token tok_ptr;
    Token_list *next;
    Token_list(){
        //tok_ptr;
        next = NULL;
    }
};

class Track{
public:
    REG_list *reg_pointer;
    Token_list *list_pointer;
    Track() {
        reg_pointer = NULL;
        list_pointer = NULL;
    }
};

//consists of token_name, reg_pointer
struct set_of_nodes{
    REG_node *node;
    set_of_nodes *next;
};

struct set_of_ints{
    set_of_ints *next;
    int longest;
};

class my_LexicalAnalyzer {
public:
    Track *list;
    std::string inputText;
    set_of_ints *sets_head;
    set_of_ints *shparser;
    int length;

    my_LexicalAnalyzer(Track *l, std::string s);
    void my_getToken(std::string, int position);
    void match(REG *r, std::string S, int p);
    set_of_nodes* match_one_char(set_of_nodes *S, char c);
    void free_set(set_of_ints *object);
    void free_node(set_of_nodes *object);
};

#endif //CSE340_PROJECT1_MY_LEXICALANALYZER_H