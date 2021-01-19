#ifndef TREE_NODE
#define TREE_NODE

#include <string>
using namespace std;

// define the node of the merkle tree
struct tree_node 
{
    string hash_value; // the hash value
    tree_node *l_neighbour; // the left neighbour 
    tree_node *r_neighbour; // the right neighbour

// instantiates the hash value within the node 
// see the corresponding .cpp file
    tree_node(string value);
};

#endif 