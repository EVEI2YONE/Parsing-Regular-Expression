#ifndef __MY_LEXICALANALYZER__H__
#define __MY_LEXICALANALYZER__H__

#include <string>

//list of structures needs to be created somewhere <-------------------
//consists of token_name, reg_pointer
class set_of_nodes{
public:
    REG_node *node;
    REG_node *next;
    set_of_nodes(){
        node = nullptr;
        next = nullptr;
    }
};

class set_of_sets{
public:
    set_of_nodes *s_node;
    set_of_sets *next;
    int longest;
    set_of_sets(){
        s_node = nullptr;
        next = nullptr;
        longest = 0;
    }
    //need set head pointer
};

class my_LexicalAnalyzer {
public:
//    void analyze(Track *list, string s);
    Token* my_getToken();
    void match(REG *r, String s, int p);
    set_of_nodes* match_one_char(set_of_nodes *S, char c);
    void free_set(set_of_sets *S);
};


class REG_node {
public:
    REG_node *first_neighbor;
    char first_label;
    REG_node *second_neighbor;
    char second_label;
    int node_num;
    REG_node(){
        first_neighbor = nullptr;
        second_neighbor = nullptr;
        node_num = 0;
    }
};

class REG {
public:
    REG_node *start;
    REG_node *accept;
    REG() {
        start = nullptr;
        accept = nullptr;
    }
};

class REG_list {
public:
    REG *expr;
    REG_list *next;
    REG_list(){
        expr = nullptr;
        next = nullptr;
    }
};

//this is for variable Track list for when my_LexicalAnalysis is called with the parameter
//list being a list of structures containing Token pointer and REG pointer

class Token_list{
public:
    Token *tok_ptr;
    Token_list *next;
    Token_list(){
        tok_ptr = nullptr;
        next = nullptr;
    }
};

class Track{
public:
    REG_list *reg_pointer;
    Token_list *list_pointer;
    Track() {
        reg_pointer = nullptr;
        list_pointer = nullptr;
    }
};

#endif //CSE340_PROJECT1_MY_LEXICALANALYZER_H