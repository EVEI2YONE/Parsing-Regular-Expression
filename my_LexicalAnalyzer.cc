#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "my_LexicalAnalyzer.h"
using namespace std;

my_LexicalAnalyzer::my_LexicalAnalyzer(Track* l, std::string s) {
    this->list = l;
    this->inputText = s;
    sets_head = NULL;
    my_getToken(inputText, 0);
    free_set();
}

void free_set(){

}

//list contains all tokens and all REG graphs or expressions
//s is the input text at position p
//take note that when p = 0, the text has yet to be parsed
void my_LexicalAnalyzer::my_getToken(std::string s, int p){
    /*
    my_getToken <- should print longest string for token, however many times necessary
    - run through final updated lengths from match
    - set lengths back to 0
    - recursively call my_getToken
    - partitions string for match function
    */





}

void my_LexicalAnalyzer::match(REG *r, string s, int p){
    /*
    match <-cycles through REG nodes of REG graph
        - update the length of maximal strings
        - note: expressions are inserted in reverse order,
        meaning the head is pointing to the last expression
    */
    //match_one_char can return NULL
    set_of_nodes *object = new set_of_nodes;
    object->next = NULL;
    object->node = r->start;
    set_of_nodes *temp1;

    //need initial set_of_nodes from REG r
    temp1 = match_one_char(object, '_');

    //now temp1 will continue to have the current set of nodes
    //temp 2 would need to have next set of nodes...right?
    while (p != s.length) {

        p++;
    }


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
    // 2. if accept state is reached, update set_of_sets parser on - character, string length, or position <------------ set_of_sets longest updated with length further down at accept node point
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
        //assume the set_of_nodes are all epsilon - aka initial letter
        //then all the epsilon nodes are being parsed by the parser in the large do-while loop <------------ASSOCIATED IF COMMENTED OUT PARTS ARE TRUE
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
    // step 1 is the purpose of the do-while loop <-------------------ASSOCIATED IF COMMENTED OUT PARTS ARE TRUE
    //set_of_nodes has REG_node and set_of_nodes pointers
    //do {<---------------COMMENTED OUT
    //create new set_of_nodes for viable nodes
    //accept node
    if(S->node->first_neighbor == NULL){
        sets_head->longest = length; //<--------------------------double check that string length or position is updated correctly
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
        }while(parse2->next != NULL);
        set_of_nodes *find_end = temp1;
        do {
            find_end = find_end->next;
        } while (find_end->next != NULL);
        find_end->next = update;
        update = temp1;
        temp1 = NULL;
        find_end = NULL;
    }
    else{
        cout << "my_LexicalAnalysis match_one_char expression" << endl;
        update = S;
    }
    //} while (parser->next != NULL); <--------------COMMENTED OUT

    return update;
}

