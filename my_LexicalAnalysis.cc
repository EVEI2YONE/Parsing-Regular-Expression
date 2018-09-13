#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

my_LexicalAnalysis::my_LexicalAnalysis(){

}

void my_LexicalAnalysis::my_getToken();

//page 9-10 in pdf
void my_LexicalAnalysis::match(REG *r, string s, int p);

//page 9 in pdf
/*
 * Potential issues: how do I keep track of these sets of nodes in a REG expression?
 * Do I use pointers?
 * Do I create multiple sets to keep with n number of REG expressions?
 * How do I know which pointers aren't pointing to the same node?
 *      - especially in the same REG expression?
 */
set_of_nodes * my_LexicalAnalysis::match_one_char(set_of_nodes *S, char c){
    // 1. find all nodes that can be reached from S by consuming c
    //
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
