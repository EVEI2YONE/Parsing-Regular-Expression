#ifndef CSE340_PROJECT1_MY_LEXICALANALYSIS_H
#define CSE340_PROJECT1_MY_LEXICALANALYSIS_H

#include <string>

//list of structures needs to be created somewhere <-------------------
//consists of token_name, reg_pointer
class set_of_nodes{
    REG_node *node;
    REG_node *next;
}*set = nullptr;

//my_LexicalAnalyzer(token_name, reg_pointer); parameters are (UNKNOWN *list, *REG reg_pointer)<------------
class my_LexicalAnalyzer {
private:
public:
    my_LexicalAnalyzer(Track *list, string s);
    Token * my_getToken();
    void match(REG r, String s, int p);
    set_of_nodes * match_one_char(set_of_nodes *S, char c);
}

#endif //CSE340_PROJECT1_MY_LEXICALANALYSIS_H
