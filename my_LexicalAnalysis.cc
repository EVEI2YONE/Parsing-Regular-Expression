#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

my_LexicalAnalysis::my_LexicalAnalysis(Track *list, string s){

}
void free_set(set_of_sets *S){

}
void my_LexicalAnalysis::my_getToken(){

}

//page 9-10 in pdf
void my_LexicalAnalysis::match(REG *r, string s, int p){

}

//page 9 in pdf
/*
 * Potential issues: how do I keep track of these sets of nodes in a REG expression?
 * Do I use pointers?
 * Do I create multiple sets to keep with n number of REG expressions?
 * How do I know which pointers aren't pointing to the same node?
 *      - especially in the same REG expression?
 */
set_of_nodes * my_LexicalAnalysis::match_one_char(set_of_nodes *S, char c){
    // Goal: find all nodes that can be reached from S by consuming c
    // 1. parse through S and list viable nodes that can be reached from S
    // 2. if accept state is reached, update set_of_sets parser on - character, string length, or position <------------
    // 3. new set_of_nodes list needs to be created and returned
    set_of_nodes *update = nullptr; //acts as the head of updated list
    set_of_nodes *parser = S;
    // step 1 is the purpose of the do-while loop
    // create
    if (parser == nullptr){
        return nullptr;
    }
    //
    //set_of_nodes has REG pointers
    do{
        //create new set_of_nodes for viable nodes
        //check if epsilon, _
        //accept node
        if(S->node->first-neighbor == nullptr){
            return S;
        }
        //1st neighbor has epsilon, and no 2nd neighbor
        else if((parser->node->first_neighbor == '_') && parser->node->second_neighbor == nullptr){
            update = match(temp1->node->first_neighbor);
            return update;
        }//1st and 2nd neighbors have epsilons
        else if((parser->node->first_neighbor == '_') && parser->node->second_neighbor == '_')){
            set_of_nodes *temp1;
            temp1->node = match_one_char(S->node->first_neighbor);
            set_of_nodes *temp2;
            temp2->node = match_one_char(S->node->second_neighbor);
            //temp1 and temp2 are the heads of received list of nodes
            //parse them for comparative purposes
            set_of_nodes *parse1;
            parse1->node = temp1;
            set_of_nodes *parse2;
            parse2->node = temp2;
            //compare the two temp variables, and return one list union of the two: temp1 U temp2
            do {
                int flag = 0;
                do {
                    if(parse1->node->node_num == parse2->node->node_num) {
                        flag = 1;
                    }
                }while(parse1->next != nullptr);
                if(flag == 0) {
                    set_of_nodes *temp3;
                    temp3->node = parser2;
                    temp3->next = update;
                    update = temp3;
                }
            }while(parse2->next != nullptr);
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

    // S' = empty set
    // for every node n in S
    // if ( (there is an edge from n to m labeled with c) &&
    // ( m is not in S') ) {
    // add m to S'
    // }
    //
    // if (S' is empty)
    // return empty set
    //
    // At this point, S' is not empty and it contains the nodes that
    // can be reached from S by consuming the character c directly
    //
    //
    // 2. find all nodes that can be reached from the resulting
    // set S' by consuming no input
    //
    // changed = true
    // S'' = empty set
    // while (changed) {
    // changed = false
    // for every node n in S' {
    // add n to S''
    // for ever neighbor m of n {
    // if ( (the edge from n to m labeled with '_') && ( m is not in S'') )
    // add m to S''
    // }
    // }
    // if (S' not equal to S'') {
    // changed = true;
    // S' = S''
    // S'' = empty set
    // }
    // }
    //
    // at this point the set S' contains all nodes that can be reached
    // from S by first consuming C, then traversing 0 or more epsilon
    // edges
    //
    // return S'

}
