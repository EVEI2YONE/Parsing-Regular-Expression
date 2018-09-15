#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

#include "my_LexicalAnalyzer.h"

using namespace std;
set_of_sets *sets_head = new set_of_sets();

/*
void my_LexicalAnalyzer::analyze(Track *list, string s){
    cout << "testing" << endl;
}
 */
void free_set(set_of_sets *S){

}
void my_LexicalAnalyzer::my_getToken(){

}

//page 9-10 in pdf
void my_LexicalAnalyzer::match(REG *r, string s, int p){

}

//page 9 in pdf
/*
 * Potential issues: how do I keep track of these sets of nodes in a REG expression?
 * Do I use pointers?
 * Do I create multiple sets to keep with n number of REG expressions?
 * How do I know which pointers aren't pointing to the same node?
 *      - especially in the same REG expression?
 */
set_of_nodes* my_LexicalAnalyzer::match_one_char(set_of_nodes *S, char c){
    // Goal: find all nodes that can be reached from S by consuming c
    // 1. parse through S and list viable nodes that can be reached from S
    // 2. if accept state is reached, update set_of_sets parser on - character, string length, or position <------------
    // 3. new set_of_nodes list needs to be created and returned
    set_of_nodes *update;
    set_of_nodes *parser = set_of_nodes;
    // step 1 is the purpose of the do-while loop
    // create
    if (parser == NULL){
        return NULL;
    }
    //
    //set_of_nodes has REG pointers
    do {
        //create new set_of_nodes for viable nodes
        //check if epsilon, _
        //accept node
        if(S->node->first-neighbor == NULL){
            return S;
        }
            //1st neighbor has epsilon, and no 2nd neighbor
        else if((parser->node->first_neighbor == '_') && parser->node->second_neighbor == NULL){
            set_of_sets *temp1;
            temp1-> s_node = match(temp1->node->first_neighbor);
            return temp1;
        }//1st and 2nd neighbors have epsilons
        else if((parser->node->first_neighbor == '_') && (parser->node->second_neighbor == '_')){
            set_of_sets *temp1;
            temp1->s_node = match_one_char(S->node->first_neighbor);
            set_of_sets *temp2;
            temp2->s_node = match_one_char(S->node->second_neighbor);
            //compare the two temp variables, and return one list union of the two: temp1 U temp2
            set_of_sets *parse1 = temp1;
            set_of_sets *parse2 = temp2;
            set_of_sets *temp_list;
            do {
                int flag = 0;
                do {
                    if(parse1->s_node->node->node_num == parse2->s_node->node->node_num) {
                        flag = 1;
                    }
                }while(parse1->next != NULL);
                //flag = 1 means there is a copy node pointer
                //flag = 0 means to add the node that parse2 is pointing at to temp_list
                if(flag == 0) {
                    //<======================================
                }
            }while(parse2->next != NULL);
        }
        else{
            cout << "my_LexicalAnalysis match_one_char expression" << endl;
        }
        //check if char
        if(c != '_'){





        }
        //parse epsilon nodes
        //check if char matches next node
        parser = parser->next;
    }while(parser->next != nullptr);
}
