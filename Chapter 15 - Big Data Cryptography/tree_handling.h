#ifndef TREE_MISC
#define TREE_MISC

#include <iostream>
#include <string>
#include "tree.h"
#include "picosha2.h"

using namespace std;

// computes the hash value of the input using SHA256
inline string compute_sha256(string input_string) 
{
    string hash_string = picosha2::hash256_hex_string(input_string);
    return hash_string;
}

// display the hash values from a vector of tree nodes
inline void print_hash_values(vector<tree_node*> vector_nodes) 
{
    for (int i = 0; i < vector_nodes.size(); i++) 
    {
        cout << vector_nodes[i]->hash_value << endl;
    }
}

#endif 