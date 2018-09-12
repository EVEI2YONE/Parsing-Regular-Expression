#ifndef CSE340_PROJECT1_MY_LEXICALANALYSIS_H
#define CSE340_PROJECT1_MY_LEXICALANALYSIS_H
#include <string>

//list of structures needs to be created somewhere <-------------------
//consists of token_name, reg_pointer
typedef struct set_of_nodes{
    REG *list;
};


//my_LexicalAnalyzer(token_name, reg_pointer); parameters are (UNKNOWN *list, *REG reg_pointer)<------------
my_LexicalAnalyzer() {
private:
public:
    void my_getToken();
    void match(REG r, String s, int p);
    set_of_nodes *match_one_char(set_of_nodes S, char c);
}

#endif //CSE340_PROJECT1_MY_LEXICALANALYSIS_H
