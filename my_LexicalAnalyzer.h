#ifndef __MY_LEXICALANALYZER__H__
#define __MY_LEXICALANALYZER__H__

#include <string>

//list of structures needs to be created somewhere <-------------------
//consists of token_name, reg_pointer
class set_of_nodes{
    REG_node *node;
    REG_node *next;
};

class set_of_sets{
    set_of_nodes *s_node = nullptr;
    set_of_sets *next = nullptr;
    int longest = 0;
}*set = nullptr;

class my_LexicalAnalyzer {
private:
public:
    my_LexicalAnalysis(Track *list, string s);
    Token * my_getToken();
    void match(REG *r, String s, int p);
    set_of_nodes * match_one_char(set_of_nodes *S, char c);
    void free_set(set_of_sets *S);
}

#endif //CSE340_PROJECT1_MY_LEXICALANALYZER_H