#ifndef MERKLE_TREE
#define MERKLE_TREE

#include "tree_node.h"
#include "picosha2.h"
#include "tree_handling.h"
#include <vector>
#include <string>

using namespace std;


struct merkle_tree {
    tree_node* tree_root;
    merkle_tree(vector<tree_node*> vector_nodes);
    ~merkle_tree();
    void print_merkle_tree(tree_node *node, int index);
    void delete_merkle_tree(tree_node *node);
};


#endif 