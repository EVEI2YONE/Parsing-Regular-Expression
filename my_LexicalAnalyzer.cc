#include <iostream>
#include <istream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "my_LexicalAnalyzer.h"
using namespace std;

my_LexicalAnalyzer::my_LexicalAnalyzer(Track* l, std::string s) {
    length = 0;
    this->list = l;
    this->inputText = s;
    //sets_head holds lengths of successful iterations of the REG graphs
    sets_head = NULL;
    //get string without spaces
    int t = 0;
    for (int i = 0; s[i] == ' '; i++) {
        t++;
    }
    int len = inputText.size() - t;
    std::string a = inputText.substr(t, len);
    my_getToken(a, 0);	//<-------------------------MY_GETTOKEN FUNCTION CALLED
    //shparser = sets_head;
    //free_set();
    //sets_head = NULL;
}

void my_LexicalAnalyzer::free_set(set_of_ints *object) {
    if (object->next != NULL) {
        free_set(object->next);
    }
    free(object);
    return;
}

void my_LexicalAnalyzer::free_node(set_of_nodes *object) {
    if (object->next != NULL) {
        object->node = NULL;
        free_node(object->next);
    }
    free(object);
}

//list contains all tokens and all REG graphs or expressions
//s is the input text at position p
//take note that when p = 0, the text has yet to be parsed
void my_LexicalAnalyzer::my_getToken(std::string s, int p) {
    /*
    my_getToken <- should print longest string for token, however many times necessary
    - run through final updated lengths from match
    - set lengths back to 0
    - recursively call my_getToken
    - partitions string for match function
    */
    if (list->reg_pointer == NULL) {
        cout << "ERROR" << endl;
        //exit(1);
        return;
    }
    if (p > s.size() - 1) {
        return;
    }
    //shparser will parse through all the numbers to find the longest length eventually
    shparser = sets_head;
    REG_list *rpparser = list->reg_pointer;	//rpparser is reg_pointer_parser
    Token_list *tlp = list->list_pointer;
    do {
        match(rpparser->expr, s, 0);	//<---------------------MATCH FUNCTION CALLED
        if (length == s.size()) {
            cout << tlp->tok_ptr.lexeme << " , \"" << s << "\"" << endl;
            length = 0;
            return;
        }
        rpparser = rpparser->next;
        tlp = tlp->next;
    } while (rpparser->next != NULL);
    tlp = NULL;
    //reset shparser - shparser inserting new set_of_ints objects within match function at the tail
    shparser = sets_head;
    length = shparser->longest;
    //find longest lexeme
    //shparser parses sets_head <- holds all lengths in order relative to each reg_expr list
    if (shparser->next != NULL) {
        do {
            if (shparser->longest > length) {
                length = shparser->longest;
            }
            shparser = shparser->next;
        } while (shparser->next != NULL);
    }
    //check if entire list was -1 <- suggests that NO EXPRESSION MATCHED
    if (length == -1) {
        cout << "ERROR" << endl;
        //exit(1);
        return;
    }
    //print out appropriate token, lexeme
    shparser = sets_head;
    //find longest length in set_of_ints while incrementing list->list_pointer parser
    Token_list *tlparser = list->list_pointer;
    while (shparser->longest != length) {
        tlparser = tlparser->next;
        shparser = shparser->next;
    }
    if (length == 0) {
        cout << tlparser->tok_ptr.lexeme << " , \"\"" << endl;
    }
    else {
        cout << tlparser->tok_ptr.lexeme << " , \"" << s.substr(0, length) << "\"" << endl;
    }
    int t = 0;
    for (int i = 0; s[i] == ' ' || s[i] == '\n'; i++) {
        t++;
    }
    int len = s.size() - t;
    std::string a = s.substr(t, len);
    shparser = sets_head;
    free_set(shparser);
    sets_head = NULL;
    shparser = NULL;
    my_getToken(a, 0);
    return;
}

void my_LexicalAnalyzer::match(REG *r, string s, int p){
    /*
    match <-cycles through REG nodes of REG graph
        - update the length of maximal strings
        - note: expressions are inserted in queue order
        meaning the head is pointing to the first expression
    */
    length = 0; //tracks length of string parsed successfully - updated at accept node - incremented with successful set_of_nodes returns
    set_of_nodes *object = new set_of_nodes;
    object->next = NULL;
    object->node = r->start;

    //initialize set_of_ints object
    set_of_ints *setTemp = new set_of_ints;
    setTemp->longest = -1;	//keeps track if NULL returned without accept node being reached
    //this means there was an unrecognizeable char
    setTemp->next = NULL;

    //now temp1 will continue to have the current set of nodes
    //keep in mind that match_one_char can return NULL
    if (shparser == NULL) {
        shparser = setTemp;
    }
    else {
        shparser->next = setTemp;
        shparser = setTemp;
    }
    setTemp = NULL;

    //need initial set_of_nodes from REG r
    object = match_one_char(object, '_');	//<------------------MATCH_ONE_CHAR FUNCTION CALLED
    //NULL indicates that there is no more string left to explore
    //p == s.size() indicates that end of string has been parsed
    while (object != NULL && p < s.size()) {
        length++;
        object = match_one_char(object, s[p]);	//update object's set_of_nodes <------MATCH_ONE_FUNCTION CALLED
        p++;
    }
    free_node(object);
    return;
}

set_of_nodes* my_LexicalAnalyzer::match_one_char(set_of_nodes *S, char c){
    /*
    match_one_char <-per REG graph / expression
        - checks if other set_of_nodes are similar, and adds if different
        - recursively checks at position p of string
        - should update length when viable position is reached
    */
    // Goal: find all nodes that can be reached from S by consuming c
    // 1. parse through S (recursively) and list viable nodes that can be reached from S
    // 2. if accept state is reached, update set_of_ints parser on - character, string length, or position <------------ set_of_ints longest updated with length further down at accept node point
    // 3. new set_of_nodes list needs to be created and returned
    set_of_nodes *update;
    set_of_nodes *parser = S;
    if (parser == NULL){
        return NULL;
    }
    //check if char
    //at this point I have all epsilon nodes
    //char nodes only have one neighbor (1st neighbor)
    //there could be more epsilon nodes following suite
    //- this could be due to DOT operator which may follow up with a STAR or OR operator
    if (c != '_') {
        length++;
        //assume the set_of_nodes are all epsilon - aka initial letter
        //by the end of char check, S should be updated...to follow suit with epsilon nodes
        update = NULL;
        do {
            if (parser->node->first_label == c) {
                set_of_nodes *temp1 = new set_of_nodes;
                temp1->node = parser->node;
                temp1->next = update;
                update = temp1;
            }
            parser = parser->next;
        } while (parser->next != NULL); //check all nodes for matching char
        S = update;
        update = NULL;
        parser = S;
        if (S == NULL) {
            return NULL;
        }
    }
    //set_of_nodes has REG_node and set_of_nodes pointers
    //create new set_of_nodes for viable nodes
    //accept node
    if(S->node->first_neighbor == NULL){
        shparser->longest = length; //<--------------------------double check that string length or position is updated correctly
        return S;
    }
        //check if epsilon, _
        //1st neighbor has epsilon, and no 2nd neighbor
    else if ((parser->node->first_label == '_') && (parser->node->second_neighbor == NULL)) {
        //temp1 explores parser's 1st and only neighbor
        set_of_nodes *temp1 = new set_of_nodes;
        temp1->node = parser->node->first_neighbor;
        temp1->next = match_one_char(temp1, c);
        return temp1;
    }//1st and 2nd neighbors have epsilons
    else if((parser->node->first_label == '_') && (parser->node->second_label == '_')){
        //purpose of update is to copy unique elements between temp1 and temp2 to be appended to temp1
        update = new set_of_nodes;

        //dealing with fork-like nodes, two calls to match_one_char
        //temp1 explores parser's 1st neighbor
        set_of_nodes *temp1 = new set_of_nodes;
        temp1->node = parser->node->first_neighbor;
        temp1->next = match_one_char(temp1, c);

        //temp2 explores parser's 2nd neighbor
        set_of_nodes *temp2 = new set_of_nodes;
        temp2->node = parser->node->second_neighbor;
        temp2->next = match_one_char(temp2, c);

        set_of_nodes *parse1 = temp1;
        set_of_nodes *parse2 = temp2;
        do {
            int flag = 0;
            do {
                if(parse1->node->node_num == parse2->node->node_num) {
                    flag = 1;
                }
                parse1 = parse1->next;
            }while(parse1->next != NULL);
            //flag = 1 means there is a copy node pointer
            //flag = 0 means to add the node that parse2 is pointing at to temp_list
            if(flag == 0) {
                //copy set_of_nodes parse 2, add it to updated list
                set_of_nodes *temp3 = new set_of_nodes;
                temp3->node = parse2->node;
                temp3->next = update;
                update = temp3;
                temp3 = NULL;
            }
            parse2 = parse2->next;
        }while(parse2->next != NULL);
        set_of_nodes *find_end = temp1;
        while (find_end->next != NULL) {
            find_end = find_end->next;
        }
        find_end->next = update;
        update = temp1;
        temp1 = NULL;
        find_end = NULL;
    }
    else{
        //cout << "my_LexicalAnalysis match_one_char expression" << endl;
        //update = S;
        update = NULL;
    }

    return update;
}

